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

    svr.listen("localhost", 8080);
    return 0;
}