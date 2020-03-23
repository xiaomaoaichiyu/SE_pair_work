#include "CppUnitTest.h"
#include "../core/core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4 {
	TEST_CLASS(cirlce_circle_intersect)
	{
	public:
		TEST_METHOD(Test_getCircleCross1) {
			//相交，外交
			Point p(1.25, 0.9682458365519);
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 0, 1, 3, 0, 2, x, y);
			Assert::IsTrue(num == 2);
		}
		TEST_METHOD(Test_getCircleCross2) {
			//相交，内交
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(2, 0, 2, 3, 0, 2, x, y);
			Assert::IsTrue(num == 2);
		}
		TEST_METHOD(Test_getCircleCross3) {
			//相切，外切
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 0, 1, 3, 0, 1, x, y);
			Assert::IsTrue(num == 1);
		}
		TEST_METHOD(Test_getCircleCross4) {
			//相切，内切
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 0, 1, 2, 0, 2, x, y);
			Assert::IsTrue(num == 1);
		}
		TEST_METHOD(Test_getCircleCross5) {
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 0, 1, 8, 0, 2, x, y);
			Assert::IsTrue(num == 0);
		}
		TEST_METHOD(Test_getCircleCross6) {
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(3, 0, 1, 3, 0, 2, x, y);
			Assert::IsTrue(num == 0);
		}
		TEST_METHOD(Test_getCircleCross7) {
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 1, 1, 1, 3, 2, x, y);
			Assert::IsTrue(num == 2);
		}
		TEST_METHOD(Test_getCircleCross8) {
			double* x = new double();
			double* y = new double();
			int num = cirWithcir(1, 1, 2, 2, 2, 2, x, y);
			Assert::IsTrue(num == 2);
		}

		TEST_METHOD(circle_circle1) {
			resetRes();
			addCircle(1, 1, 1);
			addCircle(1, 3, 2);
			addCircle(3, 5, 3);

			int num = getResultOfIntersect();

			Assert::IsTrue(num == 4);
		}

		TEST_METHOD(circle1) {
			Circle c1(1, 1, 1);
			Circle c2(1, 1, 1);
			Assert::IsTrue(c1 == c2);

			resetRes();
			addCircle(1, 1, 1);
			delCircle(1, 1, 1);
		}
	};
}