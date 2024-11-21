#include "start_functions.h"
using namespace std;

void StartFunc(vector<shared_ptr<Command>> start)
{
    //Resource
    //People
    //Build (city/ village/ road)
    //MakeEmpty
    //Manufacture (car/ truck/ helicopter-test4)
    //Resources 

    StepName stepName;
    for (int i = 0; i < start.size(); i++) {
        stepName = Command::getStepName(start[i]->name);
        try {
            switch (stepName) {
            case StepName::Resource: {
                resource_func(start[i]->arguments);
                break;
            }
            case StepName::Resources: {
                resources_func(start[i]->arguments);
                break;
            }
            case StepName::People: {
                people_func(start[i]->arguments);
                break;
            }
            case StepName::MakeEmpty: {
                makeEmpty_func(start[i]->arguments);
                break;
            }
            case StepName::Build: {
                build_func(start[i]->arguments, true);
                break;
            }
            case StepName::Manufacture: {
                manufacture_func(start[i]->arguments, true);
                break;
            }
            default:
                break;
            }
        }
        catch (string msg) {
            cout << "ERROR! " << msg;
        }
    }
}

void resource_func(vector<string> args)
{
    int x = stoi(args[2]), y = stoi(args[3]), count = stoi(args[0]);
    string typeRes = args[1];
    Place* p = World::board[y - 1][x - 1].place.get();

    int i = find(Configuration::ResourceTypes.begin(), Configuration::ResourceTypes.end(), typeRes) - Configuration::ResourceTypes.begin();
    if (World::board[y - 1][x - 1].person)
        World::board[y - 1][x - 1].person->r.res[i] = count;
    else if (Tile* t = dynamic_cast<Tile*>(p)) {
        t->r.res[i] = count;
        //if (t->tileType - 3 == find(Configuration::ResourceTypes.begin(), Configuration::ResourceTypes.end(), typeRes) - Configuration::ResourceTypes.begin())//Configuration::conf["ResourceTypes"].find(typeRes) - Configuration::conf["ResourceTypes"].begin())
        //    t->r.res[t->tileType - 3] = count;
        //else
        //    cerr << "Not suitable resource!";
    }
    else if (VillageCity* vc = dynamic_cast<VillageCity*>(p)) {
        
        vc->r.res[i] = count;
    }
    else
        cerr << "Not suitable resource to road!";
}

void resources_func(vector<string> args)
{
    Position p = { stoi(args[4]), stoi(args[5]) };
    Resources* r;

    if (World::board[p.second - 1][p.first - 1].person)
        r = &World::board[p.second - 1][p.first - 1].person->r;
    else if (Vehicle* v = dynamic_cast<Vehicle*>(World::board[p.second - 1][p.first - 1].vehicle.get()))
        r = &v->r;
    else if (VillageCity* vc = dynamic_cast<VillageCity*>(World::board[p.second - 1][p.first - 1].place.get()))
        r = &vc->r;
    else if (Tile* t = dynamic_cast<Tile*>(World::board[p.second - 1][p.first - 1].place.get()))
        r = &t->r;
    else
        return; //cerr << "This place can not contain resources!";

    for (int i = 0; i < 4; i++)
    {
        r->res[i] = stoi(args[i]);
    }
}

void people_func(vector<string> args)
{
    int count = stoi(args[0]), x = stoi(args[1]), y = stoi(args[2]);
    if (World::board[y - 1][x - 1].person != nullptr || World::board[y - 1][x - 1].vehicle != nullptr)//check what is the first argument, can I create 2 peaple?
        cerr << "This square is full!";
    if (VillageCity* vc = dynamic_cast<VillageCity*>(World::board[y - 1][x - 1].place.get())) {
        Resources temp;
        temp.res[4] = count;
        int countProduced = count - vc->c.check(vc->r, temp).res[4];
        //for(int i = y - 1; i < ) // I have to check if a person is in specific square
    }
    else if (count == 1) {
        World::board[y - 1][x - 1].person = new Person();
        Images::fillSquare(y - 1, x - 1);
    }
        
    else
        cerr << "Can't produce few people not in a Village or City!";
}

void build_func(vector<string> args, bool start)
{
    string whatToBuild = args[0];
    Position pos = { stoi(args[1]), stoi(args[2]) };

    Position size = Configuration::conf["Sizes"][whatToBuild];

    //check if all the area is ground
    for (int i = pos.second - 1; i < pos.second + size.first - 1; i++) {
        for (int j = pos.first - 1; j < pos.first + size.second - 1; j++) {
            if (Tile* t = dynamic_cast<Tile*>(World::board[i][j].place.get())) {
                if (t->tileType != 1)
                    return;
                //cerr << "You can't build city not on ground!";
            }
            else
                return;
                //cerr << "You can't build city not on ground!";
        }
    }

    //check if existing way
    if (!start) {
        int count1 = 0, count2 = 0;
        bool flag = false;

        for (int i = pos.second - 1; i < pos.second + size.first - 1; i++) {

            if (pos.first - 2 >= 0) {
                if (dynamic_cast<Road*>(World::board[i][pos.first - 2].place.get()))
                    count1++;
                else if(whatToBuild=="Road" && dynamic_cast<VillageCity*>(World::board[i][pos.first - 2].place.get()))
                    count1++;
                else
                    count1 = 0;

                if (count1 == Configuration::conf["Sizes"]["Road"][0]) {
                    flag = true;
                    break;
                }
            }
            
            if (pos.first + size.second < World::board[i].size()) {
                if (dynamic_cast<Road*>(World::board[i][pos.first + size.second].place.get()))
                    count2++;
                else if(whatToBuild == "Road" && dynamic_cast<VillageCity*>(World::board[i][pos.first + size.second].place.get()))
                    count2++;
                else
                    count2 = 0;

                if (count2 == Configuration::conf["Sizes"]["Road"][0]) {
                    flag = true;
                    break;
                }
            }
                
        }

        count1 = count2 = 0;

        for (int j = pos.first - 1; j < pos.first + size.second - 1 && !flag; j++) {

            if (pos.second - 2 >= 0) {
                if (dynamic_cast<Road*>(World::board[pos.second - 2][j].place.get()))
                    count1++;
                else if (whatToBuild == "Road" && dynamic_cast<VillageCity*>(World::board[pos.second - 2][j].place.get()))
                    count1++;
                else
                    count1 = 0;

                if (count1 == Configuration::conf["Sizes"]["Road"][0]) {
                    flag = true;
                    break;
                }
            }

            if (pos.second + size.first < World::board.size()) {
                if (dynamic_cast<Road*>(World::board[pos.second + size.first][j].place.get()))
                    count2++;
                else if (whatToBuild == "Road" && dynamic_cast<VillageCity*>(World::board[pos.second + size.first][j].place.get()))
                    count2++;
                else
                    count2 = 0;

                if (count2 == Configuration::conf["Sizes"]["Road"][0]) {
                    flag = true;
                    break;
                }
            }
        }

        if (!flag)
            return;
            //cerr << "You can't the city, because there is no road here!";
    }


    shared_ptr<Place> place = nullptr;
    if (whatToBuild == "City")
        place.reset(new City());
    else if (whatToBuild == "Village")
        place.reset(new Village());
    else if (whatToBuild == "Road")
        place.reset(new Road());

    if (VillageCity* vc = dynamic_cast<VillageCity*>(place.get()))
        vc->completed = start;

    Resources tempRes = {0, 0, 0, 0, 1};

    for (int i = pos.second - 1; i < pos.second + size.first - 1; i++) {
        for (int j = pos.first - 1; j < pos.first + size.second - 1; j++) {
            World::board[i][j].place = place;

            if (whatToBuild == "Road")
                Images::fillSquare(i, j);

            if (VillageCity* v = dynamic_cast<VillageCity*>(place.get())) {
                if (World::board[i][j].person != nullptr)
                    v->c.check(v->r, tempRes);
            }
        }
    }

    Images::fillSquare(pos.second - 1, pos.first - 1);
}

void manufacture_func(vector<string> args, bool start)
{
    string whatToManufacture = args[0];
    Position pos = { stoi(args[1]), stoi(args[2]) };

    //only if we add Vehicle to our resources and capacities
    //VillageCity* vc = dynamic_cast<VillageCity*>(w.board[pos.second - 1][pos.first - 1].place.get());

    if (!start) {

        Resources* r;
        if (VillageCity* vc = dynamic_cast<VillageCity*>(World::board[pos.second - 1][pos.first - 1].place.get()))
            r = &vc->r;
        else if (Tile* t = dynamic_cast<Tile*>(World::board[pos.second - 1][pos.first - 1].place.get()))
            r = &t->r;
        else
            return; //cerr << "This place do not contain resources!";


        auto temp = Configuration::conf["Costs"][whatToManufacture];
        Resources tempRes;
        for (int i = 0; i < 5; i++)
        {
            tempRes.res[i] = temp[i];
        }
        if (*r < tempRes)
            return; //cerr << "This place do not contain enough resources!";
        else
            *r = *r - tempRes;
    }

    shared_ptr<Vehicle> vehicle = nullptr;
    if (whatToManufacture == "Car") {
        vehicle.reset(new Car());
        /*if (vc)
            vc->r.res[]++;*/
    }   
    else if (whatToManufacture == "Truck") {
        vehicle.reset(new Truck());
        /*if (vc)
            vc->r.res[]++;*/
    }
    else if (whatToManufacture == "Helicopter") {
        vehicle.reset(new Helicopter());
        /*if (vc)
            vc->r.res[]++;*/
    }

    Position size = Configuration::conf["Sizes"][whatToManufacture];///

    for (int i = pos.second - 1; i < pos.second + size.first - 1; i++) {
        for (int j = pos.first - 1; j < pos.first + size.second - 1; j++) {
            World::board[i][j].vehicle = vehicle;
        }
    }

    Images::fillSquare(pos.second - 1, pos.first - 1);

}

void makeEmpty_func(vector<string> args)
{
    Position pos = { stoi(args[0]), stoi(args[1]) };
    if (Tile* t = dynamic_cast<Tile*>(World::board[pos.second - 1][pos.first - 1].place.get()))
        t->r = { 0, 0, 0, 0, 0 };
    else if(VillageCity* vc = dynamic_cast<VillageCity*>(World::board[pos.second - 1][pos.first - 1].place.get()))
        vc->r = { 0, 0, 0, 0, 0 };
}