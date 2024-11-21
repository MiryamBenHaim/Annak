#ifndef __VEHICLE__
#define __VEHICLE__

#include "movies.h"
#include "resources.h"
#include "capacities.h"

class Vehicle : public Movies {
public:
    double speed;
    Capacities c;
    Resources r;

    Vehicle(double s) :speed(s) {}
    virtual ~Vehicle() {}
};

#endif // __VEHICLE__