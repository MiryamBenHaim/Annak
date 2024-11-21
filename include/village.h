#ifndef __VILAGE__
#define __VILAGE__

#include "village_city.h"
#include "configuration.h"

class Village : public VillageCity {
public:
    static int villageCount;

    Village() {
        r.res[4] = 1;
        villageCount++;
        for (int i = 0; i < 5; i++)
            c.cap[i] = Configuration::conf["Capacities"]["Village"][i];
    }
};

#endif // __VILAGE__