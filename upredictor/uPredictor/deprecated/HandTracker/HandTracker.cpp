#include <WinSock2.h>
#include <Windows.h>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <fstream>
#include <iostream>

//#include <tchar.h>

using namespace std;
//
//int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
//	_In_ int nCmdShow) {
int main(int argc, char **argv) {

	Py_Initialize();

	// import the module 
	PyObject* myModuleString = PyString_FromString((char*)"test");
	PyObject* myModule = PyImport_Import(myModuleString);

	//getting a reference to the function 
	PyObject* function = PyObject_GetAttrString(myModule, (char*)"myabs");
	PyObject* args = PyTuple_Pack(1, PyFloat_FromDouble(-2.0));

	PyObject* presult = PyObject_CallObject(function, args);
	double result = PyFloat_AsDouble(presult);
	while(true)
	cout << result << endl;


	// Finish the Python Interpreter
	Py_Finalize();

	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();

	exit(EXIT_SUCCESS);
}
