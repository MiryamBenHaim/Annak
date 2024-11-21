#ifndef __SQUARE__
#define __SQUARE__

#include <iostream>
#include <memory>
#include <typeinfo>
#include "place.h"
#include "person.h"
#include "vehicle.h"
#include "tile.h"

enum Type {
    _Tile, _VillageCity, _Road
};

typedef std::pair<int, int> Position;

class Square
{
public:
    Type type;
    std::shared_ptr<Place> place;
    Person* person;
    std::shared_ptr<Vehicle> vehicle;

    Square(Type type = _Tile, std::shared_ptr<Place> place = nullptr) : type(type), place(place), person(nullptr) { }

    ~Square() { }

    void Change(Place * place);

};

#endif // __SQUARE__