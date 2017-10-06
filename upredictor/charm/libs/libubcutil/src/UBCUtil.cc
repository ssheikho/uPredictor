#include "UBCUtil.h"

#include <Eigen\Geometry>

#include <codecvt>
#include <iterator>
/*
extern "C" {
	#include <swscale.h>
}
*/

#include <cstdlib>
#include <sstream>

void copyEigenToGL(Vector3f *from, GLfloat *to) {
	for (int i = 0; i < 3; i++) to[i] = (*from)(i);
}

void copyEigenToGL(Vector3f *from, GLfloat **to, int n) {
	for (int i = 0; i < n; i++)	copyEigenToGL(&from[i], to[i]);
}

void copyEigenToGL(Vector3d *from, GLfloat *to) {
	for (int i = 0; i < 3; i++) to[i] = (*from)(i);
}

void copyEigenToGL(Vector3d *from, GLfloat **to, int n) {
	for (int i = 0; i < n; i++)	copyEigenToGL(&from[i], to[i]);
}

void copyEigenToGL(Matrix4d *from, GLdouble *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			to[j * 4 + i] = (*from)(i, j);
		}
	}
}

void copyEigenToGL(Matrix4d from, GLdouble *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			to[j * 4 + i] = from(i, j);
		}
	}
}

void copyGLToEigen(GLdouble *from, Matrix4d *to) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(*to)(i, j) = from[j * 4 + i];
		}
	}
}

void printEigenMathematica(MatrixXd &mat, ostream &o, string variableName) {
	o.precision(7);
	o << std::fixed;
	o << variableName << " = {" << endl;

	for (int row = 0; row < mat.rows(); row++) {
		o << "{";
		for (int col = 0; col < mat.cols(); col++) {
			o << mat(row, col);
			if (col < mat.cols() - 1) o << ",";
		}
		o << "}";
		if (row < mat.rows() - 1) o << ",";
		o << endl;
	}

	o << "};" << endl;
}

Matrix4d rotX4(double rad) {
	Matrix4d rot = Matrix4d::Identity();
	AngleAxisd aaX(rad, Vector3d::UnitX());
	Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Matrix4d rotY4(double rad) {
	Matrix4d rot = Matrix4d::Identity();
	AngleAxisd aaX(rad, Vector3d::UnitY());
	Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Matrix4d rotZ4(double rad) {
	Matrix4d rot = Matrix4d::Identity();
	AngleAxisd aaX(rad, Vector3d::UnitZ());
	Matrix3d mX = aaX.toRotationMatrix();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = mX(i, j);
		}
	}

	return rot;
}

Matrix4d transX4(double d) {
	Matrix4d trans = Matrix4d::Identity();
	trans(0, 3) = d;
	return trans;
}

Matrix4d transY4(double d) {
	Matrix4d trans = Matrix4d::Identity();
	trans(1, 3) = d;
	return trans;
}

Matrix4d transZ4(double d) {
	Matrix4d trans = Matrix4d::Identity();
	trans(2, 3) = d;
	return trans;
}

Matrix3d toRotMat(Vector3d v) {
	double norm = v.norm();
	AngleAxisd aa(norm, v / norm);
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

string doubleToString(double d, int precision) {
	stringstream ws;
	ws.precision(precision);
	ws << fixed << d;
	return ws.str();
}

wstring doubleToWString(double d, int precision) {
	wstringstream ws;
	ws.precision(precision);
	ws << fixed << d;
	return ws.str();
}

string intToString(UINT64 i) {
	stringstream ws;
	ws << i;
	return ws.str();
}

wstring intToWString(UINT64 i) {
	wstringstream ws;
	ws << i;
	return ws.str();
}

//LPCTSTR intToLPCSTR(UINT64 i) {
//
//}

string wstringToString(wstring s) {
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(s);
}

wstring stringToWString(string s) {
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}

int getNTextLines(IplImage *inImg) {
	Mat img(inImg);
	int baseline = 0;
	int fontFace = CV_FONT_HERSHEY_PLAIN;
	int fontScale = 2;
	int thickness = 3;
	Size textSize = getTextSize("0", fontFace, fontScale, thickness,
		&baseline);
	return floor((double)img.rows / (double)textSize.height);
}

void renderTextOnImage(IplImage *inImg, string text, int lineNo, int justify) {
	Mat img(inImg);
	int baseline = 0;
	int fontFace = CV_FONT_HERSHEY_PLAIN;
	int fontScale = 2;
	int thickness = 3;
	Size textSize = getTextSize(text.c_str(), fontFace,	fontScale, thickness,
		&baseline);
	//Point textOrg((img.cols - textSize.width) / 2,
	//	(img.rows - textSize.height) / 2);
	Point textOrg;
	switch (justify) {
	case 0:
	case 1:
	case 2:
		textOrg = Point(img.cols - textSize.width - 10, lineNo * textSize.height);
		break;
	}
	putText(img, text.c_str(), textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);
}

wstring getCurDateLabelString() {
	wstringstream ws;
	SYSTEMTIME st;
	GetSystemTime(&st);

	ws << st.wYear << "_" << st.wMonth << "_" << st.wDay << "_" << st.wHour <<
		"_" << st.wMinute << "_" << st.wSecond;

	return ws.str();
}

void saveIplImage(ofstream &f, IplImage *colorImage) {
	try{
		f.write((const char *)&colorImage->width, sizeof(int));
		f.write((const char *)&colorImage->height, sizeof(int));
		f.write((const char *)&colorImage->depth, sizeof(int));
		f.write((const char *)&colorImage->nChannels, sizeof(int));

		f.write((const char *)&colorImage->nSize, sizeof(int));
		f.write((const char *)&colorImage->ID, sizeof(int));
		//f.write((const char *)colorImage->alphaChannel, sizeof(int));
		//f.write((const char *)colorImage->colorModel, 4 * sizeof(char));
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
		cerr << e.what() << endl;
	}
}

IplImage *loadIplImage(ifstream &f) {
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
		cerr << e.what() << endl;
	}

	return colorImage;
}

/*
int av2ipl(AVFrame *src, IplImage *dst, int height, int width) {
	struct SwsContext *swscontext = sws_getContext(width, height, AV_PIX_FMT_BGRA, dst->width, dst->height, AV_PIX_FMT_BGRA, SWS_BILINEAR, 0, 0, 0);
	if (swscontext == 0)
		return 0;
	int linesize[4] = { dst->widthStep, 0, 0, 0 };
	sws_scale(swscontext, src->data, src->linesize, 0, height, (uint8_t **)& (dst->imageData), linesize);
	return 1;
}

int ipl2av(IplImage* src, AVFrame* dst, int height, int width) {
	int num_bytes = avpicture_get_size(AV_PIX_FMT_BGRA, width, height);
	uint8_t* frame2_buffer = (uint8_t *)av_malloc(num_bytes*sizeof(uint8_t));
	avpicture_fill((AVPicture*)dst, frame2_buffer, AV_PIX_FMT_BGRA, width, height);

	struct SwsContext *swscontext = sws_getContext(width, height, AV_PIX_FMT_BGRA, width, height, AV_PIX_FMT_BGRA, SWS_BILINEAR, 0, 0, 0);
	if (swscontext == 0) {
		return 0;
	}
	int linesize[4] = { src->widthStep, 0, 0, 0 };
	sws_scale(swscontext, (uint8_t **)& (src->imageData), linesize, 0, height, dst->data, dst->linesize);
	return 1;
	}
*/

double rndDouble() {
	return (double)rand() / (double)RAND_MAX;
}

int rndInt(int minVal, int maxVal) {
	int range = maxVal - minVal + 1;
	int val = rndDouble() * range;
	return val + minVal;
}

vector<string> splitString(string s) {
	stringstream ss(s);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	return vector<string>(begin, end);
}
