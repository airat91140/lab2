#include "X16.h"
#include <iostream>
using namespace std;

int main() {
    X16 a((char *)"ba2c"), b((char *)"baaa");
    cout<<a.compare(b)<<endl;
}
