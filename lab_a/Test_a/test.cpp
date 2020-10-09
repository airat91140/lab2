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
	ASSERT_EQ(0xb, a5.getnumber()[N - 1] & 0x0f); //00001011

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

	X16 a7("0b");
	ASSERT_EQ(2, a7.getlen());
	for (int i = 0; i < N - 1; ++i) {
		ASSERT_EQ(0, a7.getnumber()[i]);
	}
	ASSERT_EQ(0x0b, a7.getnumber()[N - 1]);
}
TEST(X16Constructor, TestException)
{
	ASSERT_ANY_THROW(X16(""));
	ASSERT_ANY_THROW(X16("G"));
	ASSERT_ANY_THROW(X16("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	ASSERT_THROW(X16(""), std::invalid_argument);
}

TEST(X16Functions, TestFunctions)
{
	X16 a(100000);
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(a.getnumber()[i],(X16(20).add(X16(99980)).getnumber())[i]);
	}
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(a.getnumber()[i], (X16(125000).add(X16(-25000)).getnumber())[i]);
	}
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(a.getnumber()[i], (X16(100046).subtract(X16(46)).getnumber())[i]);
	}
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(a.getnumber()[i], (X16(73000).subtract(X16(-27000)).getnumber())[i]);
	}
	X16 b1("ABC0");
	X16 c1("82BC");
	b1.Rshift(1);
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(c1.getnumber()[i], b1.getnumber()[i]);
	}
	X16 b3("FFFF");
	X16 c3("8000");
	b3.Rshift(15);
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(c3.getnumber()[i], b3.getnumber()[i]);
	}
	X16 b2("ABC0");
	X16 c2("BC00");
	b2.Lshift(1);
	for (int i = 0; i < N; ++i) {
		ASSERT_EQ(c2.getnumber()[i], b2.getnumber()[i]);
	}

	ASSERT_EQ(true, X16(0L).isEven());
	ASSERT_EQ(true, X16("8").isEven());

	ASSERT_EQ(1, X16(286).compare(X16(13)));
	ASSERT_EQ(1, X16(286).compare(X16(-13)));
	ASSERT_EQ(1, X16(-50).compare(X16(-100)));
	ASSERT_EQ(0, X16(15).compare(X16(15)));
	ASSERT_EQ(0, X16(-286).compare(X16(-286)));
	ASSERT_EQ(-1, X16(286).compare(X16(562)));
	ASSERT_EQ(-1, X16(-15).compare(X16(562)));
	ASSERT_EQ(-1, X16(-36).compare(X16(-30)));
}

TEST(X16Functions, TestExcepttions)
{
	X16 a("ab");
	ASSERT_ANY_THROW(a.Lshift(-2));
	ASSERT_ANY_THROW(a.Rshift(-2));

}
