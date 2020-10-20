#include "gtest/gtest.h"
#include "X16.h"

#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

TEST(X16Constructor, DefaultConstructor)
{
	X16 a1;
	ASSERT_EQ(1, a1.getlen());
	for (int i = 0; i < 2; ++i) {
		ASSERT_EQ(0, a1.getnumber()[i]);
	}
}

TEST(X16Constructor, InitNumConstructors)
{
	X16 a2(0x3);
	ASSERT_EQ(1, a2.getlen());
	ASSERT_EQ(0, a2.getnumber()[0]);
	ASSERT_EQ(3, a2.getnumber()[1]);

	X16 a3(0x14);
	ASSERT_EQ(2, a3.getlen());
	ASSERT_EQ(0, a3.getnumber()[0]);
	ASSERT_EQ(0x14, a3.getnumber()[1]);

	X16 a4(28675); //0x7003
	ASSERT_EQ(4, a4.getlen());
	ASSERT_EQ(0, a4.getnumber()[0]);
	ASSERT_EQ(0x70, a4.getnumber()[1]);
	ASSERT_EQ(0x03, a4.getnumber()[2]);

	X16 a5(-3);
	ASSERT_EQ(1, a5.getlen());
	ASSERT_EQ(0x80, a5.getnumber()[0]);
	ASSERT_EQ(0x3, a5.getnumber()[1]); //00001011

	X16 a6(-235); //-eb
	ASSERT_EQ(2, a6.getlen());
	ASSERT_EQ(0x80, a6.getnumber()[0]);
	ASSERT_EQ(0xeb, a6.getnumber()[1]);

    X16 a7(-24658); //-6052
    ASSERT_EQ(4, a7.getlen());
    ASSERT_EQ(0x80, a7.getnumber()[0]);
    ASSERT_EQ(0x60, a7.getnumber()[1]);
    ASSERT_EQ(0x52, a7.getnumber()[2]);
}


TEST(X16Constructor, InitCharConstructors)
{
	X16 a2("3");
	ASSERT_EQ(1, a2.getlen());
	ASSERT_EQ(0, a2.getnumber()[0]);
	ASSERT_EQ(0x03, a2.getnumber()[1]);

	X16 a3("14");
	ASSERT_EQ(2, a3.getlen());
	ASSERT_EQ(0, a3.getnumber()[0]);
	ASSERT_EQ(0x14, a3.getnumber()[1]);

	X16 a4("7003");
	ASSERT_EQ(4, a4.getlen());
    ASSERT_EQ(0, a4.getnumber()[0]);
    ASSERT_EQ(0x70, a4.getnumber()[1]);
	ASSERT_EQ(0x03, a4.getnumber()[2]);

	X16 a5("-b");
	ASSERT_EQ(1, a5.getlen());
	ASSERT_EQ(0x80, a5.getnumber()[0] );
	ASSERT_EQ(0xb, a5.getnumber()[1]);

	X16 a6("-8eb");
	ASSERT_EQ(3, a6.getlen());
    ASSERT_EQ(0x80, a6.getnumber()[0]);
    ASSERT_EQ(0x08, a6.getnumber()[1]);
	ASSERT_EQ(0xeb, a6.getnumber()[2]);

	X16 a7("0b");
	ASSERT_EQ(1, a7.getlen());
    ASSERT_EQ(0, a7.getnumber()[0]);
    ASSERT_EQ(0x0b, a7.getnumber()[1]);
}

TEST(X16Constructor, TestCopy)
{
    X16 aa("abcdef");
    ASSERT_EQ(0, aa.compare(X16("abcdef")));
}

TEST(X16Constructor, TestException)
{
	ASSERT_ANY_THROW(X16(""));
	ASSERT_ANY_THROW(X16("G"));
	ASSERT_THROW(X16(""), std::invalid_argument);
	ASSERT_THROW(X16("G"), std::invalid_argument);
}

TEST(X16Functions, TestFunctions)
{
	X16 a(100000);
	ASSERT_EQ(0, a.compare((X16(20) + (X16(99980)))));
	ASSERT_EQ(0, a.compare((X16(100056) + (X16(-56)))));
	ASSERT_EQ(0, a.compare((X16(100046) - (X16(46)))));
	ASSERT_EQ(0, a.compare((X16(86000) - (X16(-14000)))));

	X16 a1(-100000);
	ASSERT_EQ(0, a1.compare((X16(-20) + (X16(-99980)))));
	ASSERT_EQ(0, a1.compare((X16(-100056) + (X16(56)))));
	ASSERT_EQ(0, a1.compare((X16(-100046) - (X16(-46)))));
	ASSERT_EQ(0, a1.compare((X16(-86000) - (X16(14000)))));

	const X16 d1(150000);
	const X16 d2(50000);
	ASSERT_EQ(0, a.compare(d1 - d2));

        X16 b1("-ABC0");
        X16 c1("-ABC");
        b1 >>= 1;
        ASSERT_EQ(0, b1.compare(c1));

        X16 b4("-ABC0");
        X16 c4("-AB");
        b4 >>= 2;
        ASSERT_EQ(0, b4.compare(c4));

        X16 b5("-ABC0");
        X16 c5("-A");
        b5 >>= 3;
        ASSERT_EQ(0, b5.compare(c5));

        X16 b3("-FFFF");
        X16 c3("0");
        b3 >>= 15;
        ASSERT_EQ(0, b3.compare(c3));

        X16 b6("ABC0");
        X16 c6("0");
        b6 >>= 34;
        ASSERT_EQ(0, b6.compare(c6));

        X16 b2("-ABC0");
        X16 c2("-BC00");
        b2 <<= 1;
        ASSERT_EQ(0, b2.compare(c2));

        X16 b7("-ABC0");
        X16 c7("-C000");
        b7 <<= 2;
        ASSERT_EQ(0, b7.compare(c7));

        X16 b8("-ABCD");
        X16 c8("-D000");
        b8 <<= 3;
        ASSERT_EQ(0, b8.compare(c8));

        X16 b9("-FFFF");
        X16 c9("0");
        b9 <<= 15;
        ASSERT_EQ(0, b9.compare(c9));

        X16 b10("ABC0");
        X16 c10("0");
        b10 <<= 34;
        ASSERT_EQ(0, b10.compare(c10));



        X16 b11("ABc");
        X16 c11("AB");
        b11 >>= 1;
        ASSERT_EQ(0, b11.compare(c11));

        X16 b41("ABC0");
        X16 c41("AB");
        b41 >>= 2;
        ASSERT_EQ(0, b41.compare(c41));

        X16 b51("ABC0");
        X16 c51("A");
        b51 >>= 3;
        ASSERT_EQ(0, b51.compare(c51));

        X16 b21("ABC0");
        X16 c21("BC00");
        b21 <<= 1;
        ASSERT_EQ(0, b21.compare(c21));

        X16 b71("ABC0");
        X16 c71("C000");
        b71 <<= 2;
        ASSERT_EQ(0, b71.compare(c71));

        X16 b81("ABCD");
        X16 c81("D000");
        b81 <<= 3;
        ASSERT_EQ(0, b81.compare(c81));


	ASSERT_EQ(true, X16(0L).isEven());
	ASSERT_EQ(false, X16("9").isEven());

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
	ASSERT_THROW(a <<= -2, std::invalid_argument);
	ASSERT_THROW(a >>= -2, std::invalid_argument);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}