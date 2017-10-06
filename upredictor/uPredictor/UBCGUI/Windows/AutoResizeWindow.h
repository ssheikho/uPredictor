#ifndef AUTO_RESIZE_WINDOW_H
#define AUTO_RESIZE_WINDOW_H

#include "LayoutContainer.h"
#include "DefaultShutdownInterface.h"

#include <map>

using namespace std;

class AutoResizeWindow : public LayoutContainer, public DefaultShutdownInterface {
public:
	AutoResizeWindow(HINSTANCE hInstance, int minW, int minH);
	~AutoResizeWindow();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	int getMaxWidth(LayoutElement *child);
	int getMaxHeight(LayoutElement *child);

	void prepareForSizeChanges();
	void postSizeChanges();
	void updateSizeInfo(LayoutElement *child);

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	void onChildAdd(LayoutElement *child);
	void onClear();

	//ShutdownInterface
	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);

	static WNDCLASSW _wc;
	static map<HWND, AutoResizeWindow *> _hcb;
	static bool _initialized;

	HINSTANCE _hInstance;
	int _minW, _minH, _curW, _curH;
	HWND _hwnd;
};

#endif
