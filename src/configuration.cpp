#include "configuration.h"
using json = nlohmann::json;
using namespace std;

//load configuration.json
json* readData() {
    ifstream f("../configuration.json");
    json* data = new json(json::parse(f));
    return data;
}

json Configuration::conf = *(readData());

vector<string> Configuration::Tiles = {"Ground", "Water", "Forest", "Field", "IronMine", "BlocksMine"};

vector<string> Configuration::ResourceTypes = { "Wood", "Wool", "Iron", "Blocks", "People" };