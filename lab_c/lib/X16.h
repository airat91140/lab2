#ifndef LAB2_X16_H
#define LAB2_X16_H

#include <iostream>

using namespace std;


class X16 {
private:
    static void dopoln(const unsigned char *, int, unsigned char *, int);

    int len; //длина числа
    unsigned char *number = nullptr;
    //само число, в каждом байте - две цифры

    void correctlen(int); //корректирование длинны числа

    void static setSign(unsigned char *, int);

    const unsigned char *getnumber() { //получение самого числа как массива чисел
        return number;
    };

    [[nodiscard]] const unsigned char *getnumber() const{ //получение самого числа как массива чисел
        return number;
    };

    [[nodiscard]] int getlen() const; //получение длины строки

    static int inline findmax(int a, int b) {
        return a > b ? a : b;
    }

public:
    X16():len(1), number(new unsigned char[2]{0}) {};//конструктор по умолчанию

    explicit X16(long int num); //конструктор создающий число из константного значения

    explicit X16(char *num); //конструктор создающий число из строки

    ~X16();

    X16(X16 &&) noexcept ;

    X16(const X16 &);

    X16 &operator = (const X16 &);

    X16 &operator = (X16 &&) noexcept;

    friend ostream &operator <<(ostream &, const X16 &); //вывод числа

    friend istream &operator >>(istream &, X16 &); //ввод числа в виде строки
//число можно вводить как например "abc" (положительное) и "-abc" (отрицательное), но "+abc" вызовет исколючение
    X16 operator +(const X16 &) const; //сложение чисел

    X16 operator -(X16) const; //вычетание чисел

    X16 operator <<=(int); //сдвиг влево на int

    X16 operator >>=(int); //сдвиг вправо на int

    bool isEven(); //проверка на четность

    int compare(const X16 &); // сравнение числе  1 - левый больше, -1 - правый больше, 0 одинаковы
};


#endif //LAB2_X16_H
