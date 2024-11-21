#include "resources.h"
using namespace std;

Resources Resources::operator+(const Resources& other) const
{
    Resources r;
    for (int i = 0; i < 5; i++)
        r.res[i] = this->res[i] + other.res[i];
    return r;
}

Resources Resources::operator-(const Resources& other) const
{
    Resources r;
    for (int i = 0; i < 5; i++)
        r.res[i] = this->res[i] - abs(other.res[i]);
    return r;
}

bool Resources::operator<(const Resources& other) const
{
    for (int i = 0; i < 5; i++)
        if(this->res[i] < other.res[i])
            return true;
    return false;
}

string Resources::toString() {
    stringstream ss("");
    ss << this->res[0] << " " << this->res[1] << " " << this->res[2] << " " << this->res[3];
    return ss.str();
}