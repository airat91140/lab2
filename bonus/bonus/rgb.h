#ifndef RGB_H
#define RGB_H

#include "Hex.h"

struct RGB {
    H16_3::Hex R, G, B;

    RGB(): R(0), G(0), B(0) {};

    RGB(char [7]);

    RGB operator +(const RGB &) const;
};

RGB average(const RGB &, const RGB &);

std::stringstream &trueHex(const RGB &, std::stringstream &);

#endif // RGB_H
