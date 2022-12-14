#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("./image/lenna.bmp", IMREAD_COLOR);	// 컬러 영상 로드
	CV_Assert(image.data);							// 예외 처리
	
	Mat bgr[3];
	split(image, bgr);								// 3채널 행렬에서 채널 분리
	
	imshow("image", image);
	imshow("blue 채널", bgr[0]);
	imshow("green 채널", bgr[1]);
	imshow("red 채널", bgr[2]);
	waitKey(0);
	return 0;
}
