#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/Calculate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		Calculate calc;

		TEST_METHOD(Add)//��
		{
			int a = rand();
			int b = rand();
			int exp = a + b;
			int ret = calc.Add(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Subtract)//��
		{
			int a = rand();
			int b = rand();
			int exp = a - b;
			int ret = calc.Subtract(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Multiply)//��
		{
			int a = rand();
			int b = rand();
			int exp = a * b;
			int ret = calc.Multiply(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Divide)//��
		{
			int a = rand();
			int b = rand();
			int exp = a / b;
			int ret = calc.Divide(a, b);
			Assert::AreEqual(exp, ret);
		}
		TEST_METHOD(Mod)//����
		{
			int a = rand();
			int b = rand();
			int exp = a % b;
			int ret = calc.Mod(a, b);
			Assert::AreEqual(exp, ret);
		}
	};
}
