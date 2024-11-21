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
        case StepName::SelectedResource: {
            selectedResource_func(current);
            break;
        }
        case StepName::SelectedComplete: {
            selectedComplete_func(current);
            break;
        }
        case StepName::CityCount: {
            cityCount_func();
            break;
        }
        case StepName::VillageCount: {
            villageCount_func();
            break;
        }
        case StepName::RoadCount: {
            roadCount_func();
            break;
        }
        case StepName::SelectedCar: {
            selectedCar_func(current);
            break;
        }
        case StepName::SelectedTruck: {
            selectedTruck_func(current);
            break;
        }
        case StepName::SelectedPeople: {
            selectedPeople_func(current);
            break;
        }
        case StepName::CarCount: {
            carCount_func();
            break;
        }
        case StepName::TruckCount: {
            truckCount_func();
            break;
        }
        case StepName::HelicopterCount: {
            helicopterCount_func();
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

void selectedCar_func(Square& s) {
    if (Car* c = dynamic_cast<Car*>(s.vehicle.get()))//check capacities and resources
        cout << "SelectedCar 1" << endl;
    else
        cout << "SelectedCar 0" << endl;
}

void selectedTruck_func(Square& s) {
    if (Truck* t = dynamic_cast<Truck*>(s.vehicle.get()))//check capacities and resources
        cout << "SelectedTruck 1" << endl;
    else
        cout << "SelectedTruck 0" << endl;
}

void selectedPeople_func(Square& s) {
    if (s.person != nullptr)
        cout << "SelectedPeople 1" << endl;
    else if (VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get()))//check capacities and resources
        //if(vc->r.res[4] != 0)
            cout << "SelectedPeople " << vc->r.res[4] << endl;
    else
        cout << "SelectedPeople 0" << endl;
}

void selectedResource_func(Square& s) {
    //before we have to check what with vehicle/truck/helicopter
    //in the end - it's OK
    if(s.person)
        cout << "SelectedResource " << s.person->r.toString() << endl;
    else if (Tile* t = dynamic_cast<Tile*>(s.place.get()))
        cout << "SelectedResource " << t->r.toString() << endl;
    else if(VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get()))
        cout << "SelectedResource " << vc->r.toString() << endl;
}

void selectedComplete_func(Square& s) {
    if (VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get())) {
        cout << "SelectedComplete ";
        vc->completed ? cout << "True" << endl : cout << "False" << endl;
    }
    else if (Road* r = dynamic_cast<Road*>(s.place.get())) {
        cout << "SelectedComplete ";
        r->completed ? cout << "True" << endl : cout << "False" << endl;
    }
}

void cityCount_func()
{
    cout << "CityCount " << City::cityCount << endl;
}

void villageCount_func()
{
    cout << "VillageCount " << Village::villageCount << endl;
}

void roadCount_func()
{
    cout << "RoadCount " << Road::roadCount << endl;
}

void carCount_func()
{
    cout << "CarCount " << Car::carCount << endl;
    //if the count for Sthe city selected (and get Square& s in the statement)
    /*if (VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get()))
        cout << "CarCount " << vc->r.res[] << endl;*/
}

void truckCount_func()
{
    cout << "TruckCount " << Truck::truckCount << endl;
    /*if (VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get()))
        cout << "TruckCount " << vc->r.res[] << endl;*/
}

void helicopterCount_func()
{
    cout << "HelicopterCount " << Helicopter::helicopterCount << endl;
    /*if (VillageCity* vc = dynamic_cast<VillageCity*>(s.place.get()))
        cout << "HelicopterCount " << vc->r.res[] << endl;*/
}

void selectedCoordinates_func(Position& pos)
{
    cout << "SelectedCoordinates " << pos.first / 5 << " " << pos.second / 5 << endl;
}