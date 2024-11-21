#ifndef __START_FUNCTIONS__
#define __START_FUNCTIONS__

#include <vector>
#include <string>

#include "../resources/code/Command.h"

#include "capacities.h"
#include "car.h"
#include "city.h"
#include "configuration.h"
#include "helicopter.h"
#include "images.h"
#include "movies.h"
#include "person.h"
#include "place.h"
#include "resources.h"
#include "road.h"
#include "square.h"
#include "tile.h"
#include "truck.h"
#include "vehicle.h"
#include "village_city.h"
#include "village.h"
#include "world.h"

void StartFunc(std::vector<std::shared_ptr<Command>> start);

#endif // __START_FUNCTIONS__