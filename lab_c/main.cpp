#include "functions.h"
#include "X16.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main() {
    int rc;
    char *errmsg = (char *) "";
    X16 *num = new X16;
    cout << "Enter your number:" << endl;
    do {
        cout << errmsg;
        errmsg = (char *) "You are wrong. Repeat, please!\n";
        try {
            cin >> *num;
            rc = 1;
        }
        catch (exception &br) {
            cout << br.what() << endl;
            rc = -1;
        }
    } while (rc < 0);
    cout << "Choose your variant" << endl;
    while ((rc = dialog(msgs, NMsgs))) {
        if (!fptr[rc](*num))
            break;
    }
    delete num;
    return 0;
}
