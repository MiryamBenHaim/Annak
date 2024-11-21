#ifndef __VILAGE_CITY__
#define __VILAGE_CITY__

#include "place.h"
#include "capacities.h"

class VillageCity : public Place {
public:
    Capacities c;
    bool completed = false;

    VillageCity() { }
};

#endif // __VILAGE_CITY__