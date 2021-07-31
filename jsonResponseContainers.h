#include <string>
#include "stringFunctions.h"

struct SituationUpdateContainer {
    std::string boardSituation;
    bool isStarted;
    int currTurn;
    int winner;
    
    SituationUpdateContainer(bool=false, std::string="", int=0, int=0);
    void JSONparser(std::string);
    std::string JSONserializer();
};

struct RegisterContainer {
    bool inAction;
    int id;

    RegisterContainer(bool=true, int=0);
    void JSONparser(std::string);
    std::string JSONserializer();
};

struct MakeMoveContainer {
    bool isDone;

    MakeMoveContainer(bool=false);
    void JSONparser(std::string);
    std::string JSONserializer();
};
