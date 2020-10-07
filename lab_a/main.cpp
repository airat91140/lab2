#include <iostream>
#include "X16.h"
#include "functions.h"

using namespace std;

int main() {
    int rc;
    char *errmsg = (char *) "";
    X16 num;
    cout << "Enter your number:" << endl;
    do {
        cout << errmsg;
        errmsg = (char *) "You are wrong. Repeat, please!\n";
        try {
            num.input(cin);
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
    }
    return 0;
}
