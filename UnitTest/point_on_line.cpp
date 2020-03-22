#include "CppUnitTest.h"
#include "../core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2 {
	TEST_CLASS(point_is_on_line)
	{
	public:
		//L and L
		TEST_METHOD(on_radial)
		{
			Line l1('L', 6, 4, 14, 10);
			Point p1(-2, -2);
			Point p2(6, 4);
			Point p3(11.76, 8.32);
			Point p4(14, 10);
			Point p5(15.28, 10.96);
			Assert::AreEqual(isOnRadial(p1, l1), false);
			Assert::AreEqual(isOnRadial(p2, l1), true);
			Assert::AreEqual(isOnRadial(p3, l1), true);
			Assert::AreEqual(isOnRadial(p4, l1), true);
			Assert::AreEqual(isOnRadial(p5, l1), true);
		}
		
		TEST_METHOD(on_segment) {
			Line l1('L', 6, 4, 14, 10);
			Point p1(-2, -2);
			Point p2(6, 4);
			Point p3(11.76, 8.32);
			Point p4(14, 10);
			Point p5(15.28, 10.96);
			Assert::AreEqual(isOnSegment(p1, l1), false);
			Assert::AreEqual(isOnSegment(p2, l1), true);
			Assert::AreEqual(isOnSegment(p3, l1), true);
			Assert::AreEqual(isOnSegment(p4, l1), true);
			Assert::AreEqual(isOnSegment(p5, l1), false);
		}
	};
}