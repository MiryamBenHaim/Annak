#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <queue>

class Configuration {
public:
    static nlohmann::json conf;

    static std::vector<std::string> Tiles;

    static std::vector<std::string> ResourceTypes;
};

#endif // __CONFIGURATION__