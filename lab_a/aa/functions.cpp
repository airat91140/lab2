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
        num.input(cin);
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    return 1;
}

int PrintNum(X16 &num) {
    num.print(cout);
    cout << endl;
    return 1;
}

int Add(X16 &num1) {
    cout << "Enter second number" << endl;
    X16 num2;
    try {
        num2.input(cin);
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    num1 = num1.add(num2);
    cout << "The result is:" << endl;
    num1.print(cout);
    cout << endl;
    return 1;
}

int Subtract(X16 &num1) {
    cout << "Enter second number" << endl;
    X16 num2;
    try {
        num2.input(cin);
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    num1 = num1.subtract(num2);
    cout << "The result is:" << endl;
    num1.print(cout);
    cout << endl;
    return 1;
}

int LShift(X16 &num) {
    int am;
    cout << "Enter how many shifts do you want" << endl;
    get_num(am); try {
        num.Lshift(am);
        cout << "The result is:" << endl;
        num.print(cout);
        cout << endl;
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
        num.Rshift(am);
        cout << "The result is:" << endl;
        num.print(cout);
        cout << endl;
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
        num2.input(cin);
    }
    catch(exception &br) {
        cout << br.what() << endl;
        return 1;
    }
    int res = num1.compare(num2);
    if (res > 0) {
        num1.print(cout);
        cout << " is bigger than ";
        num2.print(cout);
        cout << endl;
    }
    else if (res < 0) {
        num1.print(cout);
        cout << " is less than ";
        num2.print(cout);
        cout << endl;
    }
    else {
        num1.print(cout);
        cout << " is equal to ";
        num2.print(cout);
        cout << endl;
    }
     return 1;
}

int IsEven(X16 &num) {
    if (!num.isEven())
        cout << "It is not even" << endl;
    else
        cout << "It is even" << endl;
    return 1;
}