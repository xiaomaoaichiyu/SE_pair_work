#include "core.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	addLine('S', 2, 4, 3, 2);
	addLine('L', -1, 4, 5, 2);
	addLine('R', 2, 5, -1, 2);
	addCircle(3, 3, 3);

	int num = getResultOfIntersect();



	string inFileName = "";
	string outFileName = "";
	for (int i = 1; i < argc; i++) {
		if (i == 2) {
			inFileName = argv[2];
		}
		if (i == 4) {
			outFileName = argv[4];
		}
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
	fileIn >> lineNum;
	for (int i = 0; i < lineNum; i++) {
		fileIn >> mark;
		if (mark == 'L') {
			fileIn >> x1 >> y1 >> x2 >> y2;
			addLine(mark, x1, y1, x2, y2);
		}
		else if (mark == 'C') {
			fileIn >> x1 >> y1 >> r;
			addCircle(x1, y1, r);
		}
	}
	fileIn.close();
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	//get the intersection num of all lines
	cnt1 = linesIntersect();
	cnt2 = linesCirclesIntersect();
	cnt3 = circlesIntersect();

	int res = getResultOfIntersect();
	if (fileOut) {
		fileOut << res;
	}
	cout << res << endl;
	return 0;
}
