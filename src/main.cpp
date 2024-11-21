#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "../resources/code/Input.h"

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
#include "input_functions.h"
#include "asserts_functions.h"

#include "mouse_events.h"

using namespace cv;
using namespace std;


////////////////////////////

vector<vector<int>>* fixStart(vector<vector<string>>& vec) {
    vector<vector<int>>* good = new vector<vector<int>>;
    vector<int> temp;
    for (int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++)
            temp.push_back(stoi(vec[i][j]));
        good->push_back(temp);
        temp.clear();
    }
    return good;
}

///////////////////////

//------------------------  main  --------------------------

int main()
{

#pragma region Get Input

    Input in("../txt_input.txt", "../txt_output.txt");
    in.parse_and_store();

#pragma endregion

//-------------------------------------

#pragma region +World

    vector<vector<int>> myTiles = *fixStart(in.world->data);

    World::addTiles(myTiles);

#pragma endregion

//-------------------------------------

#pragma region +Start

    StartFunc(in.start);
    World::printBoard();

#pragma endregion

//-------------------------------------

#pragma region +Input

    Position* pos = new Position(0, 0);
    InputFunc(in.steps, pos);

#pragma endregion

//-------------------------------------

#pragma region +Asserts

    AssertsFunc(in.asserts, *pos);
    cout << "-----------------------------------\n" << endl;

#pragma endregion

//-------------------------------------

    return 0;
}