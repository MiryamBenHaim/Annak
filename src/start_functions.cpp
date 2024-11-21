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
            default:
                break;
            }
        }
        catch (string msg) {
            cout << "ERROR! " << msg;
        }
    }
}