#ifndef LAB2_FUNCTIONS_H
#define LAB2_FUNCTIONS_H

#include "X16.h"


__declspec(selectany) const char *msgs[] = {"0. Quit",
                                            "1. Set number",
                                            "2. Print number",
                                            "3. Add",
                                            "4. Subtract",
                                            "5. Left shift of set number",
                                            "6. Right shift of set number",
                                            "7. Compare numbers",
                                            "8. Check, if set number is even"};

__declspec(selectany) int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

template<class T>
void get_num(T &);

int dialog(const char*[], int);

int SetNum(X16 &);

int PrintNum(X16 &);

int Add(X16 &);

int Subtract(X16 &);

int LShift(X16 &);

int RShift(X16 &);

int Compare(X16 &);

int IsEven(X16 &);

__declspec(selectany) int (*fptr[])(X16 &) = {nullptr, SetNum, PrintNum, Add, Subtract, LShift, RShift, Compare, IsEven};



#endif //LAB2_FUNCTIONS_H
