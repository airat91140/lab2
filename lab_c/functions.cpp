#include "functions.h"
#include <iostream>
using namespace std;


template<class T>
void get_num(T &a) {
    while (true) {
        cin >> a;
        if (cin.good()) {
            cin.ignore();
            return;
        }
        cout << "You are wrong. Repeat, please." << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

int dialog(const char *qmsgs[], int M) {
    char *errmsg = (char *) "";
    int rc;
    do {
        cout << errmsg;
        errmsg = (char *) "You are wrong. Repeat, please!\n";
        for (int i = 0; i < M; ++i)
            cout << qmsgs[i] << endl;
        cout << ("Make your choice: --> ") << endl;
        get_num(rc);
    } while (rc < 0 || rc >= M);
    return rc;
}

int SetNum(X16 &num) {
    cout << "Input number" << endl;
    try {
        cin >> num;
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    return 1;
}

int PrintNum(X16 &num) {
    cout << num << endl;
    return 1;
}

int Add(X16 &num1) {
    cout << "Enter second number" << endl;
    X16 num2;
    try {
        cin >> num2;
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    num1 = num1 + num2;
    cout << "The result is:" << endl;
    cout << num1 << endl;
    return 1;
}

int Subtract(X16 &num1) {
    cout << "Enter second number" << endl;
    X16 num2;
    try {
        cin >> num2;
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    num1 = num1 - num2;
    cout << "The result is:" << endl;
    cout << num1 << endl;
    return 1;
}

int LShift(X16 &num) {
    int am;
    cout << "Enter how many shifts do you want" << endl;
    get_num(am); try {
        num <<= am;
        cout << "The result is:" << endl;
        cout << num << endl;
        return 1;
    }
    catch (exception& br) {
        cout << br.what() << endl;
        return 1;
    }
}

int RShift(X16 &num) {
    int am;
    cout << "Enter how many shifts do you want" << endl;
    get_num(am);
    try {
        num >>= am;
        cout << "The result is:" << endl;
        cout << num << endl;
        return 1;
    }
    catch (exception& br) {
        cout << br.what() << endl;
        return 1;
    }
}

int Compare(X16 &num1) {
    cout << "Enter second number" << endl;
    X16 num2;
    try {
        cin >> num2;
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    int res = num1.compare(num2);
    if (res > 0)
        cout << num1 << " is bigger than " << num2 << endl;
    else if (res < 0)
        cout << num1 << " is less than " << num2 << endl;
    else
        cout << num1 << " is equal to " << num2 << endl;
     return 1;
}

int IsEven(X16 &num) {
    if (!num.isEven())
        cout << "It is not even" << endl;
    else
        cout << "It is even" << endl;
    return 1;
}