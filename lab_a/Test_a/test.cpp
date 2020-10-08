#include "pch.h"
#include "../X16.h"
#include "../X16.cpp"

TEST(X16Constructor, DefaultConstructor)
{
	X16 a1;
	ASSERT_EQ(1, a1.getlen());
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(0, a1.getnumber()[i]);
	}
}

TEST(X16Constructor, InitNumConstructors)
{
	X16 a2(0x3);
	ASSERT_EQ(1, a2.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a2.getnumber()[i]);
	}
	ASSERT_EQ(0, a2.getnumber()[N - 1] & 0xf0);
	ASSERT_EQ(3, a2.getnumber()[N - 1] & 0x0f);

	X16 a3(0x14);
	ASSERT_EQ(2, a3.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a3.getnumber()[i]);
	}
	ASSERT_EQ(0x14, a3.getnumber()[N - 1]);

	X16 a4(28675); //0x7003
	ASSERT_EQ(4, a4.getlen());
	for (int i = 0; i < N - 2; ++i) {
		ASSERT_EQ(0, a4.getnumber()[i]);
	}
	ASSERT_EQ(0x70, a4.getnumber()[N - 2]);
	ASSERT_EQ(0x03, a4.getnumber()[N - 1]);

	X16 a5(-3);
	ASSERT_EQ(1, a5.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a5.getnumber()[i]);
	}
	ASSERT_EQ(0, a5.getnumber()[N - 1] & 0xf0);
	ASSERT_EQ(11, a5.getnumber()[N - 1] & 0x0f);

	X16 a6(-235); //0x8eb
	ASSERT_EQ(3, a6.getlen());
	for (int i = 0; i < N - 2; ++i) {
		ASSERT_EQ(0, a6.getnumber()[i]);
	}
	ASSERT_EQ(0x08, a6.getnumber()[N - 2]);
	ASSERT_EQ(0xeb, a6.getnumber()[N - 1]);
}

TEST(X16Constructor, InitCharConstructors)
{
	X16 a2("3");
	ASSERT_EQ(1, a2.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a2.getnumber()[i]);
	}
	ASSERT_EQ(0, a2.getnumber()[N - 1] & 0xf0);
	ASSERT_EQ(3, a2.getnumber()[N - 1] & 0x0f);

	X16 a3("14");
	ASSERT_EQ(2, a3.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a3.getnumber()[i]);
	}
	ASSERT_EQ(0x14, a3.getnumber()[N - 1]);

	X16 a4("7003");
	ASSERT_EQ(4, a4.getlen());
	for (int i = 0; i < N - 2; ++i) {
		ASSERT_EQ(0, a4.getnumber()[i]);
	}
	ASSERT_EQ(0x70, a4.getnumber()[N - 2]);
	ASSERT_EQ(0x03, a4.getnumber()[N - 1]);

	X16 a5("b");
	ASSERT_EQ(1, a5.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a5.getnumber()[i]);
	}
	ASSERT_EQ(0, a5.getnumber()[N - 1] & 0xf0);
	ASSERT_EQ(11, a5.getnumber()[N - 1] & 0x0f);

	X16 a6("8eb");
	ASSERT_EQ(3, a6.getlen());
	for (int i = 0; i < N - 2; ++i) {
		ASSERT_EQ(0, a6.getnumber()[i]);
	}
	ASSERT_EQ(0x08, a6.getnumber()[N - 2]);
	ASSERT_EQ(0xeb, a6.getnumber()[N - 1]);
}
TEST(X16Constructor, TestException)
{
	ASSERT_ANY_THROW(X16(""));
	ASSERT_ANY_THROW(X16("G"));
	ASSERT_ANY_THROW(X16("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}
/*
TEST(X16set, TestSet)
{
	X16 a;
	a.set_length(12);
	ASSERT_EQ(12, a.get_length());
	a.set_line(3, 5);
	ASSERT_EQ(3, a.get_line().k);
	ASSERT_EQ(5, a.get_line().b);
}

TEST(X16set, TestSetexceptions)
{
	X16 a;
	ASSERT_ANY_THROW(a.set_length(-12));
	ASSERT_ANY_THROW(a.set_length(0));
}

TEST(X16Functions, TestFunctions)
{
	X16 a;
	double t = 1.0;
	ASSERT_NEAR(-0.06428, a.get_coordinates(t).x, 0.001);
	ASSERT_NEAR(0.84147, a.get_coordinates(t).y, 0.001);
	ASSERT_NEAR(0.99999, a.get_line_length(t), 0.001);
	ASSERT_NEAR(0.64209, a.get_radius(t), 0.001);
	ASSERT_NEAR(PI / 2, a.get_area(), 0.001);
	ASSERT_NEAR(PI * 4, a.get_rotation_area(), 0.001);
	ASSERT_NEAR(2 * PI / 3, a.get_volume(), 0.001);
	a.set_line(3, 2);
	Point p = a.get_coordinates(t);
	ASSERT_NEAR(-1.10893, p.x, 0.001);
	ASSERT_NEAR(2.24648, p.y, 0.001);
	ASSERT_NEAR(3.37679, a.get_line_length(t), 0.001);
	ASSERT_NEAR(0.642, a.get_radius(t), 0.001);
}

TEST(X16Functions, TestExcepttions)
{
	X16 a;
	double t1 = -1;
	double t2 = 4;
	ASSERT_ANY_THROW(a.get_coordinates(t1));
	ASSERT_ANY_THROW(a.get_coordinates(t2));
	ASSERT_ANY_THROW(a.get_line_length(t1));
	ASSERT_ANY_THROW(a.get_line_length(t2));
	ASSERT_ANY_THROW(a.get_radius(t1));
	ASSERT_ANY_THROW(a.get_radius(t2));
}
*/