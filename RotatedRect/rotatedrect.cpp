#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image(300, 500, CV_8UC1, Scalar(255));			// 행렬 선언
	Point2f	center(250, 150), pts[4];
	Size2f	size(300, 100);
	RotatedRect	rot_rect(center, size, 20);				// 회전사각형 선언
	
	Rect bound_rect = rot_rect.boundingRect();
	rectangle(image, bound_rect, Scalar(0), 1);			// 사각형 그리기
	circle(image, rot_rect.center, 1, Scalar(0), 2);	// 원 그리기
	
	rot_rect.points(pts);								// 회전사각형 꼭짓점 변환
	for(int i = 0; i < 4; i++) {
		circle(image, pts[i], 4, Scalar(0), 1);					// 꼭짓점 표시
		line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);	// 꼭짓점 잇는 직선
	}
	
	imshow("회전사각형", image);
	waitKey(0);
	return 0;	
}
