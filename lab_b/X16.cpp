#include "X16.h"
#include <cstdlib>
#include <cstring>
#include <cerrno>

X16::X16() {
    this->len = 0;
    for (int i = 0; i < N; ++i)
        this->number[i] = '\0';
}

X16::X16(const long num) {
    unsigned long temp = num > 0 ? num : -num;
    for (int i = 0; i < sizeof(long); ++i) {
        unsigned char fig;
        fig = temp & 0xff;
        temp >>= 8;
        number[N - i - 1] = fig;
    }
    for (int i = 0; i < N - sizeof(long); ++i) {
        number[i] = '\0';
    }
    if (num < 0) {
        for (int i = 0; i < N; ++i) {
            if (number[i] != 0) {
                if ((number[i] & 0xf0) == 0) {
                    if (number[i] & 0x08)
                        number[i] |= 0x80;
                    else
                        number[i] |= 0x08;
                } else {
                    if (number[i] & 0x80) {
                        if (i == 0)
                            throw logic_error("overflow");
                        number[i - 1] |= 0x08;
                    } else {
                        number[i] |= 0x80;
                    }
                }
                break;
            }
        }
    }
    correctlen();
    if (num >= 0) {
        if (this->getsign() != 0)
            ++len;
    }
}

X16::X16(char *num) {
    for (int i = 0; i < N; ++i) {
        number[i] = 0;
    }
    char **ptr;
    len = 0;
    if (strlen(num) > N * 2)
        throw invalid_argument("Too long string");
    for (int i = strlen(num) - 1, j = 1; i >= 0; i -= 2) {
        char tmp[2];
        if (i > 0) {
            if (!((num[i - 1] >= 'A' && num[i - 1] <= 'F' || num[i - 1] >= 'a' && num[i - 1] <= 'f' ||
                   num[i - 1] >= '0' && num[i - 1] <= '9') &&
                  (num[i] >= 'A' && num[i] <= 'F' || num[i] >= 'a' && num[i] <= 'f' || num[i] >= '0' && num[i] <= '9')))
                throw invalid_argument("Wrong string");
            tmp[0] = num[i - 1];
            tmp[1] = num[i];
            unsigned long res = 0;
            res = strtoul(tmp, nullptr, 16);
            number[N - j] = res & 0x00ff;
            ++j;
            len += 2;
        } else {
            if (!(num[i] >= 'A' && num[i] <= 'Z' || num[i] >= 'a' && num[i] <= 'z' || num[i] >= '0' && num[i] <= '9'))
                throw invalid_argument("Wrong string");
            tmp[1] = num[i];
            unsigned long res = 0;
            res = strtoul(tmp + 1, nullptr, 16);
            number[N - j] = res & 0x000f;
            ++len;
            ++j;
        }
    }
}

ostream &operator<<(ostream &out, X16 x16) {
    if ((N * 2 - x16.getlen()) & 1)
        out << hex << (unsigned int) (x16.getnumber()[(N * 2 - x16.getlen()) / 2] & 0x0f);
    else
        out << hex << (unsigned int) ((x16.getnumber()[(N * 2 - x16.getlen()) / 2] >> 4) & 0x0f)
            << (unsigned int) (x16.getnumber()[(N * 2 - x16.getlen()) / 2] & 0x0f);
    for (int i = (N * 2 - x16.getlen()) / 2 + 1; i < N; ++i) {
        out << (unsigned int) ((x16.getnumber()[i] >> 4) & 0x0f)
            << (unsigned int) (x16.getnumber()[i] & 0x0f);
    }
    return out << dec;
}

istream &operator>>(istream &in, X16 x16) {
    char name[N];
    in >> name;
    X16 num(name);
    x16 = num;
    return in;
}

X16 X16::operator+(X16 sec) {
    unsigned char a[N], b[N];
    dopoln(this->getnumber(), this->getlen(), a);
    dopoln(sec.getnumber(), sec.getlen(), b);
    unsigned char res[N], res2[N];
    char perenos = 0;
    for (int i = N - 1; i >= 0; --i) {
        unsigned char fig;
        char sum;
        for (int j = 0; j < 8; ++j) {
            sum = (a[i] ^ b[i] ^ perenos) & 1;
            perenos = ((a[i] & b[i]) | (perenos & (a[i] ^ b[i]))) & 1;
            fig >>= 1;
            if (sum) {
                fig |= '\200'; //1000 0000
            }
            a[i] >>= 1;
            b[i] >>= 1;
        }
        res[i] = fig;
    }
    dopoln(res, N, res2);
    X16 result;
    result.setmas(res2);
    result.correctlen();
    if (this->getsign() == 0 && sec.getsign() == 0 && result.getsign() != 0) {
        ++result.len;
    }
    return result;
}

X16 X16::operator-(X16 sec) {
    if (len & 1) //нечетное количество символов
        (sec.number[(N * 2 - len) / 2]) ^= 0x08;
    else
        (sec.number[(N * 2 - len) / 2]) ^= 0x80;
    return *this + sec;
}

X16 X16::operator<<=(int am) {
    unsigned char sign = getsign();
    for (int i = 0; i < am; ++i) {
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 0; j < len; ++j) {
            if (j & 1) {
                tmpl = number[N - 1 - j / 2] & 0xf0;
                tmpl >>= 4;
                number[N - 1 - j / 2] &= 0x0f;
                number[N - 1 - j / 2] |= tmpr;
            } else {
                tmpr = number[N - 1 - j / 2] & 0x0f;
                tmpr <<= 4;
                number[N - 1 - j / 2] &= 0xf0;
                number[N - 1 - j / 2] |= tmpl;
            }
        }
    }
    if (len & 1) {//нечетное количество символов
        if (sign == 0)
            number[(N * 2 - len) / 2] &= 0xf7;
        else
            number[(N * 2 - len) / 2] |= 0x08;
        }
    else {
        if (sign == 0)
            number[(N * 2 - len) / 2] &= 0x7f;
        else
            number[(N * 2 - len) / 2] |= 0x80;
    }
    return *this;
}

X16 X16::operator>>=(int am) {
    unsigned char sign = getsign();
    if (len & 1) {//нечетное количество символов
        number[(N * 2 - len) / 2] &= 0xf7;
    }
    else {
        number[(N * 2 - len) / 2] &= 0x7f;
    }
    for (int i = 0; i < am; ++i) {
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 2 * N - len; j < 2 * N; ++j) {
            if (j & 1) {
                tmpr = number[j / 2] & 0x0f;
                tmpr <<= 4;
                number[j / 2] &= 0xf0;
                number[j / 2] |= tmpl;
            } else {
                tmpl = number[j / 2] & 0xf0;
                tmpl >>= 4;
                number[j / 2] &= 0x0f;
                number[j / 2] |= tmpr;
            }
        }
    }
    if (sign != 0) {
        if (len & 1) {//нечетное количество символов
            number[(N * 2 - len) / 2] |= 0x08;
        } else {
            number[(N * 2 - len) / 2] |= 0x80;
        }
    }
    return *this;
}

int X16::getlen() const {
    return this->len;
}

unsigned char (&X16::getnumber())[N] {
    return this->number;
}

void X16::correctlen() {
    this->len = N * 2;
    int i = 0;
    while (this->number[i] == 0) {
        ++i;
        this->len -= 2;
    }
    if ((this->number[i] >> 4) == 0)
        --this->len;
}

void X16::setmas(const unsigned char n[N]) {
    for (int i = 0; i < N; ++i) {
        number[i] = n[i];
    }
    correctlen();
}

char X16::getsign() {
    if (len & 1) //нечетное количество символов
        return (getnumber()[(N * 2 - len) / 2]) & 0x08;
    else
        return (getnumber()[(N * 2 - len) / 2]) & 0x80;
}

bool X16::isEven() {
    return number[N - 1] & 1;
}

int X16::compare(X16 sec) { // 1 - левый больше, -1 - правый больше, 0 одинаковы
    char sign1 = this->getsign(), sign2 = sec.getsign();
    if (sign1 == 0 && sign2 != 0)
        return 1;
    if (sign1 != 0 && sign2 == 0)
        return -1;
    unsigned char num1[N], num2[N];
    for (int i = 0; i < N; ++i) {
        num1[i] = this->getnumber()[i];
        num2[i] = sec.getnumber()[i];
    }
    if (this->len & 1)
        num1[(N * 2 - this->len) / 2] &= 0xf7;
    if (sec.len & 1)
        num2[(N * 2 - sec.len) / 2] &= 0x7f;
    for (int i = 0; i < N; ++i) {
        if (num1[i] > num2[i]) {
            if (sign1 == 0)
                return 1;
            else
                return -1;
        }
        if (num1[i] < num2[i]) {
            if (sign1 == 0)
                return -1;
            else
                return 1;
        }
    }
    return 0;
}

void dopoln(const unsigned char num[N], int len, unsigned char dop[N]) {
    for (int i = 0; i < len; ++i)
        dop[i] = 0;
    if (len & 1) { //нечетное количество символов
        if ((num[(N * 2 - len) / 2] & 0x08) == 0) {//положительно число
            for (int i = 0; i < N; ++i)
                dop[i] = num[i];
            return;
        } else { //отрицательное число
            bool flag = true;
            for (int i = N - 1; i >= 0; --i) {
                dop[i] = ~(num[i]);
                if (i == (N * 2 - len) / 2)
                    dop[(N * 2 - len) / 2] |= 0x08;
                if (flag) {
                    dop[i] += 1;
                    if (dop[i] != 0) { //переполнение
                        flag = false;
                    }
                }
            }
        }
    } else { //четное количество символов
        if ((num[(N * 2 - len) / 2] & 0x80) == 0) {//положительно число
            for (int i = 0; i < N; ++i)
                dop[i] = num[i];
            return;
        } else { //отрицательное число
            bool flag = true;
            for (int i = N - 1; i >= 0; --i) {
                dop[i] = ~(num[i]);
                if (i == (N * 2 - len) / 2)
                    dop[(N * 2 - len) / 2] |= 0x80;
                if (flag) {
                    dop[i] += 1;
                    if (dop[i] != 0) { //переполнение
                        flag = false;
                    }
                }
            }
        }
    }
}

X16::~X16() = default;

