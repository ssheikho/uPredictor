#ifndef REC_NAME_COLLECTION_H
#define REC_NAME_COLLECTION_H

#include <string>

using namespace std;

class RecNameCollection {
public:
	RecNameCollection(wstring directory);
	~RecNameCollection();

	wstring getDirectory();
	wstring getIDFilename();
	wstring getDefaultAnnotationFilename();
	wstring getCamFilename(int index);
	wstring get3DFilename(int index);
	wstring getSkeTimeFilename(int index);

	string getDirectoryS();
	string getIDFilenameS();
	string getDefaultAnnotationFilenameS();
	string getCamFilenameS(int index);
	string get3DFilenameS(int index);
	string getSkeTimeFilenameS(int index);

	void setDirectory(wstring directory);

protected:
	wstring _directory;
};

#endif
