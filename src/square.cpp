#include "square.h"
using namespace std;

void Square::Change(Place * place)
{
    if (typeid(this->place) != typeid(Tile*) || ((Tile*)this->place.get())->tileType != 1)
        cerr << "You can't put this place on place which is not ground";
    else
        *(this->place) = *place;
    //to check what with if there is something in this square.mabey with overriding?
}