#ifndef __TILE__
#define __TILE__

#include <iostream>
#include <vector>
#include <memory>
#include "resources.h"

class Tile : public Place {
public:
    int tileType;

    Tile(int tType) : Place(), tileType(tType) {
        if (tileType == 3 || tileType == 4) {
            r.res[tileType - 3] = 10;
        }
        else if (tileType == 5 || tileType == 6) {
            r.res[tileType - 3] = 100;
        }
    };

    ~Tile() { }

};

#endif // __TILE__