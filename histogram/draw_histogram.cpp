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

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));				// 그래프 행렬
	float bin = (float)hist_img.cols / hist.rows;			// 한 계급 너비
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);
	
	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = i * bin;						// 막대 사각형 시작 x 좌표
		float end_x = (i + 1) * bin;					// 막대 사각형 종료 x 좌표
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));
		
		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);	// 막대 사각형 그리기
	}
	flip(hist_img, hist_img, 0);
}

int main()
{
	Mat image = imread("./image/lenna.bmp", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());								// 예외처리
	
	Mat hist, hist_img;
	calc_Histo(image, hist, 256);							// 히스토그램 계산
	draw_histo(hist, hist_img);								// 그래프 그리기
	
	imshow("image", image);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;
}
