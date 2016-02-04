#include "stdafx.h"
#include "../Triangle.h"
#include <math.h>

using namespace std;

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, const string & expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e){
		return e.what() == expectedDescription; 
	});
}

template <typename Ex>
void ExpectConstructorFailure(double side1, double side2, double side3, const string & expectedDescription)
{
	ExpectException<Ex>([&]{
		CTriangle(side1, side2, side3); 
	}, expectedDescription);
}

void TriangleExists(double side1, double side2, double side3)
{
	BOOST_REQUIRE_NO_THROW(CTriangle(side1, side2, side3));
	CTriangle t(side1, side2, side3);
	BOOST_CHECK_EQUAL(t.GetSide1(), side1);
	BOOST_CHECK_EQUAL(t.GetSide2(), side2);
	BOOST_CHECK_EQUAL(t.GetSide3(), side3);
}

void CheckPerimeter(double side1, double side2, double side3)
{
	CTriangle const t(side1, side2, side3);
	//BOOST_CHECK_CLOSE_FRACTION(t.GetPerimeter(), side1 + side2 + side3, 1e-10);
	BOOST_CHECK_EQUAL(t.GetPerimeter(), side1 + side2 + side3);
}

void CheckArea(double side1, double side2, double side3)
{
	CTriangle const t(side1, side2, side3);
	double p = (t.GetPerimeter() / 2);
	double expectedArea = sqrt(p * (p - side1) * (p - side2) * (p - side3));
	BOOST_CHECK_EQUAL(t.GetArea(), expectedArea);
}

BOOST_AUTO_TEST_SUITE(Triangle)
	BOOST_AUTO_TEST_CASE(cannot_have_negative_sides)
	{
		ExpectConstructorFailure<invalid_argument>(-1, 2, 3, "Side 1 can not be negative.");
		ExpectConstructorFailure<invalid_argument>(1, -2, 3, "Side 2 can not be negative.");
		ExpectConstructorFailure<invalid_argument>(1, 2, -3, "Side 3 can not be negative.");
	}

	BOOST_AUTO_TEST_CASE(cannot_have_side_greater_than_sum_of_other_sides)
	{
		ExpectConstructorFailure<domain_error>(4, 1, 2, "Side 1 can not be greater than sum of side 2 and side 3");
		ExpectConstructorFailure<domain_error>(1, 4, 2, "Side 2 can not be greater than sum of side 1 and side 3");
		ExpectConstructorFailure<domain_error>(1, 2, 4, "Side 3 can not be greater than sum of side 1 and side 2");
	}

	BOOST_AUTO_TEST_CASE(can_be_degerate)
	{
		TriangleExists(0, 0, 0);

		TriangleExists(1, 1, 2);
		TriangleExists(1, 2, 1);
		TriangleExists(2, 1, 1);

		TriangleExists(0, 1, 1);
		TriangleExists(1, 0, 1);
		TriangleExists(1, 1, 0);

		TriangleExists(1, 2, 3);
		TriangleExists(1, 3, 2);
		TriangleExists(2, 3, 1);
		TriangleExists(2, 1, 3);
		TriangleExists(3, 1, 2);
		TriangleExists(3, 2, 1);
	}

	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		CheckPerimeter(3, 4, 5);

		CheckPerimeter(0, 0, 0);
		CheckPerimeter(1, 1, 2);
		CheckPerimeter(1, 2, 3);

		CheckPerimeter(7.25, 4.08, 9.99);
	}

	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		const CTriangle t(3, 4, 5);
		BOOST_CHECK_EQUAL(t.GetArea(), 6);
		CheckArea(1, 1, 1);
		CheckArea(1, 1, 0);
		CheckArea(3.1, 3.2, 3.3);
	}

	struct when_created_
	{
		CTriangle t = CTriangle(3, 4, 5);
	};
	BOOST_FIXTURE_TEST_SUITE(when_created, when_created_)
		BOOST_AUTO_TEST_CASE(has_three_sides)
		{
			BOOST_CHECK_EQUAL(t.GetSide1(), 3);
			BOOST_CHECK_EQUAL(t.GetSide2(), 4);
			BOOST_CHECK_EQUAL(t.GetSide3(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()