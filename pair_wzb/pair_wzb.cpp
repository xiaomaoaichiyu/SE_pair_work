#include "../core/core.h"
#include <iostream>
#include <sstream>
#include<Windows.h>

using namespace std;

//extern "C" __declspec(dllimport) void Clear();

//extern "C" __declspec(dllimport) void AddLine(int x1, int y1, int x2, int y2);

//extern "C" __declspec(dllimport) int GetIntersectionSize();


bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}

int main(int argc, char** argv) {
	//AddLine(0, 0, 1, 1);
	//AddLine(1, 1, 1, 0);
	//int num = GetIntersectionSize();
	typedef void(*ADD)(int x1, int y1, int x2, int y2);
	typedef int(*GetNum)();
	typedef void(*ADDCIRCLE)(int x, int y, int r);
	typedef void(*Getdian)(double* x, double*y, int size);
	HMODULE hMod = LoadLibrary(L"intersect_core.dll");
	ADD addAline = (ADD)GetProcAddress(hMod, "AddLine");
	ADD addAradial = (ADD)GetProcAddress(hMod, "AddRay");
	ADD addAsegment = (ADD)GetProcAddress(hMod, "AddSection");
	ADDCIRCLE addAcircle = (ADDCIRCLE)GetProcAddress(hMod, "AddCircle");
	GetNum getInSize = (GetNum)GetProcAddress(hMod, "GetIntersectionsSize");
	Getdian getDian = (Getdian)GetProcAddress(hMod, "GetIntersections");

	addAcircle(2, 2, 3);
	addAcircle(2, 3, 4);
	int num = getInSize();
	double x[2];
	double y[2];
	getDian(x, y, 1);

	string inFileName = "";
	string outFileName = "";
	int flag = 0;
	if (argc > 5) {
		cerr << "Too Many Arguements!!" << endl;
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'i') {
				inFileName = argv[i + 1];
				flag++;
			}
			else if (argv[i][1] == 'o') {
				outFileName = argv[i + 1];
				flag++;
			}
			else {
				cerr << "Wrong Arguement!!" << endl;
				return 0;
			}
		}
	}
	if (flag != 2) {
		cerr << "Too Few Arguements!!" << endl;
		return 0;
	}

	ifstream fileIn(inFileName, ios::in);
	ofstream fileOut(outFileName, ios::out);

	if (!fileIn) {
		cerr << "input file open Error!!" << endl;
		return 0;
	}

	if (!fileOut) {
		cerr << "output file open Error!!" << endl;
		return 0;
	}

	int lineNum = 0;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, r = 0;
	char mark;
	string tmp = "";
	getline(fileIn, tmp);
	if (!isNum(tmp)) {
		cerr << "Please Input N!!" << endl;
		return 0;
	}
	stringstream ss;
	ss << tmp;
	ss >> lineNum;
	for (int i = 0; i < lineNum; i++) {
		getline(fileIn, tmp);
		stringstream tmps;
		tmps << tmp;
		tmps >> mark;
		if (mark >= 'a' && mark <= 'z') {
			cerr << "Please Use Capiter Letter!!" << endl;
			return 0;
		}
		else if (mark < 'A' || mark > 'Z') {
			cerr << "Please Input Type!!" << endl;
			return 0;
		}
		if (mark == 'L' || mark == 'R' || mark == 'S') {
			stringstream nums;
			for (int i = 0; i < 4; i++) {
				tmp = "";
				tmps >> tmp;
				nums << tmp + " ";
				if (tmp == "") {
					cerr << "Too Few Messages!!" << endl;
					return 0;
				}
				else if (!isNum(tmp)) {
					cerr << "Please Input a Interger!!" << endl;
					return 0;
				}
			}
			tmp = "";
			tmps >> tmp;
			if (tmp != "") {
				cerr << "Too Many Messages!!" << endl;
				return 0;
			}
			nums >> x1 >> y1 >> x2 >> y2;
			if (x1 >= 100000 || x1 <= -100000 || y1 >= 100000 || y1 <= -100000 || x2 >= 100000 || x2 <= -100000 || y2 >= 100000 || y2 <= -100000) {
				cerr << "Out Of Bound!!" << endl;
				return 0;
			}
			if (x1 == x2 && y1 == y2) {
				cerr << "Two Points Coincide!!" << endl;
				return 0;
			}
			addLine(mark, x1, y1, x2, y2);
			if (mark == 'L') {
				addAline(x1, y1, x2, y2);
			}
			else if (mark == 'R') {
				addAradial(x1, y1, x2, y2);
			}
			else if (mark == 'S') {
				addAsegment(x1, y1, x2, y2);
			}
		}
		else if (mark == 'C') {
			stringstream nums;
			for (int i = 0; i < 3; i++) {
				tmp = "";
				tmps >> tmp;
				nums << tmp + " ";
				if (tmp == "") {
					cerr << "Too Few Messages!!" << endl;
					return 0;
				}
				else if (!isNum(tmp)) {
					cerr << "Please Input a Num!!" << endl;
					return 0;
				}
			}
			tmp = "";
			tmps >> tmp;
			if (tmp != "") {
				cerr << "Too Many Messages!!" << endl;
				return 0;
			}

			nums >> x1 >> y1 >> r;
			if (x1 >= 100000 || x1 <= -100000 || y1 >= 100000 || y1 <= -100000 || r >= 100000 || r <= -100000) {
				cerr << "Out Of Bound!!" << endl;
				return 0;
			}
			if (r <= 0) {
				cerr << "Radius Must Be Greater Than Zero!!" << endl;
			}
			addCircle(x1, y1, r);
			addAcircle(x1, y1, r);
		}
	}
	fileIn.close();

	int res = getResultOfIntersect();
	int res1 = getInSize();
	if (fileOut) {
		fileOut << res;
	}
	cout << res << " " << res1 << endl;
	return 0;
}