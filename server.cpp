#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <vector>
#include <string>
#include "utils/httplib.h"
#include "board.h"
#include "utils/stringFunctions.h"
#include "utils/jsonResponseContainers.h"

using namespace httplib;
using namespace std;

int main() {
    string tmpN;
    int n;
    cout << "Please enter the player amount below:\n";
    cin >> tmpN;
    while (stringIsInt(tmpN) == false or string2Int(tmpN) < 2 or string2Int(tmpN) > 4) {
        cout << "the amount should be 2-4 players, please choose again:\n";
        cin >> tmpN;
    }
    n = string2Int(tmpN);
    Board game = Board(n);
    
    Server svr;
    int currTurn = 0;

    svr.Get("/situationUpdate", [&](const Request& req, Response& res) {
        SituationUpdateContainer response;
        response.boardSituation = game.printBoard();
        response.winner = game.whichInMiddle();
        response.currTurn = currTurn;
        response.isStarted = ((game.getPlayer(n-1) != NULL)?true:false);
        
        cerr << "sent response:\n" << response.JSONserializer() << "\n\n\n";
        res.set_content(response.JSONserializer(), "success");
    });

    svr.Post("/makeMove", [&](const Request& req, Response& res) {
        MakeMoveContainer response;

        const auto& id = req.get_file_value("id");
        const auto& type = req.get_file_value("type");
        if (type.content == "w") {
            const auto& dir = req.get_file_value("dir");
            Direction drr;
            if (dir.content == "u") drr = UP;
            else if (dir.content == "d") drr = DOWN;
            else if (dir.content == "l") drr = LEFT;
            else if (dir.content == "r") drr = RIGHT;

            response.isDone = game.setPlayer(*game.getPlayer(string2Int(id.content)), drr);
        } else if (type.content == "b") {
            const auto& moveX = req.get_file_value("moveX");
            const auto& moveY = req.get_file_value("moveY");
            const auto& orient = req.get_file_value("orient");
            
            Direction drr;
            if (orient.content == "v") drr = UP;
            if (orient.content == "h") drr = LEFT;
            
            int X = string2Int(moveX.content);
            int Y = string2Int(moveY.content);

            response.isDone = game.setBlock(abs(11-Y), X-1, drr);
        }
        if (response.isDone == true) currTurn = (currTurn+1)%n;
        cerr << "sent response:\n" << response.JSONserializer() << "\n\n\n";
        res.set_content(response.JSONserializer(), "success");
    });

    svr.Get("/register", [&](const Request& req, Response& res) {
        RegisterContainer response;
        if (game.getPlayer(n-1) != NULL) {
            response.inAction = true;
            response.id = 0;
        } else {
            response.inAction = false;
            int id = 0;
            while (game.getPlayer(id) != NULL) id++;
            game.startPlayer(id);
            response.id = id;
        }
        cerr << "sent response:\n" << response.JSONserializer() << "\n\n\n";
        res.set_content(response.JSONserializer(), "success");
    });

    svr.Get("/quit", [&](const Request& req, Response& res) {
        svr.stop();
    });

    cout << "server in action..." << endl;
    svr.listen("localhost", 8080);
    return 0;
}
