#ifndef __TRUCK__
#define __TRUCK__

#include "vehicle.h"
#include "configuration.h"

class Truck : public Vehicle {
public:
    static int truckCount;

    Truck() : Vehicle(Configuration::conf["Speeds"]["Truck"]) {
        truckCount++;

        for (int i = 0; i < 5; i++)
            c.cap[i] = Configuration::conf["Capacities"]["Truck"][i];
    }
};

#endif // __TRUCK__