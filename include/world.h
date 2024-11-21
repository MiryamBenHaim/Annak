#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <memory>
#include "square.h"
#include "tile.h"
#include "road.h"
#include "place.h"
#include "configuration.h"

class World
{
public:
    static std::vector<std::vector<Square>> board;

    static void addTiles(std::vector<std::vector<int>> myTiles);

    static void printBoard();
};

#endif // __WORLD__