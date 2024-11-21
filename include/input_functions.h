#ifndef __INPUT_FUNCTIONS__
#define __INPUT_FUNCTIONS__

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

#include "start_functions.h"

void InputFunc(std::vector<std::shared_ptr<Command>> steps, Position* p);

#pragma region Go Function

std::vector<Position> generateDirectWay(Position& src, Position& dest);

std::vector<Position> generateWayOnRoads(Position& src, Position& dest);

bool move(Position* src, Position& dest);

bool goOnSquare(Position* src, Position& dest);

bool goOnRoad(Position* src, Position& dest);

bool go(Position* src, Position& dest);

#pragma endregion

///////
void deposit_func(std::vector<std::string> args, int time, Position* src);

void takeResources_func(std::vector<std::string>& args, int time, Position* src);
//////

void work_func(std::vector<std::string> args, Position* src);

void move_func(std::vector<std::string> args, Position* src);

void rain_func();

void wait_func(std::vector<std::shared_ptr<Command>>& whatToDo, int time, Position* p);

Square& select_func(std::vector<std::string>& pos, Position* p);

#endif // __INPUT_FUNCTIONS__