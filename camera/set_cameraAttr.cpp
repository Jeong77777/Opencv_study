#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// 문자열 출력 함수 - 그림자 효과
void put_string(Mat &frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);			// 그림자 효과
	putText(frame, text,    pt, font, 0.7, Scalar(120, 200, 90), 2);	// 작성 문자
}

VideoCapture capture;				// 전역 변수 선언 - 여러 함수에서 사용

void zoom_bar(int value, void*) {					// 트렉바 콜백함수
	capture.set(CAP_PROP_ZOOM, value);				// 줌 설정
}
void focus_bar(int value, void*) {
	capture.set(CAP_PROP_FOCUS, value);				// 초점 설정
}

int main()
{
	capture.open(0);
	CV_Assert(capture.isOpened());
	
	//capture.set(CAP_PROP_FRAME_WIDTH, 400);					// 카메라 프레임 너비
	//capture.set(CAP_PROP_FRAME_HEIGHT, 300);
	//capture.set(CAP_PROP_AUTOFOCUS, 0);						// 오토포커싱 중지
	//capture.set(CAP_PROP_BRIGHTNESS, 150);					// 프레임 밝기 초기화
	
	int zoom = capture.get(CAP_PROP_ZOOM);					// 카메라 속성 가져오기
	int focus = capture.get(CAP_PROP_FOCUS);
	
	string title = "카메라 속성변경";							// 윈도우 이름 지정
	namedWindow(title);										// 윈도우 생성
	createTrackbar("zoom", title, &zoom, 10, zoom_bar);		// 윈도우에 줌 트랙바 추가
	createTrackbar("focus", title, &focus, 40, focus_bar);
	
	for(;;) {
		Mat frame;
		capture >> frame;										// 카메라 영상받기
		
		put_string(frame, "zoom: ", Point(10, 240), zoom);		// 줌 값 영상 표시
		put_string(frame, "focus: ", Point(10, 270), focus);	// 포커스
		
		imshow(title, frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}
