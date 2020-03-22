#include "CppUnitTest.h"
#include "../pair_wzb/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(line_line_intersect)
	{
	public:
		//L and L
		TEST_METHOD(L_L_true)
		{
			Line l1('L', -2, 4, 3, 5);
			Line l2('L', 9, -2, 6, 4);
			Point p(5.272727272727273, 5.45454545454545455);
			double* x = new double();
			double* y = new double();
			int num = lWithl('L', -2, 4, 3, 5, 'L', 9, -2, 6, 4, x, y);
			Assert::IsTrue(num == 1);
			Point res(*x, *y);
			Assert::IsTrue(p == res);
		}

		TEST_METHOD(L_L_false) {
			Line l1('L', 0, 0, 5, 5);
			Line l2('L', 5, 0, 0, -5);
			//Point p(5.272727272727273, 5.45454545454545455);
			Point res;
			double* x = new double();
			double* y = new double();
			int num = lWithl('L', 0, 0, 5, 5, 'L', 5, 0, 0, -5, x, y);
			Assert::IsTrue(num == 0);
			//Assert::AreEqual(p, res);
		}

		//L and R
		TEST_METHOD(L_R_true) {
			Line l1('L', -2, 4, 3, 5);
			Line l2('R', -4, 0, 0, 2);
			Point p(8, 6);
			Point res;
			double* x = new double();
			double* y = new double();
			int num = lWithl('L', -2, 4, 3, 5, 'R', -4, 0, 0, 2, x, y);
			Assert::IsTrue(num == 1);

			//revert
			num = lWithl('R', -4, 0, 0, 2, 'L', -2, 4, 3, 5, x, y);
			Assert::IsTrue(num == 1);
		}

		TEST_METHOD(L_R_false) {
			Line l1('L', -2, 4, 3, 5);
			Line l2('R', -4, 0, 2, -2);
			//Point p(5.272727272727273, 5.45454545454545455);
			Point res;
			double* x = new double();
			double* y = new double();
			int num = lWithl('L', -2, 4, 3, 5, 'R', -4, 0, 2, -2, x, y);
			Assert::IsTrue(num == 0);
			//Assert::AreEqual(p, res);
		}

		//L and S
		TEST_METHOD(L_S_true) {
			Line l1('L', -2, 4, 3, 5);
			Line l2('S', 4, 8, 8, 2);
			Point p(5.6470588235294, 5.5294117647059);
			Point res;
			//case 1
			Assert::IsTrue(line2line(l1, l2, res) != 0);
			Assert::IsTrue(p == res);
			//revert
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) != 0);
			Assert::IsTrue(p == res);

			//case 2
			Line l3('S', -2, 6, 8, 0);
			p.setPoint(0.5, 4.5);
			Assert::IsTrue(line2line(l1, l3, res) != 0);
			Assert::IsTrue(p == res);
			//revert
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l3, l1, res) != 0);
			Assert::IsTrue(p == res);
		}

		TEST_METHOD(L_S_false) {
			//case 1
			Line l1('L', -2, 4, 3, 5);
			Line l2('S', 4, 8, 8, 8);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) == 0);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) == 0);

			//case 2
			Line l3('L', -2, 4, 4, 6);
			Line l4('S', 4, 8, 10, 10);
			Assert::IsTrue(line2line(l3, l4, res) == 0);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l4, l3, res) == 0);
		}

		TEST_METHOD(R_R_true) {
			//case 1
			Line l1('R', -2, 4, 5, 10);
			Line l2('R', 4, 2, 10, 10);
			Point p(19, 22);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) != 0);
			Assert::IsTrue(p == res);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) != 0);
			Assert::IsTrue(p == res);

			//case 2
			Line l3('R', 4, 2, 2, 6);
			p.setPoint(1.5, 7);
			Assert::IsTrue(line2line(l1, l3, res) != 0);
			Assert::IsTrue(p == res);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l3, l1, res) != 0);
			Assert::IsTrue(p == res);
		}

		TEST_METHOD(R_R_false) {
			//case 1
			Line l1('R', -2, 4, 5, 10);
			Line l2('S', 4, 2, -2, 2);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) == 0);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) == 0);
		}

		TEST_METHOD(R_S_true) {
			//case 1
			Line l1('R', 2, 6, 14, 12);
			Line l2('S', 6, 12, 14, 6);
			Point p(9.2, 9.6);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) != 0);
			Assert::IsTrue(p == res);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) != 0);
			Assert::IsTrue(p == res);

			//case 2
			Line l3('R', 2, 6, 14, 12);
			Line l4('S', 16, 16, 14, 6);
			p.setPoint(15.3333333333333333, 12.6666666666666667);
			Assert::IsTrue(line2line(l3, l4, res) != 0);
			Assert::IsTrue(p == res);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l4, l3, res) != 0);
			Assert::IsTrue(p == res);
		}

		TEST_METHOD(R_S_false) {
			//case 1
			Line l1('R', 2, 6, 14, 12);
			Line l2('S', -2, 8, 2, 4);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) == 0);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) == 0);
			//case 2
			Line l3('S', 2, 12, 4, 10);
			Assert::IsTrue(line2line(l1, l3, res) == 0);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l3, l1, res) == 0);
		}

		TEST_METHOD(S_S_true) {
			//case 1
			Line l1('S', -2, 4, 2, 8);
			Line l2('S', -2, 8, 2, 4);
			Point p(0, 6);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) != 0);
			Assert::IsTrue(p == res);
			res.setPoint(0, 0);
			Assert::IsTrue(line2line(l2, l1, res) != 0);
			Assert::IsTrue(p == res);
		}

		TEST_METHOD(S_S_false) {
			//case 1
			Line l1('S', 2, 6, 8, 10);
			Line l2('S', 2, 10, 4, 8);
			Point res;
			Assert::IsTrue(line2line(l1, l2, res) == 0);
			Assert::IsTrue(line2line(l2, l1, res) == 0);

			Line l3('S', -2, 10, 0, 6);

			Assert::IsTrue(line2line(l1, l3, res) == 0);
			Assert::IsTrue(line2line(l3, l1, res) == 0);
		}

		TEST_METHOD(line_with_line) {
			addLine('S', -1, 3, 2, -1);
			addLine('L', -2, 2, 3, 0);
			addLine('R', -3, 0, 4, 2);

			linesIntersect();

			int num = getResultOfIntersect();

			Assert::IsTrue(1 == num);
		}

		TEST_METHOD(line_with_line2) {
			resetRes();
			addLine('L', 91598, 51695, -292, 76595);
			addLine('L', 91040, -72215, -66266, 41547);
			addLine('L', 79726, 64976, -47232, -59439);
			addLine('L', -60802, -86271, 15560, 68129);
			addLine('L', -18061, 96085, 98631, 76823);

			int num = getResultOfIntersect();
			
			Assert::IsTrue(num == 10);
		}

		TEST_METHOD(line) {
			Line l1('L', 1, 1, 2, 2);
			Line l2('L', 1, 1, 2, 2);
			Assert::IsTrue(l1 == l2);

			resetRes();
			addLine('L', 1, 1, 2, 2);
			delLine('L', 1, 1, 2, 2);
		}
	};
}
