#ifndef __RESOURCES__
#define __RESOURCES__

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

class Resources {
public:
    double res[5] = {0, 0, 0, 0, 0};

    Resources operator+(const Resources& other) const;

    Resources operator-(const Resources& other) const;

    bool operator<(const Resources& other) const;

    std::string toString();
};

#endif // __RESOURCES__