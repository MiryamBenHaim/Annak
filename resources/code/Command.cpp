#include "Command.h"

const std::string Command::WORLD = "World";
const std::string Command::START = "Start";
const std::string Command::INPUT = "Input";
const std::string Command::ASSERTS = "Asserts";

// Function to map step name strings to enum values
StepName Command::getStepName(const std::string& name)
{
    static const std::unordered_map<std::string, StepName> stepNameMap = {
        {"Select", StepName::Select},
        {"Work", StepName::Work},
        {"Wait", StepName::Wait},
        {"Rain", StepName::Rain},
        {"Build", StepName::Build},
        {"People", StepName::People},
        {"Deposit", StepName::Deposit},
        {"TakeResources", StepName::TakeResources},
        {"Manufacture", StepName::Manufacture},
        {"Move", StepName::Move},
        {"Resource", StepName::Resource},
        {"Resources", StepName::Resources},
        {"MakeEmpty", StepName::MakeEmpty},
        {"SelectedCategory", StepName::SelectedCategory},
        {"SelectedResource", StepName::SelectedResource},
        {"SelectedComplete", StepName::SelectedComplete},
        {"CityCount", StepName::CityCount},
        {"VillageCount", StepName::VillageCount},
        {"RoadCount", StepName::RoadCount},
        {"SelectedCar", StepName::SelectedCar},
        {"SelectedTruck", StepName::SelectedTruck},
        {"SelectedPeople", StepName::SelectedPeople},
        {"CarCount", StepName::CarCount},
        {"TruckCount", StepName::TruckCount},
        {"HelicopterCount", StepName::HelicopterCount},
        {"SelectedCoordinates", StepName::SelectedCoordinates}
    };

    auto it = stepNameMap.find(name);
    return it != stepNameMap.end() ? it->second : StepName::Unknown;
}

//const std::string Command::WAIT = "Wait";
//
//const std::string Command::SELECT = "Select";
//const std::string Command::MOVE = "Move";
//const std::string Command::WORK = "Work";
//const std::string Command::DEPOSIT = "Deposit";
//const std::string Command::TAKE_RESOURCES = "TakeResources";
//const std::string Command::BUILD = "Build";
//const std::string Command::MANUFACTURE = "Manufacture";
//const std::string Command::PEOPLE = "People";
//const std::string Command::RESOURCE = "Resource";
//const std::string Command::RESOURCES = "Resources";
//const std::string Command::MAKE_EMPTY = "MakeEmpty";
//const std::string Command::RAIN = "Rain";
//const std::string Command::ROBBER = "Robber";
//const std::string Command::MAKE_ROBBER = "MakeRobber";

