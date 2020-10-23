#include "X16.h"
#include <cstring>
#include <iostream>

X16::X16(const long num) {
    auto temp = (unsigned long) (num > 0 ? num : -num); //берем модуль от числа
    number = new unsigned char[sizeof(long)];
    for (int i = 0; i < sizeof(long); ++i) {
        unsigned char fig;
        fig = temp & 0xff; //берем последний байт числа
        temp >>= 8; //сдвигаем наше число вправо на 1 байт
        number[sizeof(long) - i - 1] = fig; //записываем с конца байт
    }
    correctlen(sizeof(long));
    if (num < 0) { //выставление знака числа
        setSign(number, sizeof(long));
    }
    if (len <= 0)
        len = 1;
    if ((len + 3) / 2 != sizeof(long)) { //уменьшение памяти
        auto *tmp = new unsigned char[(len + 3) / 2];
        for(int i = 0; i < (len + 3) / 2; ++i) {
            tmp[(len + 3) / 2 - 1 - i] = number[sizeof(long) - 1 - i];
        }
        delete [] number;
        number = tmp;
    }
}

X16::X16(char *num) {
    char sign = 0;
    if (strlen(num) < 1)
        throw invalid_argument("Too short string");
    len = strlen(num);
    if (num[0] == '-') {
        sign = 1;
        num += 1;
        --len;
    }
    number = new unsigned char[(len + 3) / 2] {0};
    for (int i = (int) strlen(num) - 1, j = 1; i >= 0; i -= 2) { //идем в цикле с конца строки
        char tmp[3]; // j нужно для контроляв какой байт записывать
        if (i > 0) { //случай когда есть возможность взять два символа строки
            if (!((num[i - 1] >= 'A' && num[i - 1] <= 'F' ||
                   num[i - 1] >= 'a' && num[i - 1] <= 'f' ||
                   num[i - 1] >= '0' && num[i - 1] <= '9') &&
                  (num[i] >= 'A' && num[i] <= 'F' ||
                   num[i] >= 'a' && num[i] <= 'f' ||
                   num[i] >= '0' && num[i] <= '9'))) {
                delete[] number;
                throw invalid_argument("Wrong string"); //проверяем валидность строки
            }
            tmp[0] = num[i - 1];
            tmp[1] = num[i]; //записываем два символа в строку
            tmp[2] = '\0';
            unsigned long res;
            res = strtoul(tmp, nullptr, 16); //переводим строку в число
            number[(len + 3) / 2 - j] &= 0;
            number[(len + 3) / 2 - j] = res & 0xff; //берем последний байт из полученного числа и записываем в массив
            ++j;
        } else { //случай когда остался только один символ
            if (!(num[i] >= 'A' && num[i] <= 'F' ||
                  num[i] >= 'a' && num[i] <= 'f' ||
                  num[i] >= '0' && num[i] <= '9')) {
                delete[] number;
                throw invalid_argument("Wrong string"); //проверка правильности символа
            }
            tmp[0] = num[i];
            tmp[1] = '\0';
            unsigned long res;
            res = strtoul(tmp, nullptr, 16); //переводим символ в строку
            number[(len + 3) / 2 - j] &= 0;
            number[(len + 3) / 2 - j] = res & 0xf; //записываем последний полубайт
            ++j;
        }
    }
    correctlen((len + 3) / 2);
    if (len != strlen(num)) {
        auto *tmp = new unsigned char[(len + 3) / 2];
        for(int i = 0; i < (len + 3) / 2; ++i) {
            tmp[(len + 3) / 2 - 1 - i] = number[(strlen(num) + 3) / 2 - 1 - i];
        }
        delete [] number;
        number = tmp;
    }
    number[0] &= 0;
    if (sign == 1) {
        number[0] |= 0x80;
    }
}

X16::X16(const X16 &num): len(num.len) {
    number = new unsigned char [(len + 3) / 2];
    for (int i = 0; i < (len + 3) / 2; ++i)
        number[i] = num.number[i];
}

X16::X16(X16 &&num)noexcept: len(num.len), number(num.number) {
    num.number = nullptr;
}

X16 &X16::operator = (X16 &&num)  noexcept {
    if (this != &num) {
        int tmp = num.len;
        num.len = len;
        len = tmp;
        unsigned char *ptr = num.number;
        num.number = number;
        number = ptr;
    }
    return *this;
}

X16 &X16::operator = (const X16 &num) {
    if (this != &num) {
        len = num.len;
        delete [] number;
        number = new unsigned char [(len + 3) / 2];
        for (int i = 0; i < (len + 3) / 2; ++i) {
            number[i] = num.number[i];
        }
    }
    return *this;
}

ostream &operator <<(ostream &out, const X16 &num) {
    if (num.number[0] != 0)
        cout << '-';
    if (num.len & 1) //выписываем первые буквы в зависмости от того находятся они в первой или второй половине
        out << hex << (unsigned int) (num.number[1] & 0x0f);
    else
        out << hex << (unsigned int) ((num.number[1] >> 4) & 0x0f)
            << (unsigned int) (num.number[1] & 0x0f);
    for (int i = 2; i < (num.len + 3) / 2; ++i) {//выписываем по очереди оставшиеся символы
        out << (unsigned int) ((num.number[i] >> 4) & 0x0f)
            << (unsigned int) (num.number[i] & 0x0f);
    }
    return out << dec;
}

istream &operator >>(istream &in, X16 &num) {
    char name[500];
    in.getline(name, 499);
     if (!in.good()) {
         in.clear();
         in.ignore(32767, '\n');
         throw invalid_argument("Wrong string");
     }
    num = X16(name);
    return in;
}

X16 X16::operator +(const X16 &sec) const {
    unsigned char *a, *b;
    unsigned char sign;
    int length = findmax((this->len + 1) / 2, (sec.len + 1) / 2) + 2;
    a = new unsigned char [length]{0};
    b = new unsigned char [length]{0};
    dopoln(this->number, (this->len + 3) / 2, a, length);//находим дополнительный код для обоих чисел
    dopoln(sec.number, (sec.len + 3) / 2, b, length);//находим дополнительный код для обоих чисел
    unsigned char perenos = 0;
    for (int i = length - 1; i >= 0; --i) {
        unsigned char fig = 0, sum;
        for (int j = 0; j < 8; ++j) { //внутри байта складываем каждый бит по отдельности
            sum = (a[i] ^ b[i] ^ perenos) & 1; //формируем сумму двух битов
            perenos = ((a[i] & b[i]) | (perenos & (a[i] ^ b[i]))) & 1; //формируем единицу переноса
            fig >>= 1; //сдвигаем впрво для добавления новыого элемента
            if (sum) { //ставим первым элементом полученный результат
                fig |= 0x80; //1000 0000
            }
            a[i] >>= 1; //двигаем данные внутри байтов для рассмотрения следующих битов
            b[i] >>= 1;
        }
        a[i] = fig; //вставляем полученный байт в массив
    }
    delete [] b;
    dopoln(a, length, a, length); //перводим из дополнительного кода обратно в прямой
    sign = a[0];
    a[0] &= 0;
    X16 result;
    delete [] result.number;
    result.number = a;
    result.correctlen(length);
    if (sign)
        setSign(result.number, length);
    if (length != (result.len + 3) / 2) {
        auto *tmp = new unsigned char[(result.len + 3) / 2];
        for (int i = 0; i < (result.len + 3) / 2; ++i) {
            tmp[(result.len + 3) / 2 - 1 - i] = result.number[length - 1 - i];
        }
        delete[] result.number;
        result.number = tmp;
    }
    return result;
}


X16 X16::operator -(X16 sec) const {
    sec.number[0] ^= 0x80;
    return *this + sec;
}


X16 X16::operator <<=(int am) {
    if (am < 0)
        throw invalid_argument("Wrong argument");
    if (am >= len) {
        delete [] number;
        number = new unsigned char [2] {0};
        len = 1;
        return *this;
    }
    if ((am & 1) == 0) {
        for (int j = 1 + am / 2; j < (len + 3) / 2; ++j)
            number[j - am / 2] = number[j];
        if (len & 1)
            number[1] &= 0x0f;
        for (int i = (len + 3) / 2 - am / 2; i < (len + 3) / 2; ++i)
            number[i] = 0;
    } else {
        *this <<= am - 1;
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 0; j < len; ++j) {
            if (j & 1) { //если цифра находится в левой половине байта
                tmpl = number[(len + 3) / 2 - 1 - j / 2] & 0xf0; //запоминаем стоявшее тут число
                tmpl >>= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[(len + 3) / 2 - 1 - j / 2] &= 0x0f;
                number[(len + 3) / 2 - 1 - j / 2] |= tmpr; //вставляем предыдюю цифру
            } else { //если цифра находится в правой половине байта
                tmpr = number[(len + 3) / 2 - 1 - j / 2] & 0x0f; //запоминаем стоявшее тут число
                tmpr <<= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[(len + 3) / 2 - 1 - j / 2] &= 0xf0;
                number[(len + 3) / 2 - 1 - j / 2] |= tmpl;  //вставляем предыдюю цифру
            }
        }
    }
    return *this;
}

X16 X16::operator >>=(int am) {
    if (am < 0)
        throw invalid_argument("Wrong argument");
    if (am >= len) {
        delete [] number;
        number = new unsigned char [2] {0};
        len = 1;
        return *this;
    }
    if ((am & 1) == 0) {
        auto tmp = new unsigned char[(len + 3) / 2 - am / 2];
        for (int j = 1; j < (len + 3) / 2 - am / 2; ++j)
            tmp[j] = number[j];
        tmp[0] = number[0];
        delete[] number;
        len -= am;
        number = tmp;
    }
    else {
        *this >>= am - 1;
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 2; j < ((len & 1) ?  len + 3 : len + 2); ++j) {
            if ((j & 1)) { //если цифра находится в правой половине байта
                tmpr = number[j / 2] & 0x0f; //запоминаем стоявшее тут число
                tmpr <<= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[j / 2] &= 0xf0;
                number[j / 2] |= tmpl; //вставляем предыдюю цифру
            } else { //если цифра находится в левой половине байта
                tmpl = number[j / 2] & 0xf0; //запоминаем стоявшее тут число
                tmpl >>= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[j / 2] &= 0x0f;
                number[j / 2] |= tmpr; //вставляем предыдюю цифру
            }
        }
        number[1] &= 0x0f;
        len -= 1;
        if (number[1] == 0) {
            auto *tmp = new unsigned char[(len + 3) / 2];
            tmp[0] = number[0];
            for(int i = 1; i < (len + 3) / 2; ++i) {
                tmp[i] = number[i + 1];
            }
            delete [] number;
            number = tmp;
        }
    }
    return *this;
}

int X16::getlen() const {
    return this->len;
}

void X16::correctlen(int now_len) {
    this->len = now_len * 2;
    int i = 0;
    while (this->number[i] == 0) { //проходим все пустые точки
        ++i;
        this->len -= 2;
    }
    if ((this->number[i] >> 4) == 0) //если число в левом байте пусто
        --this->len;
    if (len == 0)
	len = 1;
}


bool X16::isEven() {
    return !(number[(len + 3) / 2 - 1] & 1);
}

int X16::compare(const X16 &sec) { // 1 - левый больше, -1 - правый больше, 0 одинаковы
    if (number[0] == 0 && sec.number[0] != 0)//проверяем, вдруг одно из чисел положительное, а другое отрицательное
        return 1;
    if (number[0] != 0 && sec.number[0] == 0)
        return -1;
    if (len > sec.len) {
        if (number[0] == 0)
            return 1;
        else
            return -1;
    }
    else if (len < sec.len) {
        if (number[0] == 0)
            return -1;
        else
            return 1;
    }
    else {
        for (int i = 1; i < (len + 3) / 2; ++i) { //сверяем числа побайтно
            if (number[i] > sec.number[i]) {
                if (number[0] == 0) //для положительных
                    return 1;
                else //для отрицательных
                    return -1;
            }
            if (number[i] < sec.number[i]) {
                if (number[0] == 0) //для положительных
                    return -1;
                else //для отрицательных
                    return 1;
            }
        }
        return 0;

    }
}

void X16::setSign(unsigned char *num, int size) {
    for (int i = 0; i < size; ++i) {
        if (num[i] != 0) { //находим первый ненулевой символ
            if (i > 0) {
                num[i - 1] &= 0x0;
                num[i - 1] |= 0x80;
                return;
            }
            else
                throw logic_error("Memory is not enough"); //весь массив чисел занят и знаковый бит не вмещается
        }
    }
}

void X16::dopoln(const unsigned char *num, int len1, unsigned char *dop, int len2) {
    if (num[0] == 0) {//если число положительное, то просто перекопируем его
        for (int i = 0; i < len1; ++i)
            dop[len2 - i - 1] = num[len1 - i - 1];
        return;
    } else { //отрицательное число
        bool flag = true; //флаг добавление к байту единицы
        for (int i = len2 - 1, j = len1 - 1; j >= 1; --j, --i) {
            dop[i] = ~(num[j]); //инвертируем данный байт
            if (flag) {
                dop[i] += 1;
                if (dop[i] != 0) { //переполнение может возникнуть только если в байте все единицы
                    flag = false; //, поэтому проверяем не стало ли число нулем
                }
            }
        }

        for (int i = 0; i <= len2 - len1; ++i) {
            if (flag)
                dop[i] = 0;
            else
                dop[i] = 0xff;
        }
    }
}


X16::~X16() {
    delete[] number;
}