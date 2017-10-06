#ifndef RANGE_INTERFACE_H
#define RANGE_INTERFACE_H

#include "ColumnLayout.h"
#include "RowLayout.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "SimpleLabeledComboBox.h"
#include "TypeRecipient.h"
#include "UBCEntry.h"

using namespace std;

class ImageWindow;

class RangeInterface :
	public LayoutElement
	//, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeRecipient<pair<int, int>>
{

public:
	RangeInterface(
		LayoutContainer *parent
		, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
		);
	~RangeInterface();

	//public LayoutElement
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	pair<int, int> getCoords();
	
	//public TypeRecipient<pair<int, int>>
	void processType(pair<int, int> t);

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	//void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	
	ColumnLayout _cl;
	RowLayout _rl;
	UBCEntry _xL, _xE;
	UBCEntry _yL, _yE;
	UBCEntry _zL, _zE;
	pair<int, int> _coords;
};

#endif