#include <string>
#include "stringFunctions.h"
#include "jsonResponseContainers.h"

SituationUpdateContainer::SituationUpdateContainer(bool isStart, std::string situation, int turn, int win) {
    boardSituation = situation;
    isStarted = isStart;
    currTurn = turn;
    winner = win;
}

std::string SituationUpdateContainer::JSONserializer() {
    std::string json;
    json += "{\n";
    json += "   \"isStarted\": ";
    json += ((isStarted==true)?"true":"false");
    json += ",\n";
    json += "   \"currTurn\": \"" + int2String(currTurn) + "\",\n";
    json += "   \"winner\": \"" + int2String(winner) + "\",\n";
    json += "   \"boardSituation\": \"" + boardSituation + "\"\n";
    json += "}";
    return json;
}

void SituationUpdateContainer::JSONparser(std::string json) {
    int pos;
    pos = stringFind(json, "\"isStarted\"") + (int)std::string("\"isStarted\"").size() + 2;
    if (json.substr(pos, 4) == "true") {
        isStarted = true;
    } else {
        isStarted = false;
    }
    
    pos = stringFind(json, "\"currTurn\"") + (int)std::string("\"currTurn\"").size() + 3;
    currTurn = string2Int(json.substr(pos, 1));

    pos = stringFind(json, "\"winner\"") + (int)std::string("\"winner\"").size() + 3;
    winner = string2Int(json.substr(pos, 1));

    pos = stringFind(json, "\"boardSituation\"") + (int)std::string("\"boardSituation\"").size() + 3;
    int posEnd = pos;
    for (int i = pos; i < (int)json.size(); ++i) 
        if (json[i] == '\"') {
            posEnd = i+1;
            break;
        }
    boardSituation = json.substr(pos, posEnd-pos-1);

    return;
}

RegisterContainer::RegisterContainer(bool inAct, int idd) {
    id = idd;
    inAction = inAct;
}

std::string RegisterContainer::JSONserializer() {
    std::string json;
    json += "{\n";
    json += "   \"inAction\": ";
    json += ((inAction==true)?"true":"false");
    json += ",\n";
    json += "   \"id\": \"" + int2String(id) + "\"\n";
    json += "}";
    return json;
}

void RegisterContainer::JSONparser(std::string json) {
    int pos = stringFind(json, "\"id\"") + (int)std::string("\"id\"").size() + 3;
    int posEnd = pos;
    for (int i = pos; i < (int)json.size(); ++i) 
        if (json[i] >= '0' and json[i] <= '9') {
            posEnd = i+1;
            break;
        }
    id = string2Int(json.substr(pos, posEnd-pos));

    pos = stringFind(json, "\"inAction\"") + (int)std::string("\"inAction\"").size() + 2;
    if (json.substr(pos, 4) == "true") {
        inAction = true;
    } else {
        inAction = false;
    }
}

MakeMoveContainer::MakeMoveContainer(bool isDonee) {
    isDone = isDonee;
}

std::string MakeMoveContainer::JSONserializer() {
    std::string json;
    json += "{\n";
    json += "   \"isDone\": ";
    json += ((isDone == true)?"true":"false");
    json += "\n";
    json += "}";
    return json;
}

void MakeMoveContainer::JSONparser(std::string json) {
    int pos;
    pos = stringFind(json, "\"isDone\"") + (int)std::string("\"isDone\"").size() + 2;
    if (json.substr(pos, 4) == "true") {
        isDone = true;
    } else {
        isDone = false;
    }
}
