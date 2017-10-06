#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include <tchar.h>

//#include "RandomSphere.cuh"

int doCudaAdd();

//int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
//	_In_ int nCmdShow) {
int main(int argc, char **argv) {
	return doCudaAdd();
}

