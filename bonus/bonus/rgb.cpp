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

RGB RGB::operator+(const RGB &sec) const {
    RGB result;
    result.R = R + sec.R;
    result.B = B + sec.B;
    result.G = G + sec.G;
    return result;
}

RGB::RGB(char num[7]) {
    B = num + 4;
    if (B.Compare(0) == -1)
        throw std::invalid_argument("Invalid Hex");
    num[4] = '\0';
    G = num + 2;
    if (G.Compare(0) == -1)
        throw std::invalid_argument("Invalid Hex");
    num[2] = '\0';
    R = num;
    if (R.Compare(0) == -1)
        throw std::invalid_argument("Invalid Hex");
}
