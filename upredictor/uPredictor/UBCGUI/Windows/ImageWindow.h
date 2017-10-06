#ifndef IMAGE_WINDOW_H
#define IMAGE_WINDOW_H

#include <WinSock2.h>
#include <Windows.h>

//#include "KinectImageFrameRecipient.h"
#include "DragRect.h"
#include "LayoutElement.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <opencv/cv.hpp>

#include <map>

using namespace std;

struct FrameDesc;
class LayoutContainer;

class ImageWindow :
	public LayoutElement
	, public TypeRecipient<cv::Mat>
	, public TypeBroadcaster<pair<int, int>>
	, public TypeBroadcaster<DragRect> {
public:
	ImageWindow(LayoutContainer *parent, int w, int h, wstring name,
		double xClickMultiplier = 1.0, double yClickMultiplier = 1.0);
	~ImageWindow();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();
	
	//public TypeBroadcaster<cv::Mat *>::TypeRecipient
	void processType(cv::Mat inObj);
	void onStartup();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
		LPARAM lParam);

protected:
	static bool _isInitialized;
	static WNDCLASSW _wc;
	static map<HWND, ImageWindow *> _iw;

	LayoutContainer *_parent;
	int _x, _y, _w, _h;
	pair<int, int> _clickStart, _clickEnd;
	double _xClickMultiplier, _yClickMultiplier;
	HWND _hwnd;
	//HDC _hdc;
	BITMAPINFOHEADER _bi;
	HBITMAP _hbmp;
	cv::Mat _rgb;
	//BITMAP _bmp;
};

#endif