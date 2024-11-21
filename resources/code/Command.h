#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Enum for step names
enum class StepName {
    Select,
    Work,
    Wait,
    Rain,
    Build,
    People,
    Deposit,
    TakeResources,
    Manufacture,
    Move,
    Resource,
    Resources,
    MakeEmpty,
    SelectedCategory,
    SelectedResource,
    SelectedComplete,
    CityCount,
    VillageCount,
    RoadCount,
    SelectedCar,
    SelectedTruck,
    SelectedPeople,
    CarCount,
    TruckCount,
    HelicopterCount,
    SelectedCoordinates,
    Unknown
};

class Command
{
public:
    Command(const std::string& _name): name(_name) { }

    std::string name;
    std::vector<std::string> arguments;
    std::vector< std::vector<std::string> > data;

    // Function to map step name strings to enum values
    static StepName getStepName(const std::string& name);

    static const std::string WORLD;
    static const std::string START;
    static const std::string INPUT;
    static const std::string ASSERTS;

    /*static const std::string WAIT;

    static const std::string SELECT;
    static const std::string MOVE;
    static const std::string WORK;
    static const std::string DEPOSIT;
    static const std::string TAKE_RESOURCES;
    static const std::string BUILD;
    static const std::string MANUFACTURE;
    static const std::string PEOPLE;
    static const std::string RESOURCE;
    static const std::string RESOURCES;
    static const std::string MAKE_EMPTY;
    static const std::string RAIN;
    static const std::string ROBBER;
    static const std::string MAKE_ROBBER;*/
};



