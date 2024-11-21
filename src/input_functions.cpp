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
            case StepName::Select: {
                s = select_func(steps[i]->arguments, p);
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

Square& select_func(vector<string>& pos, Position* p) {
    *p = { stoi(pos[0]), stoi(pos[1]) };

    return World::board[p->second - 1][p->first - 1];
}