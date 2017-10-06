#ifndef UBC_UTIL_H
#define UBC_UTIL_H

#ifdef _WIN32
	#define NOMINMAX
	#include <WinSock2.h>
	#include <Kinect.h>
	#include <Windows.h>
#elif __linux__
	#include <pthread.h>
	#include <semaphore.h>
	#include "FakeWindowsTypes.h"
#endif

#include <opencv/cv.h>

#include <Eigen/Core>

#include <GL/gl.h>

#include <fstream>
#include <memory>
#include <string>

#define EPSILON 0.000001

template<typename T, typename U>
Eigen::Matrix<U,Eigen::Dynamic,Eigen::Dynamic>
	copyAndCast(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> in) {
	size_t rows = in.rows();
	size_t cols = in.cols();
	Eigen::Matrix<U,Eigen::Dynamic,Eigen::Dynamic> out(rows, cols);
	for(size_t row = 0; row < rows; row++)
		for(size_t col = 0; col < cols; col++)
			out(row,col)= U(in(row,col));

	//cout << rows << "	" << cols << endl;

	return out;
}

Eigen::MatrixXd cartToHom(Eigen::MatrixXd inPts);
Eigen::MatrixXd homToCart(Eigen::MatrixXd inPts);
Eigen::MatrixXd svdSolve(Eigen::MatrixXd inA);

void copyEigenToGL(Eigen::Vector3f *from, GLfloat *to);
void copyEigenToGL(Eigen::Vector3f *from, GLfloat **to, int n);
void copyEigenToGL(Eigen::Vector3d *from, GLfloat *to);
void copyEigenToGL(Eigen::Vector3d *from, GLfloat **to, int n);
void copyEigenToGL(Eigen::Matrix4d *from, GLdouble *to);
void copyEigenToGL(Eigen::Matrix4d from, GLdouble *to);
void copyGLToEigen(GLdouble *from, Eigen::Matrix4d *to);

Eigen::Matrix4d rotX4(double rad);
Eigen::Matrix4d rotY4(double rad);
Eigen::Matrix4d rotZ4(double rad);

Eigen::Matrix4d transX4(double d);
Eigen::Matrix4d transY4(double d);
Eigen::Matrix4d transZ4(double d);

Eigen::Matrix3d toRotMat(Eigen::Vector3d v);

void diffsizekernel(IplImage *in, IplImage *out, int f, int c);
void diffx(IplImage *img, IplImage *out);
void diffy(IplImage *img, IplImage *out);

//Allocates the outer array only
float **iplImageDataToArr(IplImage *in);

std::string doubleToString(double d, int precision);
std::wstring doubleToWString(double d, int precision);

template<typename T> std::string thingToString(T i, int precision) {
	std::stringstream ws;
	ws.precision(precision);
	ws << std::fixed << i;
	return ws.str();
}

template<typename T> std::wstring thingToWString(T i, int precision) {
	std::wstringstream ws;
	ws.precision(precision);
	ws << std::fixed << i;
	return ws.str();
}

std::string intToString(UINT64 i);
std::wstring intToWString(UINT64 i);
//LPCTSTR intToLPCSTR(UINT64 i);

std::string wstringToString(std::wstring s);
std::wstring stringToWString(std::string s);

int getNTextLines(IplImage *inImg);

//justify 0 - Left, 1 - Right, 2 - Center
void renderTextOnImage(
	IplImage *inImg
	, std::string text
	, int lineNo
	, int justify);

void saveIplImage(std::ofstream &f, IplImage *colorImage);
IplImage *loadIplImage(std::ifstream &f);

double rndDouble();

std::vector<std::string> splitString(std::string s);

//Across rows, then columns
Eigen::MatrixXd generateModelChessboard2D(int rows, int cols,
	double squareWidth = 1.0, double startX = 0.0, double startY = 0.0);

//Eigen routines to Mathematica
void printEigenMathematica(
	Eigen::MatrixXd mat, std::ostream &o, std::string variableName);

void CSPToEigenMatrix(CameraSpacePoint *p, Eigen::MatrixXd &mat);

void drawCrosshair(cv::Mat &colorImage, int x, int y, int radius,
	int thickness, CvScalar color);

void depthToGray(
	cv::Mat &depthImage, cv::Mat &greyImage, cv::Mat &colorImage
	, float scalar = 8000);

void saveWString(std::fstream &f, std::wstring s);
std::wstring readWString(std::fstream &f);

#ifdef _WIN32
	double convertSystemTimeToMS(SYSTEMTIME &st);

	void kinectJointPositionDump(Joint *j, CameraSpacePoint *p, int n);
	Eigen::MatrixXd CSPToEigenMatrix(CameraSpacePoint *p, int n);

	std::wstring getCurDateLabelString();

#elif __linux__
#endif


#endif
