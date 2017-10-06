#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "UBCColorTrackerCUDA.h"
//#pragma comment(lib, "UBCColorTrackCUDA.lib")

#include <tchar.h>

#include <fstream>

//#include "CudaFunctions.h"
//#include "RandomSphere.cuh"

//int doCudaAdd();

using namespace std;

/*
class MargSegClass {
public:
	MargSegClass() {}

	void doMS(unsigned char *inputImage, unsigned char *outputImage,
		struct MarginalTrackerParams *mtp) {
		doMarginalSegmentation(inputImage, outputImage, mtp);
	}
};
*/
extern "C" typedef int (CALLBACK* doMargSegType)(unsigned char *
	, unsigned char *
	, struct MarginalTrackerParams *marginalTrackerParams);


int main(int argc, char **argv) {
	typedef VOID(*DLLPROC) (LPTSTR);
	HINSTANCE hinstDLL = LoadLibrary(L"UBCColorTrackCUDA.dll");
	doMargSegType doMarginalSegmentation =
		(doMargSegType)GetProcAddress(hinstDLL, "doMarginalSegmentation");

	struct MarginalTrackerParams mtp;
	mtp._sizeII = sizeof(long);

	long a = 1024;
	long b = 2048;

	//MargSegClass msc;
	//msc.doMS((unsigned char *)&a, (unsigned char *)&b, &mtp);
	doMarginalSegmentation((unsigned char *)&a, (unsigned char *)&b, &mtp);

	//ofstream c("out.txt");
	//c << b << endl;

	return 0;
}