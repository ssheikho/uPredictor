#ifndef LAYOUT_ELEMENT_H
#define LAYOUT_ELEMENT_H

#define NOMINMAX

#include <WinSock2.h>
#include <Windows.h>

//#include <vector>

//using namespace std;

class LayoutElement {
public:
	virtual ~LayoutElement() = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual void setOrigin(int x, int y) = 0;
	virtual void updateSizeAllotment(int w, int h) = 0;
	virtual HWND getHWND() = 0;
	virtual HINSTANCE getHInstance() = 0;
};

#endif
