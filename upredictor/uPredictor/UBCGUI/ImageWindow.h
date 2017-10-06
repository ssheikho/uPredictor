#ifndef IMAGE_WINDOW_H
#define IMAGE_WINDOW_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

//#include "KinectImageFrameRecipient.h"
#include "DragRect.h"
//#include "KinectFrame.h"
#include "LayoutElement.h"
//#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <opencv/cv.h>

#include <map>

using namespace std;

struct FrameDesc;
class LayoutContainer;

class ImageWindow :
	public LayoutElement
	, public TypeRecipient<cv::Mat>
	//, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<pair<int, int>>
	, public TypeBroadcaster<DragRect> {
public:
	ImageWindow(LayoutContainer *parent, int w, int h, string name,
		double xClickMultiplier = 1.0, double yClickMultiplier = 1.0);
	~ImageWindow();

	// LayoutElement
	GtkWidget *getWidget();
	
	//public TypeBroadcaster<cv::Mat *>::TypeRecipient
	void processType(cv::Mat inObj);
	//void processType(SimplePool<KinectFrame>::PooledPtr inObj);
	void onStartup();

protected:
	LayoutContainer *_parent;
	int _x, _y, _w, _h;
	pair<int, int> _clickStart, _clickEnd;
	double _xClickMultiplier, _yClickMultiplier;
	cv::Mat _rgba;

	GtkWidget *_image;
	GdkPixbuf *_pixbuf;

	pthread_mutex_t _mutex;
};

#endif
