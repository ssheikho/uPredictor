#include "UBCUtil.h"

#include <Eigen/Geometry>

#ifdef _WIN32
	#include <opencv2/imgproc.hpp>
#elif __linux__
	#include <opencv2/imgproc/imgproc.hpp>
#endif

//#include <codecvt>

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>

Eigen::MatrixXd cartToHom(Eigen::MatrixXd inPts) {
	Eigen::MatrixXd outPts(inPts.rows() + 1, inPts.cols());
	outPts.block(0,0, inPts.rows(), inPts.cols()) = inPts;
	outPts.block(inPts.rows(), 0, 1, inPts.cols()) =
		Eigen::MatrixXd::Constant(1, inPts.cols(), 1.0);
	return outPts;
}

Eigen::MatrixXd homToCart(Eigen::MatrixXd inPts) {
	size_t lastRow = inPts.rows() - 1;
	Eigen::MatrixXd outPts(inPts.rows() - 1, inPts.cols());
	for(size_t row = 0; row < lastRow; row++) {
		for(size_t col = 0; col < inPts.cols(); col++) {
			outPts(row, col) = inPts(row, col) / inPts(lastRow, col);
		}
	}
	return outPts;
}

Eigen::MatrixXd svdSolve(Eigen::MatrixXd inA) {
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(inA
		, Eigen::ComputeThinU | Eigen::ComputeThinV);
	//cout << svd.singularValues() << endl;
	//cout << svd.matrixV() << endl;
	return svd.matrixV().block(
		0, svd.matrixV().cols() - 1, svd.matrixV().rows(), 1);
}

void copyEigenToGL(Eigen::Vector3f *from, GLfloat *to) {
	for (int i = 0; i < 3; i++) to[i] = (*from)(i);
}

void copyEigenToGL(Eigen::Vector3f *from, GLfloat **to, int n) {
	for (int i = 0; i < n; i++)	copyEigenToGL(&from[i], to[i]);
}

void copyEigenToGL(Eigen::Vector3d *from, GLfloat *to) {
	for (int i = 0; i < 3; i++) to[i] = (*from)(i);
}

void copyEigenToGL(Eigen::Vector3d *from, GLfloat **to, int n) {
	for (int i = 0; i < n; i++)	copyEigenToGL(&from[i], to[i]);
}

void copyEigenToGL(Eigen::Matrix4d *from, GLdouble *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			to[j * 4 + i] = (*from)(i, j);
		}
	}
}

void copyEigenToGL(Eigen::Matrix4d from, GLdouble *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			to[j * 4 + i] = from(i, j);
		}
	}
}

void copyGLToEigen(GLdouble *from, Eigen::Matrix4d *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(*to)(i, j) = from[j * 4 + i];
		}
	}
}

Eigen::Matrix4d rotX4(double rad) {
	Eigen::Matrix4d rot = Eigen::Matrix4d::Identity();
	Eigen::AngleAxisd aaX(rad, Eigen::Vector3d::UnitX());
	Eigen::Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Eigen::Matrix4d rotY4(double rad) {
	Eigen::Matrix4d rot = Eigen::Matrix4d::Identity();
	Eigen::AngleAxisd aaX(rad, Eigen::Vector3d::UnitY());
	Eigen::Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Eigen::Matrix4d rotZ4(double rad) {
	Eigen::Matrix4d rot = Eigen::Matrix4d::Identity();
	Eigen::AngleAxisd aaX(rad, Eigen::Vector3d::UnitZ());
	Eigen::Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Eigen::Matrix4d transX4(double d) {
	Eigen::Matrix4d trans = Eigen::Matrix4d::Identity();
	trans(0, 3) = d;
	return trans;
}

Eigen::Matrix4d transY4(double d) {
	Eigen::Matrix4d trans = Eigen::Matrix4d::Identity();
	trans(1, 3) = d;
	return trans;
}

Eigen::Matrix4d transZ4(double d) {
	Eigen::Matrix4d trans = Eigen::Matrix4d::Identity();
	trans(2, 3) = d;
	return trans;
}

Eigen::Matrix3d toRotMat(Eigen::Vector3d v) {
	double norm = v.norm();
	Eigen::AngleAxisd aa(norm, v / norm);
	return aa.toRotationMatrix();
}

void diffsizekernel(IplImage *in, IplImage *out, int f, int c) {
	float dkernel[] = { -1, 0, 1 };

	CvMat kernel = cvMat(f, c, CV_32FC1, dkernel);

	//IplImage *imgDiff = cvCreateImage(cvSize(in->width, img->height), IPL_DEPTH_16S, 1);

	cvFilter2D(in, out, &kernel, cvPoint(-1, -1));
}

void diffx(IplImage *in, IplImage *out) {
	return diffsizekernel(in, out, 3, 1);
}

void diffy(IplImage *in, IplImage *out) {
	return diffsizekernel(in, out, 1, 3);
}

float **iplImageDataToArr(IplImage *in) {
	float **retVal = new float*[in->height];
	for (int row = 0; row < in->height; row++)
		retVal[row] = (float *)&in->imageData[row * in->widthStep];
	return retVal;
}

std::string doubleToString(double d, int precision) {
	std::stringstream ws;
	ws.precision(precision);
	ws << std::fixed << d;
	return ws.str();
}

std::wstring doubleToWString(double d, int precision) {
	std::wstringstream ws;
	ws.precision(precision);
	ws << std::fixed << d;
	return ws.str();
}

std::string intToString(UINT64 i) {
	std::stringstream ws;
	ws << i;
	return ws.str();
}

std::wstring intToWString(UINT64 i) {
	std::wstringstream ws;
	ws << i;
	return ws.str();
}

/*
std::string wstringToString(std::wstring s) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(s);
}

std::wstring stringToWString(std::string s) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}
*/

/*
int getNTextLines(IplImage *inImg) {
	cv::Mat img = cv::cvarrToMat(inImg);
	int baseline = 0;
	int fontFace = CV_FONT_HERSHEY_PLAIN;
	int fontScale = 2;
	int thickness = 3;
	cv::Size textSize = cv::getTextSize("0", fontFace, fontScale, thickness,
		&baseline);
	return floor((double)img.rows / (double)textSize.height);
}

void renderTextOnImage(
	IplImage *inImg, std::string text, int lineNo, int justify) {
	cv::Mat img = cv::cvarrToMat(inImg);
	int baseline = 0;
	int fontFace = CV_FONT_HERSHEY_PLAIN;
	int fontScale = 2;
	int thickness = 3;
	cv::Size textSize =
		cv::getTextSize(text.c_str(), fontFace,	fontScale, thickness,
		&baseline);
	//Point textOrg((img.cols - textSize.width) / 2,
	//	(img.rows - textSize.height) / 2);
	cv::Point textOrg;
	switch (justify) {
	case 0:
	case 1:
	case 2:
		textOrg =
			cv::Point(
				img.cols - textSize.width - 10, lineNo * textSize.height);
		break;
	}
	putText(img, text.c_str(), textOrg, fontFace, fontScale,
		cv::Scalar::all(255), thickness, 8);
}
*/

void saveIplImage(std::ofstream &f, IplImage *colorImage) {
	try{
		f.write((const char *)&colorImage->width, sizeof(int));
		f.write((const char *)&colorImage->height, sizeof(int));
		f.write((const char *)&colorImage->depth, sizeof(int));
		f.write((const char *)&colorImage->nChannels, sizeof(int));

		f.write((const char *)&colorImage->nSize, sizeof(int));
		f.write((const char *)&colorImage->ID, sizeof(int));
		//f.write((const char *)colorImage->alphaChannel, sizeof(int));
		//f.write((const char *)colorImage->channelSeq, 4 * sizeof(char));
		//f.write((const char *)colorImage->channelSeq, 4 * sizeof(char));
		f.write((const char *)&colorImage->dataOrder, sizeof(int));
		f.write((const char *)&colorImage->origin, sizeof(int));
		f.write((const char *)&colorImage->align, sizeof(int));
		f.write((const char *)&colorImage->imageSize, sizeof(int));
		//f.write((const char *)&colorImage->imageData, colorImage->imageSize * sizeof(char));
		f.write((const char *)colorImage->imageData, colorImage->imageSize);
		f.write((const char *)&colorImage->widthStep, sizeof(int));
	} 
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

IplImage *loadIplImage(std::ifstream &f) {
	IplImage *colorImage = NULL;
	try{
		int width, height, depth, nChannels;
		f.read((char *)&width, sizeof(int));
		f.read((char *)&height, sizeof(int));
		f.read((char *)&depth, sizeof(int));
		f.read((char *)&nChannels, sizeof(int));

		colorImage = cvCreateImage(cvSize(width, height), depth, nChannels);

		f.read((char *)&colorImage->nSize, sizeof(int));
		f.read((char *)&colorImage->ID, sizeof(int));
		//f.write((const char *)colorImage->alphaChannel, sizeof(int));
		//f.write((const char *)colorImage->colorModel, 4 * sizeof(char));
		//f.write((const char *)colorImage->channelSeq, 4 * sizeof(char));
		f.read((char *)&colorImage->dataOrder, sizeof(int));
		f.read((char *)&colorImage->origin, sizeof(int));
		f.read((char *)&colorImage->align, sizeof(int));
		f.read((char *)&colorImage->imageSize, sizeof(int));
		//f.write((const char *)&colorImage->imageData, colorImage->imageSize * sizeof(char));
		f.read((char *)colorImage->imageData, colorImage->imageSize);
		f.read((char *)&colorImage->widthStep, sizeof(int));
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}

	return colorImage;
}

double rndDouble() {
	return (double)rand() / (double)RAND_MAX;
}

std::vector<std::string> splitString(std::string s) {
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	return std::vector<std::string>(begin, end);
}

//ColorSpacePoint.x & ColorSpacePoint.y
Eigen::MatrixXd generateModelChessboard2D(
	int rows, int cols, double squareWidth
	,double startX, double startY) {
	Eigen::MatrixXd retVal(2, rows * cols);
	for (int row = 0; row < rows; row++)
		for (int col = 0; col < cols; col++) {
			double xPos = (double)row * squareWidth + startX;
			double yPos = (double)col * squareWidth + startY;
			int matIndex = row * cols + col;
			retVal(0, matIndex) = xPos;
			retVal(1, matIndex) = yPos;
		}
	return retVal;
}

void printEigenMathematica(
	Eigen::MatrixXd mat, std::ostream &o, std::string variableName) {
	o.precision(7);
	o << std::fixed;
	o << variableName << " = {" << std::endl;

	for (int row = 0; row < mat.rows(); row++) {
		o << "{";
		for (int col = 0; col < mat.cols(); col++) {
			o << mat(row, col);
			if (col < mat.cols() - 1) o << ",";
		}
		o << "}";
		if (row < mat.rows() - 1) o << ",";
		o << std::endl;
	}

	o << "};" << std::endl;
}

Eigen::MatrixXd CSPToEigenMatrix(CameraSpacePoint *p, int n) {
	Eigen::MatrixXd mat(3, n);
	CSPToEigenMatrix(p, mat);
	return mat;
}

void CSPToEigenMatrix(CameraSpacePoint *p, Eigen::MatrixXd &mat) {
	int n = mat.cols();
	for (int i = 0; i < n; i++) {
		mat(0, i) = p[i].X;
		mat(1, i) = p[i].Y;
		mat(2, i) = p[i].Z;
	}
}

void drawCrosshair(cv::Mat &colorImage, int x, int y, int radius,
	int thickness, CvScalar color) {
	CvPoint ptA, ptB;
	//Horizontal Line
	ptA.x = x - radius;
	ptA.y = y;
	ptB.x = x + radius;
	ptB.y = y;
	line(colorImage, ptA, ptB, color, thickness, 8, 0);
	//Vertical Line
	ptA.x = x;
	ptA.y = y + radius;
	ptB.x = x;
	ptB.y = y - radius;
	line(colorImage, ptA, ptB, color, thickness, 8, 0);
}

void depthToGray(
	cv::Mat &depthImage, cv::Mat &greyImage, cv::Mat &colorImage
	, float scalar) {
	depthImage.convertTo(greyImage, CV_8UC1, -255.0f / scalar, 255.0f);

	std::vector<cv::Mat> m;
	m.push_back(greyImage);
	m.push_back(greyImage);
	m.push_back(greyImage);

	cv::merge(m, colorImage);
}

void saveWString(std::fstream &f, std::wstring s) {
	long len = s.length();
	f.write((char *)&len, sizeof(long));
	f.write((char *)s.data(), len * sizeof(wchar_t));
}

std::wstring readWString(std::fstream &f) {
	long len;
	f.read((char *)&len, sizeof(long));

	wchar_t *c = new wchar_t[len + 1];
	f.read((char *)c, len * sizeof(wchar_t));
	c[len] = 0;

	std::wstring retVal = c;
	delete[] c;
	return retVal;
}

#ifdef _WIN32

double convertSystemTimeToMS(SYSTEMTIME &st) {
	/*
	typedef struct _SYSTEMTIME {
		WORD wYear;
		WORD wMonth;
		WORD wDayOfWeek;
		WORD wDay;
		WORD wHour;
		WORD wMinute;
		WORD wSecond;
		WORD wMilliseconds;
	} SYSTEMTIME, *PSYSTEMTIME;
	*/
	return
		(double)st.wHour * 360.0 +
		(double)st.wMinute * 60.0 +
		(double)st.wSecond +
		(double)st.wMilliseconds / 1000.0;
}

void kinectJointPositionDump(Joint *j, CameraSpacePoint *p, int n) {
	for (int i = 0; i < n; i++) {
		memcpy(&p[i], &j[i].Position, sizeof(CameraSpacePoint));
	}
}

std::wstring getCurDateLabelString() {
	std::wstringstream ws;
	SYSTEMTIME st;
	GetSystemTime(&st);

	ws << st.wYear << "_" << st.wMonth << "_" << st.wDay << "_" << st.wHour <<
		"_" << st.wMinute << "_" << st.wSecond;

	return ws.str();
}
#elif __linux__
#endif
