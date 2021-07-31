#include <iostream>
#include <unistd.h>
#include <string>
#include "httplib.h"
#include "stringFunctions.h"
#include "jsonResponseContainers.h"

using namespace std;
using namespace httplib;

const int microsecond = 1000000;
char idc;
int id;

int main() {
    Client cli("localhost", 8080);
    
    {
        if (auto res = cli.Get("/register")) {
            RegisterContainer response;
            response.JSONparser(res->body);
            if (response.inAction == true) {
                cout << "There's a game currently in action in the server\nplease ask the admin to restart." << flush;
                return 0;
            } else {
                id = response.id;
                cout << "You are player " << id+1 << endl;
            }
        } else {
            cout << "The admin hasn't set up the server. Ask them to do so" << endl;
            return 0;
        }
    }

    while (true) {
        if (auto res = cli.Get("/situationUpdate")) {
            for (int i = 0; i < 50; ++i) cout << "\n";
            
            SituationUpdateContainer currSituation;
            currSituation.JSONparser(res->body);
            
            if (currSituation.winner >= 1 and currSituation.winner <= 4) {
                cout << "\n\n\nPLAYER " << currSituation.winner << " HAS WON!\nquitting in 15 seconds...";
                cli.Get("/stop");
                usleep(15 * microsecond);
                return 0;        
            }
            if (currSituation.isStarted == false) {
                cout << "please wait for the other players to join..." << endl;
                usleep(0.5 * microsecond);
                continue;
            }
            
            cout << currSituation.boardSituation << flush;

            if (currSituation.currTurn == id) {
                MultipartFormDataItems param;
                bool notMoved = true;
                
                while (notMoved) {
                    string move;
                    cout << "Please choose your move below (b for Blocking, and w for walking):\n";
                    cin >> move;
                    while (move != "b" and move != "w") {
                        cout << "Please enter a correct action:\n";
                        cin >> move;
                    }

                    param.push_back({"id", int2String(id), "", ""});
                    param.push_back({"type", move, "", ""});

                    if (move == "w") {
                        string dir;
                        cout << "please choose your direction\n(u for up, d for down, l for left, r for right)\n";
                        cin >> dir;
                        while (dir != "u" and dir != "d" and dir != "l" and dir != "r") {
                            cout << "Please enter a correct direction:\n";
                            cin >> dir;
                        }
                        param.push_back({"dir", dir, "", ""});
                    } else if (move == "b") {
                        string X, Y, orientation;
                        cout << "please choose your coordinates below:\nx: " << flush;
                        cin >> X;
                        cout << "y: " << flush;
                        cin >> Y;

                        while (stringIsInt(X) == false or stringIsInt(Y) == false or 
                                string2Int(X) <= 0 or string2Int(X) > 11 or 
                                string2Int(Y) <= 0 or string2Int(Y) > 11) {
                            cout << "please enter correct coordinates:\nx: " << flush;
                            cin >> X;
                            cout << "y: " << flush;
                            cin >> Y;
                        }
                        param.push_back({"moveX", X, "", ""});
                        param.push_back({"moveY", Y, "", ""});

                        cout << "please choose your direction\n(v for vertical and h for horizontal)\n";
                        cin >> orientation;
                        while (orientation != "v" and orientation != "h") {
                            cout << "Please enter a correct orientation:\n";
                            cin >> orientation;
                        }
                        param.push_back({"orient", orientation, "", ""});
                    }

                    if (auto res2 = cli.Post("/makeMove", param)) {
                        MakeMoveContainer response2;
                        response2.JSONparser((res2->body));
                        ((response2.isDone == true)? notMoved = false: notMoved = true);
                        if (notMoved) cout << "That move is not possible, try again...\n";
                    } else {
                        cout << "connection to server was lost, quitting..." << endl;
                        return 0;            
                    }
                }
            } else
                cout << "player " << currSituation.currTurn+1 << "'s turn.\nplease be patient..." << endl;
        } else {
            cout << "connection to server was lost, quitting..." << endl;
            return 0;
        }
        
        usleep(0.05 * microsecond);
    }
    return 0;
}
