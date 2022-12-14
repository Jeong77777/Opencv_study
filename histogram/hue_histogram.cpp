#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
				   

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int		histSize[] = { bins };						// 히스토그램 계급 개수
	float	range[] = { 0, (float)range_max };			// 0번 채널 화소값 범위
	int		channels[] = { 0 };							// 채널 목록 - 단일 채널
	const float* ranges[] = { range };					// 모든 채널 화소 범위
	
	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
							   
		  
	   
}

// hue 채널에 대한 색상 팔레트 행렬 생성
Mat make_palatte(int rows)
{
	Mat hsv(rows, 1, CV_8UC3);
	for (int i = 0; i < rows; i++)							// 행수만큼 반복
	{
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);		// 색상 계산
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);			// HSV 컬러 지정
	}

	cvtColor(hsv, hsv, COLOR_HSV2BGR);							// HSV 컬러 -> RGB 컬러

	return hsv;
}

// 색상으로 히스토그램 그리기
void draw_histo_hue(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	Mat hsv_palatte = make_palatte(hist.rows);
	
	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float bin = (float)hist_img.cols / hist.rows;			// 계급 개수
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);	// 정규화
	
	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));
		
		Scalar color = hsv_palatte.at<Vec3b>(i);
				   
		if (pt2.y>0) rectangle(hist_img, pt1, pt2, color, -2);

	}
	flip(hist_img, hist_img, 0);

}

int main()
{
	Mat image = imread("./image/lenna.bmp", 1);				// 컬러 영상 읽기
	CV_Assert(!image.empty());
	
	Mat HSV_img, HSV_arr[3];
	cvtColor(image, HSV_img, COLOR_BGR2HSV);					// BGR 컬러 -> HSV 컬러
	split(HSV_img, HSV_arr);								// 채널 분리
	
	Mat hue_hist, hue_hist_img;
	calc_Histo(HSV_arr[0], hue_hist, 18, 180);		// Hue 채널 히스토그램 계산
	draw_histo_hue(hue_hist, hue_hist_img, Size(360, 200));	// 히스토그램 그래프
	
	imshow("image", image);
	imshow("Hue_hist_img", hue_hist_img);
	waitKey();

	return 0;
}
