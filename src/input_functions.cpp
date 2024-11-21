#include "input_functions.h"
using namespace std;


void InputFunc(vector<shared_ptr<Command>> steps, Position* p)
{
    //Select
    Square s;
    //Work
    //Rain
    //Wait
    vector<shared_ptr<Command>> whatToDo;

    ////////////////
    //Build (city/ village/ road) city/ village- check toching road!
    //Wait
    //Deposit -take from the car to the square
    //TakeResources -take from the square and put in the car
    //People

    StepName stepName;
    for (int i = 0; i < steps.size(); i++) {
        stepName = Command::getStepName(steps[i]->name);
        try {
            switch (stepName) {
            case StepName::Work: {
                whatToDo.push_back(steps[i]);
                break;
            }
            case StepName::Move: {
                whatToDo.push_back(steps[i]);
                break;
            }
            case StepName::Rain: {
                whatToDo.push_back(steps[i]);
                break;
            }
            case StepName::Deposit: {
                whatToDo.push_back(steps[i]);
                break;
            }
            case StepName::TakeResources: {
                whatToDo.push_back(steps[i]);
                break;
            }
            case StepName::Wait: {
                wait_func(whatToDo, stoi(steps[i]->arguments[0]), p);
                break;
            }
            case StepName::Build: {
                build_func(steps[i]->arguments, false);
                break;
            }
            case StepName::Select: {
                s = select_func(steps[i]->arguments, p);
                break;
            }
            case StepName::People: {
                people_func(steps[i]->arguments);
                break;
            }
            case StepName::Manufacture: {
                manufacture_func(steps[i]->arguments, false);
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

#pragma region Go Function

vector<Position> generateDirectWay(Position& src, Position& dest)
{
    vector<Position> way;

    int dx = dest.first - src.first;
    int dy = dest.second - src.second;

    if (abs(dx) >= abs(dy))
        for (int x = src.first; ; dx < 0 ? x-- : x++) {
            way.push_back({ x, src.second + dy * (x - src.first) / dx });
            if (x == src.first + dx)
                break;
        }
            
    else
        for (int y = src.second; ; dy < 0 ? y-- : y++) {
            way.push_back({ src.first + dx * (y - src.second) / dy, y });
            if (y == src.second + dy)
                break;
        }

    return way;
}

vector<Position> generateWayOnRoads(Position& src, Position& dest)
{
    shared_ptr<Vehicle> v = World::board[src.second - 1][src.first - 1].vehicle;

    Position size;
    if (dynamic_cast<Car*>(v.get()))
        size = Configuration::conf["Sizes"]["Car"];
    else if (dynamic_cast<Truck*>(v.get()))
        size = Configuration::conf["Sizes"]["Truck"];


    vector<Position> whereToGo = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    
    World::board[src.second - 1][src.first - 1].dist = 0;
    queue<Position> Q;
    Q.push(src);
    Position tempPos;
    Position p;

    while (!Q.empty())
    {
        tempPos = Q.front();
        Q.pop();

        for (size_t i = 0; i < whereToGo.size(); i++)
        {
            p = { tempPos.first + whereToGo[i].first , tempPos.second + whereToGo[i].second};
            if (tempPos == dest || p.first == 0 || p.second == 0 || p.second == World::board.size() || p.first == World::board[p.second-1].size())
                break;
            bool flag = true;
            for (int x = 0; x < 2 && flag; x++) {
                for (int y = 0; y < 2 && flag; y++) {
                    Position tempP = { p.first + (size.first * x), p.second + (size.second * y) };
                    if (x != 0)
                        tempP.first--;
                    if (y != 0)
                        tempP.second--;
                    if ((
                        !dynamic_cast<Road*>(World::board[tempP.second - 1][tempP.first - 1].place.get())
                        && !dynamic_cast<VillageCity*>(World::board[tempP.second - 1][tempP.first - 1].place.get())
                        )
                        )
                        flag = false;
                }
            }
            if ((flag && World::board[p.second - 1][p.first - 1].dist == -1) || p == dest) {
                World::board[p.second - 1][p.first - 1].dist = World::board[tempPos.second - 1][tempPos.first - 1].dist + 1;
                World::board[p.second - 1][p.first - 1].parent = tempPos;
                Q.push(p);
            }
        }
        if (tempPos == dest)
            break;
    }

    int counter = 0;
    vector<Position> way;
    //generate the way using the parents
    if (tempPos == dest) {
        while (tempPos != src) {
            if (
                World::board[tempPos.second - 1][tempPos.first - 1].vehicle.get() == nullptr
                || World::board[tempPos.second - 1][tempPos.first - 1].vehicle.get() == World::board[src.second - 1][src.first - 1].vehicle.get()
                )
                way.push_back(tempPos);
            tempPos = World::board[tempPos.second - 1][tempPos.first - 1].parent;
            counter++;
        }
        if (
            World::board[tempPos.second - 1][tempPos.first - 1].vehicle.get() == nullptr
            || World::board[tempPos.second - 1][tempPos.first - 1].vehicle.get() == World::board[src.second - 1][src.first - 1].vehicle.get()
            )
        way.push_back(tempPos);
        counter++;
    }
    else
        way.push_back(src);
        
    //loop for init all we touch to dest = -1

    int i = src.second - 2 - way.size();
    if (i < 0)
        i = 0;
    for (; (i < src.second + way.size()) && (i < World::board.size()); i++) {
        int j = src.first - 2 - way.size();
        if (j < 0)
            j = 0;
        for (; (j < src.first + way.size()) && (j < World::board[i].size()); j++) {
            World::board[i][j].dist = -1;
        }
    }

    reverse(way.begin(), way.end());

    return way;
}

bool move(Position* src, Position& dest)
{
    if (abs(src->first - dest.first) > 1 || abs(src->second - dest.second) > 1)
        return false;// cerr << "The destination is far!";
    
    Square& sSrc = World::board[src->second - 1][src->first - 1];
    Square& sDest = World::board[dest.second - 1][dest.first - 1];

    string type;
    if (sSrc.person != nullptr)
        type = "People";
    else if (dynamic_cast<Car*>(sSrc.vehicle.get()))
        type = "Car";
    else if (dynamic_cast<Truck*>(sSrc.vehicle.get()))
        type = "Truck";
    else if (dynamic_cast<Helicopter*>(sSrc.vehicle.get()))
        type = "Helicopter";

    Position size = Configuration::conf["Sizes"][type];

    for (int i = dest.second - 1; i < dest.second - 1 + size.first; i++) {
        for (int j = dest.first - 1; j < dest.first - 1 + size.second; j++) {
            if (World::board[i][j].person != nullptr ||
                (World::board[i][j].vehicle.get() != nullptr &&
                    World::board[i][j].vehicle.get() != sSrc.vehicle.get()
                ))// || dynamic_cast<VillageCity*>(sDest.place.get()))
                return false;
        }
    }
    
    /*else if(Tile* t =  dynamic_cast<Tile*>(sDest.place.get()))
        if(t->tileType == 2)
            return false;*/

    //check if we have to add the person to the city
    /*if (VillageCity* vc = dynamic_cast<VillageCity*>(sDest.place.get()))
        vc->r.res[4]++;*/
        

    if (type == "People") {
        Person* person = sSrc.person;
        sSrc.person = nullptr;

        Images::fillOriginSquare(src->second - 1, src->first - 1);
        *src = dest;
        sDest.person = person;
        Images::fillSquare(dest.second - 1, dest.first - 1);

        return true;
    }

    shared_ptr<Vehicle> v = sSrc.vehicle;

    //**check what with the size of the car/truck

    for (int i = max(0, src->second - size.second); i < src->second; i++) {
        for (int j = max(0, src->first - size.first); j < src->first; j++) {
            if (World::board[i][j].vehicle.get() == v.get()) {
                *src = { j + 1, i + 1 };
                break;
            }
        }
    }

    for (int i = src->second - 1; i < src->second + size.first - 1; i++) {
        for (int j = src->first - 1; j < src->first + size.second - 1; j++) {
            World::board[i][j].vehicle.reset();
            if (!dynamic_cast<VillageCity*>(World::board[i][j].place.get()))
                Images::fillOriginSquare(i, j);
        }
    }

    *src = dest;
    
    for (int i = src->second - 1; i < src->second + size.first - 1; i++) {
        for (int j = src->first - 1; j < src->first + size.second - 1; j++) {
            World::board[i][j].vehicle = v;
        }
    }

    if (!dynamic_cast<VillageCity*>(World::board[src->second - 1][src->first - 1].place.get()))
        Images::fillSquare(src->second - 1, src->first - 1);

    return true;
}

bool goOnSquare(Position* src, Position& dest)
{
    vector<Position> way = generateDirectWay(*src, dest);
    Square& s = World::board[src->second - 1][src->first - 1];
    //mabey this will do problems with pointers who are not shared_ptr
    Movies* m;
    (s.person != nullptr) ? m = s.person : m = s.vehicle.get();

    double sizeStep;
    (s.person != nullptr) ? sizeStep = Configuration::conf["Speeds"]["People"] : sizeStep = Configuration::conf["Speeds"]["Helicopter"];

    int i = 1;
    //while (time-- && i < way.size()) {
        m->extraStep += sizeStep;
        //m->extraStep += 1;
        if (m->extraStep > 1) {
            m->extraStep -= 1;
            if (!move(src, way[i]))
                return false;// break;
            i++;
        }
    //}

    return i == way.size();
}

bool goOnRoad(Position* src, Position& dest)
{
    if (!dynamic_cast<Road*>(World::board[dest.second - 1][dest.first - 1].place.get()))
        return false;

    vector<Position> way = generateWayOnRoads(*src, dest);
    if (way.size() == 1)
        return false;

    int i = 1;
    if (!move(src, way[i]))
        return false;// break;
    i++;

    return i == way.size();
}

bool go(Position* src, Position& dest)
{
    if (*src == dest)
        return true;

    //what if it is a car? OK...
    Square& s = World::board[src->second - 1][src->first - 1];
    Person* p = s.person;
    if (p == nullptr) {
        if (Helicopter* h = dynamic_cast<Helicopter*>(s.vehicle.get()))
            return goOnSquare(src, dest);
        else if (Vehicle* v = dynamic_cast<Vehicle*>(s.vehicle.get())) {

            Square& s = World::board[src->second - 1][src->first - 1];


            double sizeStep;
            if (dynamic_cast<Car*>(v))
                sizeStep = Configuration::conf["Speeds"]["Car"];
            else if (dynamic_cast<Truck*>(v))
                sizeStep = Configuration::conf["Speeds"]["Truck"];

            v->extraStep += sizeStep;
            if (v->extraStep > 1) {
                v->extraStep -= 1;
                return goOnRoad(src, dest);
            }
            return false;
        }
    }
    return false;// goOnSquare(src, dest);
}

#pragma endregion


///////
void deposit_func(vector<string> args, int time, Position* src) {
    Position dest = { stoi(args[0]), stoi(args[1]) };
    if (go(src, dest)) {
        if (VillageCity* vc = dynamic_cast<VillageCity*>(World::board[dest.second - 1][dest.first - 1].place.get()))
            World::board[src->second - 1][src->first - 1].vehicle->r = vc->c.check(vc->r, World::board[src->second - 1][src->first - 1].vehicle->r);
    }
}

void takeResources_func(vector<string>& args, int time, Position* src) {
    Position* dest = new Position();
    *dest = { stoi(args[0]), stoi(args[1]) };
    bool b = go(src, *dest);
    /*args[0] = src->first; ///do we need casting?
    args[1] = src->second;*/

    if (b) {
        if (VillageCity* vc = dynamic_cast<VillageCity*>(World::board[dest->second - 1][dest->first - 1].place.get()))
            vc->r = World::board[dest->second - 1][dest->first - 1].vehicle->c.check(World::board[dest->second - 1][dest->first - 1].vehicle->r, vc->r);
    }
}
//////

void work_func(vector<string> args, Position* src)
{
    Position dest = { stoi(args[0]), stoi(args[1]) };
    
    if (go(src, dest))//check if consider coming to this tile, and not to the specific position
        if (Tile* t = dynamic_cast<Tile*>(World::board[src->second - 1][src->first - 1].place.get()))
            t->r = { 0,0,0,0 };//t->r = t->r - t->r;
}

void move_func(vector<string> args, Position* src)
{
    Position dest = { stoi(args[0]), stoi(args[1]) };
    go(src, dest);
}

void rain_func() {
    int i = 0, j = 0;
    for (; i < World::board.size(); i+=5) {
        for (j = 0; j < World::board[i].size(); j+=5) {
            if (Tile* t = dynamic_cast<Tile*>(World::board[i][j].place.get())) {
                if (t->tileType == 3)
                    t->r.res[0] += 1 / 2000;
                else if(t->tileType == 4)
                    t->r.res[1] += 1 / 1000;
            }   
        }
    }
}

void wait_func(vector<shared_ptr<Command>>& whatToDo, int time, Position* p)
{
    StepName stepName;
    while (time--) {
        for (int i = 0; i < whatToDo.size(); i++) {
            stepName = Command::getStepName(whatToDo[i]->name);
            switch (stepName) {
            case StepName::Work: {
                work_func(whatToDo[i]->arguments, p);
                break;
            }
            case StepName::Move: {
                move_func(whatToDo[i]->arguments, p);
                break;
            }
            case StepName::Rain: {
                if (stoi(whatToDo[i]->arguments[0]) > 0) {
                    whatToDo[i]->arguments[0] = to_string(stoi(whatToDo[i]->arguments[0]) - 1);
                    rain_func();
                }
                else
                    whatToDo.erase(whatToDo.begin() + i);

                break;
            }
            case StepName::Deposit: {
                deposit_func(whatToDo[i]->arguments, time, p);
                break;
            }
            case StepName::TakeResources: {
                takeResources_func(whatToDo[i]->arguments, time, p);
                break;
            }
            default:
                break;
            }
        }

        cv::imshow("Board", Images::img);
        cv::waitKey(1);
    }
}

Square& select_func(vector<string>& pos, Position* p) {
    *p = { stoi(pos[0]), stoi(pos[1]) };

    return World::board[p->second - 1][p->first - 1];
}