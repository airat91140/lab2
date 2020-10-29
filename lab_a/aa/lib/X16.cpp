#include "X16.h"
#include <cstdlib>
#include <cstring>

X16::X16() { //по-умолчанию нуль
    this->len = 1;
    for (unsigned char &i : this->number)
        i = 0;
}

X16::X16(const long num) {
    unsigned long temp = num > 0 ? num : -num; //берем модуль от числа
    for (int i = 0; i < sizeof(long); ++i) {
        unsigned char fig;
        fig = temp & 0xffu; //берем последний байт числа
        temp >>= 8u; //сдвигаем наше число вправо на 1 байт
        number[N - i - 1] = fig;
    }
    for (int i = 0; i < N - sizeof(long); ++i) { //оставшиееся место заполняем нулями
        number[i] = '\0';
    }
    if (num < 0) { //выставление знака числа
        setSign(number);
    }
    correctlen();
    if (num >= 0) {
        if (this->getsign() != 0)
            ++len; //для определеннности если в положительном числе первый бит единичка, то добавляем у нему еще полбайта
        //чтобы число казалось положительным
    }
    if (len <= 0)
        len = 1;
}


X16::X16(char *num) {
    for (unsigned char &i : number) { //иницализируем пустой массив из нулей
        i = 0;
    }
    len = 0;
    if (strlen(num) > N * 2)
        throw invalid_argument("Too long string");
    if (strlen(num) < 1)
        throw invalid_argument("Too short string");
    for (int i = strlen(num) - 1, j = 1;
         i >= 0; i -= 2) { //идем в цикле с конца строки, j нужно для контроляв какой байт записывать
        char tmp[3];
        if (i > 0) { //случай когда есть возможность взять два символа строки
            if (!((num[i - 1] >= 'A' && num[i - 1] <= 'F' ||
                   num[i - 1] >= 'a' && num[i - 1] <= 'f' ||
                   num[i - 1] >= '0' && num[i - 1] <= '9') &&
                  (num[i] >= 'A' && num[i] <= 'F' ||
                   num[i] >= 'a' && num[i] <= 'f' ||
                   num[i] >= '0' && num[i] <= '9')))
                throw invalid_argument("Wrong string"); //проверяем валидность строки
            tmp[0] = num[i - 1];
            tmp[1] = num[i]; //записываем два символа в строку
            tmp[2] = '\0';
            unsigned long res;
            res = strtoul(tmp, nullptr, 16); //переводим строку в число
            number[N - j] = res & 0xff; //берем последний байт из полученного числа(на всякий случай) и записываем в массив
            ++j;
            len += 2; //увеличиваем длину числв
        } else { //случай когда остался только один символ
            if (!(num[i] >= 'A' && num[i] <= 'F' ||
                  num[i] >= 'a' && num[i] <= 'f' ||
                  num[i] >= '0' && num[i] <= '9'))
                throw invalid_argument("Wrong string"); //проверка правильности символа
            tmp[0] = num[i];
            tmp[1] = '\0';
            unsigned long res;
            res = strtoul(tmp, nullptr, 16); //переводим символ в строку
            number[N - j] = res & 0xf; //записываем последний полубайт
            ++len;
            ++j;
        }
    }
}

ostream &X16::print(ostream &out) {
    if ((N * 2 - len) & 1) //выписываем первые буквы в зависмости от того находятся они в первой или второй половине
        out << hex << (unsigned int) (number[(N * 2 - len) / 2] & 0x0f);
    else
        out << hex << (unsigned int) ((number[(N * 2 - len) / 2] >> 4) & 0x0f)
            << (unsigned int) (number[(N * 2 - getlen()) / 2] & 0x0f);
    for (int i = (N * 2 - getlen()) / 2 + 1; i < N; ++i) {//выписываем по очереди оставшиеся символы
        out << (unsigned int) ((number[i] >> 4) & 0x0f)
            << (unsigned int) (number[i] & 0x0f);
    }
    return out << dec;
}

istream &X16::input(istream &in) {
    char name[N * 2];
    in.getline(name, N * 2 - 1);
    if (in.fail()) {
         in.clear();
         in.ignore(32767, '\n');
         throw invalid_argument("Wrong string");
    }
    X16 num(name);
    *this = num;
    return in;
}

X16 X16::add(X16 sec) {
    unsigned char a[N], b[N];
    dopoln(this->getnumber(), this->getlen(), a);//находим дополнительный код для обоих чисел
    dopoln(sec.getnumber(), sec.getlen(), b);
    unsigned char res[N], res2[N], perenos = 0;
    for (int i = N - 1; i >= 0; --i) {
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
        res[i] = fig; //вставляем полученный байт в массив
    }
    dopoln(res, N * 2, res2); //перводим из дополнительного кода обратно в прямой
    if ((res2[0] & 0x80) != 0) {
        res2[0] &= 0x7f;
        setSign(res2);
    }
    X16 result;
    result.setmas(res2);
    result.correctlen();

    if (this->getsign() == 0 && sec.getsign() == 0 && result.getsign() != 0) {
        ++result.len; //если положительное число начинается с 1, то увеличиваем длинну результата, чтобы он начинался с нуля
    }
    return result;
}


X16 X16::subtract(X16 sec) {
    if (sec.len & 1) //нечетное количество символов
        (sec.number[(N * 2 - sec.len) / 2]) ^= 0x08; //меняем знаковый бит на противоположный
    else
        (sec.number[(N * 2 - sec.len) / 2]) ^= 0x80;
    return this->add(sec);
}

X16 X16::Lshift(int am) {
    if (am < 0)
        throw invalid_argument("Wrong argument");
    unsigned char sign = getsign();
    if ((am & 1) == 0) {
        for (int j = (N * 2 - len) / 2 + am / 2; j < N; ++j)
            number[j - am / 2] = number[j];
        if (len & 1)
            number[(N * 2 - len) / 2] &= 0x0f;
        for (int j = N - am / 2  > 0 ? N - am / 2 : 0; j < N; ++j)
            number[j] = 0;
    } else {
        Lshift(am - 1);
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 0; j < len; ++j) {
            if (j & 1) { //если цифра находится в левой половине байта
                tmpl = number[N - 1 - j / 2] & 0xf0; //запоминаем стоявшее тут число
                tmpl >>= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[N - 1 - j / 2] &= 0x0f;
                number[N - 1 - j / 2] |= tmpr; //вставляем предыдюю цифру
            } else { //если цифра находится в правой половине байта
                tmpr = number[N - 1 - j / 2] & 0x0f; //запоминаем стоявшее тут число
                tmpr <<= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[N - 1 - j / 2] &= 0xf0;
                number[N - 1 - j / 2] |= tmpl;  //вставляем предыдюю цифру
            }
        }
    }
    if (len & 1) { //для числа, в котором крайняя левая цифра находится в правой половине байта
        if (sign == 0) //восстанавливаем знаки, ведь в прямом коде знак не сдвигается
            number[(N * 2 - len) / 2] &= 0xf7;
        else
            number[(N * 2 - len) / 2] |= 0x08;
    } else { //для числа, в котором крайняя левая цифра находится в левой половине байта
        if (sign == 0)
            number[(N * 2 - len) / 2] &= 0x7f;
        else
            number[(N * 2 - len) / 2] |= 0x80;
    }
    return *this;
}

X16 X16::Rshift(int am) {
    if (am < 0)
        throw invalid_argument("Wrong argument");
    unsigned char sign = getsign();
    if (len & 1) { //находим модуль числа, предварительно сохранив его знак
        number[(N * 2 - len) / 2] &= 0xf7;
    } else {
        number[(N * 2 - len) / 2] &= 0x7f;
    }
    if ((am & 1) == 0) {
        for (int j = N - 1 - (am / 2); j >= (N * 2 - len) / 2; --j)
            number[j + (am / 2)] = number[j];
        for (int j = (N * 2 - len) / 2; j < ((N * 2 - len) / 2 + am / 2 >= N ? N : (N * 2 - len) / 2 + am / 2); ++j)
            number[j] = 0;
    } else {
        Rshift(am - 1);
        unsigned char tmpl = 0, tmpr = 0;
        for (int j = 2 * N - len; j < 2 * N; ++j) {
            if (j & 1) { //если цифра находится в левой половине байта
                tmpr = number[j / 2] & 0x0f; //запоминаем стоявшее тут число
                tmpr <<= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[j / 2] &= 0xf0;
                number[j / 2] |= tmpl; //вставляем предыдюю цифру
            } else { //если цифра находится в правой половине байта
                tmpl = number[j / 2] & 0xf0; //запоминаем стоявшее тут число
                tmpl >>= 4; //делаем его подходящим для ставки в другую половину следующего байта
                number[j / 2] &= 0x0f;
                number[j / 2] |= tmpr; //вставляем предыдюю цифру
            }
        }
    }
    if (sign != 0) {
        if (len & 1) { //востанавливаем знак
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

void X16::correctlen() {
    this->len = N * 2;
    int i = 0;
    while (this->number[i] == 0) { //проходим все пустые точки
        ++i;
        this->len -= 2;
    }
    if ((this->number[i] >> 4) == 0) //если число в левом байте пусто
        --this->len;
    if (len <= 0) {
        len = 1;
    }
}

void X16::setmas(const unsigned char n[N]) {
    for (int i = 0; i < N; ++i) {
        number[i] = n[i];
    }
    correctlen();
}

unsigned char X16::getsign() {
    if (len & 1)
        return (getnumber()[(N * 2 - len) / 2]) & 0x08;
    else
        return (getnumber()[(N * 2 - len) / 2]) & 0x80;
}

bool X16::isEven() {
    return !(number[N - 1] & 1);
}

int X16::compare(X16 sec) { // 1 - левый больше, -1 - правый больше, 0 одинаковы
    unsigned char sign1 = this->getsign(), sign2 = sec.getsign(); //находим знаки чисел
    if (sign1 == 0 && sign2 != 0)//проверяем, вдруг одно из чисел положительное, а другое отрицательное
        return 1;
    if (sign1 != 0 && sign2 == 0)
        return -1;
    unsigned char num1[N], num2[N];
    for (int i = 0; i < N; ++i) {
        num1[i] = this->getnumber()[i];
        num2[i] = sec.getnumber()[i];
    }
    if (this->len & 1) //находим модули этих чисел, так как знаки у низх обязательно одиноковые
        num1[(N * 2 - this->len) / 2] &= 0xf7;
    else
        num1[(N * 2 - this->len) / 2] &= 0x7f;
    if (sec.len & 1)
        num2[(N * 2 - sec.len) / 2] &= 0xf7;
    else
        num2[(N * 2 - sec.len) / 2] &= 0x7f;
    for (int i = 0; i < N; ++i) { //сверяем числа побайтно
        if (num1[i] > num2[i]) {
            if (sign1 == 0) //для положительных
                return 1;
            else //для отрицательных
                return -1;
        }
        if (num1[i] < num2[i]) {
            if (sign1 == 0) //для положительных
                return -1;
            else //для отрицательных
                return 1;
        }
    }
    return 0;
}

void X16::setSign(unsigned char num[N]) {
    for (int i = 0; i < N; ++i) {
        if (num[i] != 0) { //находим первый ненулевой символ
            if ((num[i] & 0xf0) == 0) { //если первая половина байта свободна
                if (num[i] & 0x08) //если во второй половине нет места для знакового бита
                    num[i] |= 0x80; //выставляем знаковый бит во первую половину
                else
                    num[i] |= 0x08; //если есть место то знаковый бит выставляем в первую половину
            } else { //если весь байт занят числом
                if (i == 0)
                    throw logic_error("overflow"); //весь массив чисел занят и знаковый бит не вмещается
                if (num[i] & 0x80) { //проверяем свободность первого бита в байте
                    num[i - 1] |= 0x08; //выставляем знаковый бит в предыдущем байте во второй половине
                } else {
                    num[i] |= 0x80; //место есть в текущем байте и вставляем туда
                }
            }
            break; //знаковый ьит вставлен и выход из цикла
        }
    }
}

void dopoln(const unsigned char num[N], int len, unsigned char dop[N]) {
    for (int i = 0; i < N; ++i) //инициализируем дополнительеый код числа нулями
        dop[i] = 0;
    if (len & 1) { //крайний левый символ находится в правой половине байта
        if ((num[(N * 2 - len) / 2] & 0x08) == 0) {//если число положительное, то просто перекопируем его
            for (int i = 0; i < N; ++i)
                dop[i] = num[i];
            return;
        } else { //отрицательное число
            bool flag = true; //флаг добавление к байту единицы
            for (int i = N - 1; i >= 0; --i) {
                dop[i] = ~(num[i]); //инвертируем данный байт
                if (i == (N * 2 - len) / 2)
                    dop[(N * 2 - len) /
                        2] |= 0x08; //инвертируем еще раз знаковый бит, так как нужно было найти модуль числа
                if (flag) {
                    dop[i] += 1;
                    if (dop[i] !=
                        0) { //переполнение может возникнуть только если в байте все единицы, поэтому проверяем не стало ли число нулем
                        flag = false;
                    }
                }
            }
        }
    } else { //крайний левый символ находится в левой половине байта
        if ((num[(N * 2 - len) / 2] & 0x80) == 0) {//если число положительное, то просто перекопируем его
            for (int i = 0; i < N; ++i)
                dop[i] = num[i];
            return;
        } else { //отрицательное число
            bool flag = true; //флаг добавление к байту единицы
            for (int i = N - 1; i >= 0; --i) {
                dop[i] = ~(num[i]);  //инвертируем данный байт
                if (i == (N * 2 - len) / 2)
                    dop[(N * 2 - len) /
                        2] |= 0x80; //инвертируем еще раз знаковый бит, так как нужно было найти модуль числа
                if (flag) {
                    dop[i] += 1;
                    if (dop[i] !=
                        0) { //переполнение может возникнуть только если в байте все единицы, поэтому проверяем не стало ли число нулем
                        flag = false;
                    }
                }
            }
        }
    }
}

X16::~X16() = default;