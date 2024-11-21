#ifndef __CITY__
#define __CITY__

#include "village_city.h"
#include "configuration.h"

class City : public VillageCity {
public:
    static int cityCount;

    City() {
        r.res[4] = 5;
        cityCount++;
        for (int i = 0; i < 5; i++)
            c.cap[i] = Configuration::conf["Capacities"]["City"][i];
    }
};

#endif // __CITY__