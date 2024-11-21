#include  "asserts_functions.h"
using namespace std;


void AssertsFunc(vector<string> assert, Position posSelected)
{
    //selectedCategory
    //SelectedResource
    //CityCount
    //VillageCount
    //RoadCount
    //SelectedComplete
    //SelectedCar
    //SelectedTruck
    //SelectedPeople
    //CarCount
    //TruckCount
    //HelicopterCount
    //SelectedCoordinates
    Square current;
    if(posSelected.first != 0)
        current = World::board[posSelected.second - 1][posSelected.first - 1];

    StepName stepName;
    for (int i = 0; i < assert.size(); i++) {
        stepName = Command::getStepName(assert[i]);
        switch (stepName) {
        case StepName::SelectedCategory: {
            selectedCategory_func(current);
            break;
        }
        case StepName::SelectedCoordinates: {
            selectedCoordinates_func(posSelected);
            break;
        }
        default:
            break;
        }
    }
}

void selectedCategory_func(Square& s) {
    if (s.person != nullptr) {
        if(Tile* t = dynamic_cast<Tile*>(s.place.get()))
            if(t->tileType == 2)
                cout << "SelectedCategory " << Configuration::Tiles[t->tileType - 1] << endl;
        else
            cout << "SelectedCategory People" << endl;
    }
        
    else if(Tile * t = dynamic_cast<Tile*>(s.place.get()))
        cout << "SelectedCategory " << Configuration::Tiles[t->tileType - 1] << endl;
    else if(City * c = dynamic_cast<City*>(s.place.get()))
        cout << "SelectedCategory City" << endl;
    else if (Village* c = dynamic_cast<Village*>(s.place.get()))
        cout << "SelectedCategory Village" << endl;
    else if (Road* c = dynamic_cast<Road*>(s.place.get()))
        cout << "SelectedCategory Road" << endl;
}

void selectedCoordinates_func(Position& pos)
{
    cout << "SelectedCoordinates " << pos.first / 5 << " " << pos.second / 5 << endl;
}