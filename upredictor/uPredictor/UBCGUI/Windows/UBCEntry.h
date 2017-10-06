#ifndef UBC_ENTRY_H
#define UBC_ENTRY_H

//#include "IntegerIndicatorListener.h"
//#include "IntValueArrayListener.h"
#include "LayoutElement.h"
#include "TypeRecipient.h"

#include <map>
#include <memory>
#include <string>

using namespace std;

class IntValueArray;
class LayoutContainer;

class UBCEntry :
	public LayoutElement
	//, public IntegerIndicatorListener
	//, public IntValueArrayListener 
	, public TypeRecipient<long>
	, public TypeRecipient<double>
{
public:
	UBCEntry(
		wstring text, LayoutContainer *parent, bool entry, int w, int h = 25);
	~UBCEntry();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	void setTextD(double d, int precision = 1);
	void setTextI(long i);

	wstring getTextW();
	string getTextS();
	double getTextD();

	//void updateII(IntegerIndicator *ii);

	//void updateIVAL(IntValueArray *iva, int index, int value, void *origin);
	//void setIVAIndex(int index);
	//0, 1, 2
	//void listenToIVA(IntValueArray *iva, int index, int minValMax);

	void processType(double t);
	void processType(long t);
	void TypeRecipient<double>::onStartup() {}
	void TypeRecipient<long>::onStartup() {}

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static WNDCLASSW _wc;
	static map<HWND, UBCEntry *> _hcb;
	static bool _initialized;

	wstring _text;
	LayoutContainer *_parent;
	int _x, _y, _w, _h;// , _ivaIndex, _minValMax;
	bool _valIsStored;
	HWND _hwnd, _hwndE;
};

#endif