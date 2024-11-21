#ifndef __CAR__
#define __CAR__

#include "vehicle.h"
#include "configuration.h"

class Car : public Vehicle {
public:
    static int carCount;
    Car() : Vehicle(Configuration::conf["Speeds"]["Car"]) {
        carCount++;

        for (int i = 0; i < 5; i++)
            c.cap[i] = Configuration::conf["Capacities"]["Car"][i];
    }
};

#endif // __CAR__