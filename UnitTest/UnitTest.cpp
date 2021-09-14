#include "pch.h"
#include "CppUnitTest.h"

#include "Vector2d.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector2dTests
{
	TEST_CLASS(Initializers)
	{
	public:

		TEST_METHOD(initList)
		{
			Vector2d vec = { 10.0f, 12.0f };
			Assert::AreEqual(10.0f, vec.x);
			Assert::AreEqual(12.0f, vec.y);
		}

		TEST_METHOD(initConstructor)
		{
			Vector2d vec = Vector2d(10.0f, 12.0f);
			Assert::AreEqual(10.0f, vec.x);
			Assert::AreEqual(12.0f, vec.y);
		}

		TEST_METHOD(defaultConstructor)
		{
			Vector2d vec;
			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);
		}

		TEST_METHOD(reassignment1)
		{
			Vector2d vec = Vector2d(100.0f, 200.0f);

			vec = Vector2d(3.0f, 4.0f);
			Assert::AreEqual(3.0f, vec.x);
			Assert::AreEqual(4.0f, vec.y);
		}

		TEST_METHOD(reassignment2)
		{
			Vector2d vec;

			vec = Vector2d(3.0f, 4.0f);
			Assert::AreEqual(3.0f, vec.x);
			Assert::AreEqual(4.0f, vec.y);
		}
	};

	TEST_CLASS(Functions)
	{
	public:

		TEST_METHOD(cross)
		{
			Vector2d vec1 = Vector2d(1.0f, 2.0f);
			Vector2d vec2 = Vector2d(4.0f, 1.0f);

			Assert::AreEqual(-7.0f, Cross(vec1, vec2));
		}

		TEST_METHOD(dot)
		{
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);

			Assert::AreEqual(11.0f, Dot(vec1, vec2));

			vec1 = Vector2d(-12.0f, 13.0f);
			vec2 = Vector2d(66.0f, 45.0f);

			Assert::AreEqual(-207.0f, Dot(vec1, vec2));
		}
	};

	TEST_CLASS(Operators)
	{
	public:

		TEST_METHOD(add1)
		{
			// vec1 should not have changed
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);

			Vector2d vec3 = vec1 + vec2;

			Assert::AreEqual(4.0f, vec1.x);
			Assert::AreEqual(1.0f, vec1.y);
		}

		TEST_METHOD(add2)
		{
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);

			Vector2d vec3 = vec1 + vec2;

			Assert::AreEqual(6.0f, vec3.x);
			Assert::AreEqual(4.0f, vec3.y);
		}

		TEST_METHOD(add3)
		{
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);

			vec1 += vec2;

			Assert::AreEqual(6.0f, vec1.x);
			Assert::AreEqual(4.0f, vec1.y);
		}

		TEST_METHOD(float1)
		{
			Vector2d vec = Vector2d(4.0f, 1.0f);
			float val = 2.0f;

			Vector2d result = vec + val;

			Assert::AreEqual(6.0f, result.x);
			Assert::AreEqual(3.0f, result.y);
		}

		TEST_METHOD(float2)
		{
			Vector2d vec = Vector2d(4.0f, 1.0f);
			float val = 2.0f;

			vec += val;

			Assert::AreEqual(6.0f, vec.x);
			Assert::AreEqual(3.0f, vec.y);
		}

		TEST_METHOD(sub1)
		{
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);

			vec1 -= vec2;

			Assert::AreEqual(2.0f, vec1.x);
			Assert::AreEqual(-2.0f, vec1.y);
		}

		TEST_METHOD(comparison)
		{
			Vector2d vec1 = Vector2d(4.0f, 1.0f);
			Vector2d vec2 = Vector2d(2.0f, 3.0f);
			Vector2d vec3 = Vector2d(4.0f, 1.0f);

			Assert::IsTrue(vec1 == vec1);
			Assert::IsTrue(vec1 == vec3);
			Assert::IsTrue(vec1 != vec2);
			Assert::IsFalse(vec1 == vec2);
		}
	};
}
