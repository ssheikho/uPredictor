#include "ImageWindow.h"
#include "LayoutContainer.h"

//#include <opencv2/highgui/highgui.hpp>

#ifdef _WIN32
#include <windowsx.h>
#endif

ImageWindow::ImageWindow(
	LayoutContainer *parent
	, int w, int h
	, string name
	, double xClickMultiplier, double yClickMultiplier) :
	_parent(parent)
	, _x(0), _y(0)
	,_w(w), _h(h)
	, _clickStart(pair<int,int>(0,0)), _clickEnd(pair<int, int>(0, 0))
	, _xClickMultiplier(xClickMultiplier)
	, _yClickMultiplier(yClickMultiplier)
	, _rgba(_h, _w, CV_8UC3)
{
	pthread_mutex_init(&_mutex, NULL);
	_image = gtk_image_new();

	// Convert cv::Mat to GdkPixbuf
	_pixbuf = gdk_pixbuf_new_from_data(
		     _rgba.data, GDK_COLORSPACE_RGB, false, 8,
		     _w, _h
			//, 4
			, _rgba.step
			, NULL, NULL);

	parent->addChild(this);

	//cv::namedWindow("Display window", CV_WINDOW_AUTOSIZE);
}

ImageWindow::~ImageWindow() {
	gtk_widget_destroy(_image);
}

GtkWidget *ImageWindow::getWidget() {
	return _image;
}

void ImageWindow::processType(cv::Mat inObj) {
	pthread_mutex_lock(&_mutex);
	//cout << "OMFG" << endl;
	// Swap color channels to RGB
	//cv::cvtColor(inObj, _rgba, CV_BGRA2RGB);
	inObj.copyTo(_rgba);
	//memcpy(_rgba.data, inObj.data, _h * _w * 3 * sizeof(char));
	//cout << "_h:	" << _h << "	" << _w << endl;

	// Render image using pixbuf
	gtk_image_set_from_pixbuf(GTK_IMAGE(_image), _pixbuf);

	//imshow("Display window", _rgb);
	pthread_mutex_unlock(&_mutex);
}

/*
void ImageWindow::processType(SimplePool<KinectFrame>::PooledPtr inObj) {
	pthread_mutex_lock(&_mutex);
	//cv::cvtColor(inObj->_depthBGRA, _rgba, CV_BGRA2RGB);
	inObj->_depthRGB.copyTo(_rgba);
	gtk_image_set_from_pixbuf(GTK_IMAGE(_image), _pixbuf);
	pthread_mutex_unlock(&_mutex);
}
*/

void ImageWindow::onStartup() {}
