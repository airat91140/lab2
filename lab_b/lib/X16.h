#ifndef LAB2_X16_H
#define LAB2_X16_H

#include <iostream>

const int N = 10;

using namespace std;

void dopoln(const unsigned char [N], int, unsigned char [N]);

class X16 {
private:
    int len; //длина числа
    unsigned char number[N] = {0};
    //само число, в каждом байте - две цифры

    void correctlen(); //корректирование длинны числа

    inline unsigned char getsign() const; //получение знака числа  0 - положительный, любой другой - отрицательный

    void setmas(const unsigned char[N]); //установление своего массива

    static void setSign(unsigned char[N]);

    const unsigned char (&getnumber())[N] { //получение самого числа как массива чисел
        return number;
    };

    const unsigned char(&getnumber() const)[N] { //получение самого числа как массива чисел
        return number;
    };

    int getlen() const; //получение длины строки
public:
    X16();//конструктор по умолчанию

    explicit X16(long int num); //конструктор создающий число из константного значения

    explicit X16(char *num); //конструктор создающий число из строки

    ~X16();

    friend ostream &operator <<(ostream &, const X16 &); //вывод числа

    friend istream &operator >>(istream &, X16 &); //ввод числа в виде строки

    X16 operator +(const X16 &) const; //сложение чисел

    X16 operator -(X16) const; //вычетание чисел

    X16 operator <<=(int); //сдвиг влево на int

    X16 operator >>=(int); //сдвиг вправо на int

    bool isEven(); //проверка на четность

    int compare(X16); // сравнение числе  1 - левый больше, -1 - правый больше, 0 одинаковы
};


#endif //LAB2_X16_H
