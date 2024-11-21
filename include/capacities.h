#ifndef __CAPACITIES__
#define __CAPACITIES__

#include <cmath>
#include "resources.h"

class Capacities {
public:
    int cap[5] = { 0, 0, 0, 0, 0 };

    Capacities() { }

    Resources check(Resources& res1, Resources& res2) {
        Resources r = res1 + res2;
        for (int i = 0; i < 5; i++) {
            res1.res[i] = std::min(r.res[i], static_cast<double>(cap[i]));
            r.res[i] -= res1.res[i];
        }
        return r;
    }
};

#endif // __CAPACITIES__