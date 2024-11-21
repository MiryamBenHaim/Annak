#ifndef __ROAD__
#define __ROAD__

#include "place.h"

class Road : public Place {
public:
    static int roadCount;
    bool completed = false;

    Road() {
        roadCount++;
    }

    //if it can be destuct we have to decrease in the dtor
};

#endif // __ROAD__