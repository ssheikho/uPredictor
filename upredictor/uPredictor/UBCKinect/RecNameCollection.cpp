#include "RecNameCollection.h"
#include "UBCUtil.h"

RecNameCollection::RecNameCollection(wstring directory) :
_directory(directory) {}

RecNameCollection::~RecNameCollection() {}

wstring RecNameCollection::getDirectory() {
	return _directory;
}

wstring RecNameCollection::getIDFilename() {
	return _directory + L"ids.dat";
}

wstring RecNameCollection::getDefaultAnnotationFilename() {
	return _directory + L"annotations.bin";
}

wstring RecNameCollection::getCamFilename(int index) {
	return _directory + L"\\cam_" + intToWString(index) + L".avi";
}

wstring RecNameCollection::get3DFilename(int index) {
	return _directory + L"\\depth_" + intToWString(index) + L".dat";
}

wstring RecNameCollection::getSkeTimeFilename(int index) {
	return _directory + L"\\skel_" + intToWString(index) + L".dat";
}

string RecNameCollection::getDirectoryS() {
	wstring ws = getDirectory();
	return std::string(ws.begin(), ws.end());
}

string RecNameCollection::getIDFilenameS() {
	wstring ws = getIDFilename();
	return std::string(ws.begin(), ws.end());
}

string RecNameCollection::getDefaultAnnotationFilenameS() {
	wstring ws = getDefaultAnnotationFilename();
	return std::string(ws.begin(), ws.end());
}

string RecNameCollection::getCamFilenameS(int index) {
	wstring ws = getCamFilename(index);
	return std::string(ws.begin(), ws.end());
}

string RecNameCollection::get3DFilenameS(int index) {
	wstring ws = get3DFilename(index);
	return std::string(ws.begin(), ws.end());
}

string RecNameCollection::getSkeTimeFilenameS(int index) {
	wstring ws = getSkeTimeFilename(index);
	return std::string(ws.begin(), ws.end());
}

void RecNameCollection::setDirectory(wstring directory) {
	_directory = directory;
}
