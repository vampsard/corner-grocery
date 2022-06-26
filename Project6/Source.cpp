#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
std::strcpy(procname, proc.c_str());

char* paramval = new char[param.length() + 1];
std::strcpy(paramval, param.c_str());


PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
// Initialize the Python Interpreter
Py_Initialize();
// Build the name object
pName = PyUnicode_FromString((char*)"PythonCode");
// Load the module object
pModule = PyImport_Import(pName);
// pDict is a borrowed reference 
pDict = PyModule_GetDict(pModule);
// pFunc is also a borrowed reference 
pFunc = PyDict_GetItemString(pDict, procname);
if (PyCallable_Check(pFunc))
{
	pValue = Py_BuildValue("(z)", paramval);
	PyErr_Print();
	presult = PyObject_CallObject(pFunc, pValue);
	PyErr_Print();
}
else
{
	PyErr_Print();
}
//printf("Result is %d\n", _PyLong_AsInt(presult));
Py_DECREF(pValue);
// Clean up
Py_DECREF(pModule);
Py_DECREF(pName);
// Finish the Python Interpreter
Py_Finalize();

// clean 
delete[] procname;
delete[] paramval;


return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int menu() {//takes choice in menu
	int x;
	cout << "make your choice" << endl;
	cout << "1:Count all Items" << endl;
	cout << "2:Count specific Item" << endl;
	cout << "3:Count all Items and put in File" << endl;
	cout << "4:End Program" << endl;
	cin >> x;
	while ((!(cin)) || ((x > 4) || (x < 1))) {//check if x is a valid number
		cin.clear();//Clear error flags
		cin.ignore(1000, '\n');//allows cin to be used again
		cout << "Please type in a number between 1 and 4" << endl;
		cin >> x;
	}
	return x;
}

void one() {
//	callIntFunc("readFile", "C:/Users/Erik/source/repos/Project6/items.txt");
	callIntFunc("readFile", "items.txt");
}

void two() {
	string item;
	cout << "which item do you want to  count: ";
	cin >> item;//takes user input for item to be counted
	int num;
	num= callIntFunc("specItem", item);//count specific item
	cout << "The number of " << item << " was " << num << endl;//prints item and number
}

void three() {
	string s = "frequency.dat";
	int count;//used to stop the for loop when file is empty
	count = callIntFunc("makeFile",s);//makes file to be read 
	ifstream myFile(s);//open file
	string myString;
	cout << endl;
	if (myFile.is_open()) { //check whether the file is open
		for(int i =0;i<count;i++){//tell when to stop reading the file
			myFile >> myString; //get item from file
			int leng = myString.length();//used for formatting
			leng = 12 - leng;
			string space = "";
			for (int i = 0;i <= leng;i++) {
				space = space + " ";
			}
			cout << myString;
			cout << space;
			myFile >> myString; // get number from file
			int x = stoi(myString);
			cout << " ";
			for (int i = 0;i < x;i++) {//print specific number of *
				cout << "*";
			}
			cout << endl;
		}
	}
	myFile.close();
}

void main()
{
	int x = menu();//gets choice
	cout << "your choice was " << x << endl;
	if (x == 1) {
		one();//count all items from txt file 
	}
	if (x == 2) {
		two();//count specific item
	}
	if (x == 3) {
		three();//count items and put them in a dat file to be read in c++
	}
	if (x == 4) {
		cout << "Ending Program\n";
	}
}
