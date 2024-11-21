#ifndef __HELICOPTER__
#define __HELICOPTER__

#include "vehicle.h"
#include "configuration.h"

class Helicopter : public Vehicle {
public:
    static int helicopterCount;

    Helicopter() : Vehicle(Configuration::conf["Speeds"]["Helicopter"]) {
        helicopterCount++;

        for (int i = 0; i < 5; i++)
            c.cap[i] = Configuration::conf["Capacities"]["Helicopter"][i];
    }
};

#endif // __HELICOPTER__