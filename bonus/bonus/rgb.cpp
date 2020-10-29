#include "rgb.h"
#include <iostream>
#include "sstream"

RGB average(const RGB &first, const RGB &second) {
    RGB result = first + second;
    result = result + result;
    result = result + result;
    result = result + result;
    result.R >>= 1;
    result.B >>= 1;
    result.G >>= 1;
    return result;
}

std::stringstream &trueHex(const RGB &color, std::stringstream &str) {
    str.str("");
    if (color.R.Compare(16) == -1)
        str << "0";
    str << color.R;
    if (color.G.Compare(16) == -1)
        str << "0";
    str << color.G;
    if (color.B.Compare(16) == -1)
        str << "0";
    str << color.B;
    return str;
}
