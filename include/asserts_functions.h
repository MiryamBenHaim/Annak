#ifndef __ASSERTS_FUNCTIONS__
#define __ASSERTS_FUNCTIONS__

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

void AssertsFunc(std::vector<std::string> assert, Position posSelected);

void selectedCategory_func(Square& s);

void selectedCar_func(Square& s);

void selectedTruck_func(Square& s);

void selectedPeople_func(Square& s);

void selectedResource_func(Square& s);

void selectedComplete_func(Square& s);

void cityCount_func();

void villageCount_func();

void roadCount_func();

void carCount_func();

void truckCount_func();

void helicopterCount_func();

void selectedCoordinates_func(Position& pos);

#endif