#ifndef LAB2_X16_H
#define LAB2_X16_H

#include <iostream>
const int N = 4;

using namespace std;

void dopoln(const unsigned char [N], int, unsigned char [N]);

class X16 {
private:
    int len;
    unsigned char number[N];
    void correctlen();
    inline char getsign();
public:
    X16();
    explicit X16(long int num);
    explicit X16(char *num);
    ~X16();
    friend ostream & operator<< (ostream &, X16);
    friend istream & operator>> (istream &, X16);
    X16 operator + (X16);
    X16 operator - (X16);
    X16 operator <<= (X16);
    X16 operator >>= (X16);
    int getlen() const;
    unsigned char (&getnumber())[N];
    void setmas(const unsigned char[N]);
};


#endif //LAB2_X16_H
