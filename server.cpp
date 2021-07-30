#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <vector>
#include "httplib.h"
#include "board.h"

using namespace httplib;
using namespace std;
//enum Direction {RIGHT=0, UP, LEFT, DOWN};

int main() {
    int n;
    cout << "Please enter the player amount below:\n";
    cin >> n;
    Board game = Board(n);
    
    Server svr;
    int currTurn = 0;

    svr.Get("/situationUpdate", [&](const Request& req, Response& res) {
        string response = game.printBoard();
        response = char(game.whichInMiddle()) + response;
        response = char(currTurn) + response;
        res.set_content(response, "success");
    });

    svr.Post("/makeMove", [&](const Request& req, Response& res) {
        bool isPossible;
        if (req.has_file("walk")) {
            const auto& file = req.get_file_value("walk");
            Direction drr;
            if (file.content[1] == 'u') drr = UP;
            if (file.content[1] == 'd') drr = DOWN;
            if (file.content[1] == 'l') drr = LEFT;
            if (file.content[1] == 'r') drr = RIGHT;
            
            isPossible = game.setPlayer(game.getPlayer(file.content[0]), drr);
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
        res.set_content(response, "success");
    });

    svr.listen("localhost", 8080);
    return 0;
}