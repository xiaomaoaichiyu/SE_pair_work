#include "CppUnitTest.h"
#include "../core/core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest5 {
	TEST_CLASS(exception)
	{
	public:
		TEST_METHOD(lineisSame) {
			try {
				resetRes();
				addLine('L', 0, 0, 1, 1);
				addLine('L', 1, 1, 2, 2);
			}
			catch (const std::string& e){
				Assert::IsTrue(e == "Line is same with before one!");
			}
		}

		TEST_METHOD(line_Radial) {
			try {
				resetRes();
				addLine('L', 0, 0, 1, 1);
				addLine('R', 2, 2, 3, 3);
			}
			catch (const string& e){
				Assert::IsTrue(e == "Line is same with before one!");
			}
		}

		TEST_METHOD(radial_radial) {
			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('R', -1, -1, 2, 2);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('R', 0, 0, 1, 1);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('R', 1, 1, 0, 0);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('R', 0, 0, 1, 1);
				int num = getResultOfIntersect();
				Assert::IsTrue(num == 1);
			}
			catch (const string& e) {
				cerr << e << endl;
			}
		}

		TEST_METHOD(radial_segment) {
			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('S', 0, 0, 1, 1);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('S', -1, -1, 1, 1);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('S', -1, -1, 0, 0);

				int num = getResultOfIntersect();

				Assert::IsTrue(num == 1);
			}
			catch (const string& e) {
				cerr << e << endl;
			}

			try {
				resetRes();
				addLine('R', 0, 0, 2, 2);
				addLine('S', 2, 2, 3, 3);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}
		}

		TEST_METHOD(segment_segment) {
			try {
				resetRes();
				addLine('S', 0, 0, 3, 3);
				addLine('S', 2, 2, 3, 3);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('S', 0, 0, 3, 3);
				addLine('S', -1, -1, 1, 1);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}

			try {
				resetRes();
				addLine('S', 0, 0, 3, 3);
				addLine('S', -1, -1, 3, 3);
			}
			catch (const string& e) {
				Assert::IsTrue(e == "Line is same with before one!");
			}
		}
	};
}