#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	vector<float> v1, v_exp, v_log;				// float 벡터 선언
	Matx <float, 1, 5> m1(1, 2, 3, 5, 10);		// Matx 객체 선언 및 초기화
	Mat m_exp, m_sqrt, m_pow;
	v1.push_back(1);							// 원소 추가
	v1.push_back(2);
	v1.push_back(3);
	
	exp(v1, v_exp);								// 벡터에 대한 지수 계산
	exp(m1, m_exp);								// 행렬에 대한 지수 계산
	log(m1, v_log);								// 입력은 행렬, 출력은 벡터
	sqrt(m1, m_sqrt);							// 제곱근 계산
	pow(m1, 3, m_pow);							// 3 거듭제곱 계산
	
	cout << "[m1] = " << m1 << endl << endl;
	cout << "[v_exp] = " << ((Mat)v_exp).reshape(1, 1) << endl;
	cout << "[m_exp] = " << m_exp << endl;
	cout << "[v_log] = " << ((Mat)v_log).reshape(1, 1) << endl << endl;
	
	cout << "[m_sqrt] = " << m_sqrt << endl;
	cout << "[m_pow] = " << m_pow << endl;
	return 0;
}
