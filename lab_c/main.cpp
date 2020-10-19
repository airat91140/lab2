#include <iostream>
#include "functions.h"
#include "X16.h"

using namespace std;


int main() {
    X16 *a = new X16((char *)"12345");
    cout << ((*a) >>= 3);
    /*int rc;
    char *errmsg = (char *) "";
    X16 num;
    cout << "Enter your number:" << endl;
    do {
        cout << errmsg;
        errmsg = (char *) "You are wrong. Repeat, please!\n";
        try {
            cin >> num;
            rc = 1;
        }
        catch (exception &br) {
            cout << br.what() << endl;
            rc = -1;
        }
    } while (rc < 0);
    cout << "Choose your variant" << endl;
    while ((rc = dialog(msgs, NMsgs))) {
        if (!fptr[rc](num))
            break;
    }*/
    return 0;
}
