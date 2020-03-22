#include "CppUnitTest.h"
#include "../core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
	TEST_CLASS(line_circle_intersect)
	{
	public:
		TEST_METHOD(Test_CircleLineCross1) {
			//相交
			//'L'
			Circle c(2, 2, 1);
			Line l('L', 0, 0, 1, 1);
			Point p1(1.2928932188135, 1.2928932188135);
			Point p2(2.7071067811865, 2.7071067811865);
			Point res1;
			Point res2;
			Assert::IsTrue(line2circle(c, l, res1, res2) == 2);
			Assert::IsTrue(res1 == p1);
			Assert::IsTrue(res2 == p2);

			//'R'
			Line l1('R', 1.5, 2.5, 2.5, 1.5);
			Point p3(2.7071067811865, 1.2928932188135);
			Assert::IsTrue(line2circle(c, l1, res1, res2) == 1);
			Assert::IsTrue(res1 == p3);
			Line l2('R', 3, 1, 3.5, 0.5);
			Assert::IsTrue(line2circle(c, l2, res1, res2) == 0);

			//'S'
			Line l3('S', 2.5, 1.5, 3, 1);
			Assert::IsTrue(line2circle(c, l3, res1, res2) == 1);
			Assert::IsTrue(res1 == p3);
		}


		TEST_METHOD(Test_CircleLineCross3) {
			//相切
			Circle c(5, 0, 3);
			Line l('L', 0, 0, 4, 3);
			Point p(3.2, 2.4);
			Point res1;
			Point res2;
			Assert::IsTrue(line2circle(c, l, res1, res2) == 1);
			Assert::IsTrue(res1 == p);
			
			Line l1('R', 4, 3, 8, 6);
			Assert::IsTrue(line2circle(c, l1, res1, res2) == 0);
			
			Line l2('S', 0, 0, 4, 3);
			Assert::IsTrue(line2circle(c, l2, res1, res2) == 1);
		}

		TEST_METHOD(Test_CircleLineCross4) {
			//不相交
			Circle c(5, 0, 3);
			Line l('S', 5, 1, 4, 0);
			Point res1;
			Point res2;
			Assert::IsTrue(line2circle(c, l, res1, res2) == 0);

			Line l1('L', 3, 4, 2, 3);
			Assert::IsTrue(line2circle(c, l1, res1, res2) == 0);

			Line l2('R', 3, 4, 2, 3);
			Assert::IsTrue(line2circle(c, l, res1, res2) == 0);
		}

		TEST_METHOD(line_circle1) {
			resetRes();
			addLine('S', 2, 4, 3, 2);
			addLine('L', -1, 4, 5, 2);
			addLine('R', 2, 5, -1, 2);
			addCircle(3, 3, 3);

			int num = getResultOfIntersect();

			Assert::IsTrue(num == 5);
		}

	};
}
