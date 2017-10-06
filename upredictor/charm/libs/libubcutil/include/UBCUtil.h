#ifndef UBC_UTIL_H
#define UBC_UTIL_H

#include <WinSock2.h>
#include <Windows.h>

#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/flann/flann.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/legacy/compat.hpp"

#include <Eigen/Core>

#include <GL/GL.h>

#include <fstream>
#include <memory>
#include <string>

using namespace cv;
using namespace Eigen;
using namespace std;

#define EPSILON 0.000001

void copyEigenToGL(Vector3f *from, GLfloat *to);
void copyEigenToGL(Vector3f *from, GLfloat **to, int n);
void copyEigenToGL(Vector3d *from, GLfloat *to);
void copyEigenToGL(Vector3d *from, GLfloat **to, int n);
void copyEigenToGL(Matrix4d *from, GLdouble *to);
void copyEigenToGL(Matrix4d from, GLdouble *to);
void copyGLToEigen(GLdouble *from, Matrix4d *to);

void printEigenMathematica(MatrixXd &mat, ostream &o, string variableName);

Matrix4d rotX4(double rad);
Matrix4d rotY4(double rad);
Matrix4d rotZ4(double rad);

Matrix4d transX4(double d);
Matrix4d transY4(double d);
Matrix4d transZ4(double d);

Matrix3d toRotMat(Vector3d v);

void diffsizekernel(IplImage *in, IplImage *out, int f, int c);
void diffx(IplImage *img, IplImage *out);
void diffy(IplImage *img, IplImage *out);

//Allocates the outer array only
float **iplImageDataToArr(IplImage *in);

double convertSystemTimeToMS(SYSTEMTIME &st);
string doubleToString(double d, int precision);
wstring doubleToWString(double d, int precision);

string intToString(UINT64 i);
wstring intToWString(UINT64 i);
//LPCTSTR intToLPCSTR(UINT64 i);

string wstringToString(wstring s);
wstring stringToWString(string s);

int getNTextLines(IplImage *inImg);

//justify 0 - Left, 1 - Right, 2 - Center
void renderTextOnImage(IplImage *inImg, string text, int lineNo, int justify);

wstring getCurDateLabelString();

void saveIplImage(ofstream &f, IplImage *colorImage);
IplImage *loadIplImage(ifstream &f);

double rndDouble();
int rndInt(int minVal, int maxVal);

vector<string> splitString(string s);

/*
int av2ipl(AVFrame *src, IplImage *dst, int height, int width);
int ipl2av(IplImage* src, AVFrame* dst, int height, int width);
*/

#endif