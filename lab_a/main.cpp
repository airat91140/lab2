#include "X16.h"
#include <iostream>
using namespace std;

int main() {
    X16 a((char *)"0abc"), b((char *)"0545");
    cout<<a - b<<endl;
}
