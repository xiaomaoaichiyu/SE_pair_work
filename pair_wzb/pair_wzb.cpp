#include "../core/core.h"
#include <iostream>
#include <sstream>

using namespace std;

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
	addLine('S', 2, 4, 3, 2);
	addLine('L', -1, 4, 5, 2);
	addLine('R', 2, 5, -1, 2);
	addCircle(3, 3, 3);

	int num = getResultOfIntersect();



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
		}
	}
	fileIn.close();

	int res = getResultOfIntersect();
	if (fileOut) {
		fileOut << res;
	}
	cout << res << endl;
	return 0;
}