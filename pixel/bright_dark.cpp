#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("./image/lenna.bmp", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());
	
	Mat dst1 = image + 100;										// 영상 밝게
	Mat dst2 = image - 100;										// 영상 어둡게
	Mat dst3 = 255 - image;										// 영상 반전
	
	Mat dst4(image.size(), image.type());
	Mat dst5(image.size(), image.type());
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			dst4.at<uchar>(i, j) = image.at<uchar>(i, j) + 100;		// 영상 밝기
	//		dst4.at<uchar>(i, j) = saturate_cast(image.at<uchar>(i, j) + 100);
			dst5.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);		// 영상 반전
		}
	}
	
	imshow("원 영상", image),			imshow("dst1 - 밝게", dst1);
	imshow("dst2 - 어둡게", dst2),	imshow("dst3 - 반전", dst3);
	imshow("dst4 - 밝게", dst4),		imshow("dst5 - 반전", dst5);
	waitKey();
	return 0;
}
