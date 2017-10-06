#include "NumberInfoList.h"
#include "UBCEntry.h"

NumberInfoList::NumberInfoList(
	LayoutContainer *parent
	, int labelW
	, int dataW
	, int rowH
	) :
	_labelW(labelW)
	, _dataW(dataW)
	, _rowH(rowH)
	, _gl(parent, _labelW + _dataW, rowH)
{}

NumberInfoList::~NumberInfoList() {}

void NumberInfoList::addLongLabel(wstring label, TypeBroadcaster<long> *tb) {
	_gl.addRow();

	UBCEntry *l = new UBCEntry(label, &_gl, false, _labelW, _rowH);
	UBCEntry *d = new UBCEntry(L"", &_gl, true, _dataW, _rowH);

	tb->addRecipient(d);

	//_gl.addChild(l);
	//_gl.addChild(d);

	_l.push_back(l);
	_d.push_back(d);
}

void NumberInfoList::addDoubleLabel(wstring label, TypeBroadcaster<double> *tb) {
	_gl.addRow();

	UBCEntry *l = new UBCEntry(label, &_gl, false, _labelW, _rowH);
	UBCEntry *d = new UBCEntry(L"", &_gl, true, _dataW, _rowH);

	tb->addRecipient(d);

	//_gl.addChild(l);
	//_gl.addChild(d);

	_l.push_back(l);
	_d.push_back(d);
}