#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <vector>
#include "httplib.h"
#include "board.h"

using namespace httplib;
using namespace std;

int main() {
    int n;
    cout << "Please enter the player amount below:\n";
    cin >> n;
    Board game = Board(n);
    
    Server svr;
    int currTurn = 0;

    svr.Get("/situationUpdate", [&](const Request& req, Response& res) {
        string response = game.printBoard();
        if (game.getPlayer(n-1) != NULL) response = char(game.whichInMiddle()+'0') + response;
        else response = '5' + response;
        response = char(currTurn+'0') + response;
        res.set_content(response, "success");
    });

    svr.Post("/makeMove", [&](const Request& req, Response& res) {
        bool isPossible;
        if (req.has_file("walk")) {
            const auto& file = req.get_file_value("walk");
            //cerr << " * " << file.content << endl;
            Direction drr;
            //cerr << "direction " << file.content[1] << endl;
            //cerr << int(file.content[0]-'0') << endl;
            //cerr << game.getPlayer(file.content[0]-'0')->getPosX() << " " << game.getPlayer(file.content[0]-'0')->getPosY() << endl;
            if (file.content[1] == 'u') drr = UP;
            if (file.content[1] == 'd') drr = DOWN;
            if (file.content[1] == 'l') drr = LEFT;
            if (file.content[1] == 'r') drr = RIGHT;
            
            isPossible = game.setPlayer(*game.getPlayer(file.content[0]-'0'), drr);
        } else if (req.has_file("block")) {
            const auto& file = req.get_file_value("block");
            Direction drr;
            if (file.content[1] == 'v') drr = UP;
            if (file.content[1] == 'h') drr = LEFT;
            
            int X = file.content[2];
            int Y = file.content[3];

            isPossible = game.setBlock(X, Y, drr);
        }
        string response = (((isPossible == true)?"1":"0"));
        if (isPossible == true) currTurn = (currTurn+1)%n;
        res.set_content(response, "success");
    });

    svr.Get("/register", [&](const Request& req, Response& res) {
        if (game.getPlayer(n-1) != NULL) {
            res.set_content("gameInAction", "success");
        } else {
            int id = 0;
            while (game.getPlayer(id) != NULL) id++;
            string response;
            response += char(id+'0');
            game.startPlayer(id);
            res.set_content(response, "success");
        }
    });

    cout << "server in action..." << endl;
    svr.listen("localhost", 8080);
    return 0;
}