#include <iostream>
#include <unistd.h>
#include <string>
#include "httplib.h"
#include "stringFunctions.h"

using namespace std;
using namespace httplib;

const int microsecond = 1000000;
char idc;

int main() {
    Client cli("localhost", 8080);
    {
        if (auto res = cli.Get("/register")) {
            if (res->body == "gameInAction") {
                cout << "There's a game currently in action in the server\nplease ask the admin to restart." << flush;
                return 0;
            } else {
                idc = (res->body)[0];
                cout << "You are player " << char(idc+1) << endl;
            }
        } else {
            cout << "The admin hasn't set up the server. Ask them to do so" << endl;
            return 0;
        }
    }


    while (true) {
        if (auto res = cli.Get("/situationUpdate")) {
            //cerr << "response was " << res->body << endl;
            if (res->body[1] >= '1' and res->body[1] <= '4') {
                cout << "\n\n\nPLAYER " << res->body[0] << " HAS WON!\nquitting in 15 seconds...";
                cli.Get("/stop");
                usleep(15 * microsecond);
                return 0;        
            }
            if (res->body[1] == '5') {
                cout << "please wait for the other players to join..." << endl;
                usleep(3 * microsecond);
                continue;
            }
            cout << (res->body).substr(2) << flush;

            if ((res->body)[0] == idc) {
                MultipartFormDataItems param;
                string move;
                bool notMoved = true;
                while (notMoved) {
                    cout << "Please choose your move below (b for Blocking, and w for walking):\n";
                    cin >> move;
                    while (move != "b" and move != "w") {
                        cout << "Please enter a correct action:\n";
                        cin >> move;
                    }

                    string dir;
                    if (move == "w") {
                        cout << "please choose your direction\n(u for up, d for down, l for left, r for right)\n";
                        cin >> dir;
                        while (dir != "u" and dir != "d" and dir != "l" and dir != "r") {
                            cout << "Please enter a correct direction:\n";
                            cin >> dir;
                        }
                        //cerr << "dir before " << dir << endl;
                        dir = idc + dir;
                        //cerr << "dir after " << dir << endl;
                        param = { {"walk", dir, "", ""} };
                    } else {
                        string tmpX, tmpY;
                        cout << "please choose your coordinates below:\nx: " << flush;
                        cin >> tmpX;
                        cout << "y: " << flush;
                        cin >> tmpY;

                        while (stringIsInt(tmpX) == false or stringIsInt(tmpY) == false or 
                                string2Int(tmpX) <= 0 or string2Int(tmpX) > 11 or 
                                string2Int(tmpY) <= 0 or string2Int(tmpY) > 11) {
                            cout << "please enter correct coordinates:\nx: " << flush;
                            cin >> tmpX;
                            cout << "y: " << flush;
                            cin >> tmpY;
                        }
                        int X = string2Int(tmpX), Y = string2Int(tmpY);

                        cout << "please choose your direction\n(v for vertical and h for horizontal)\n";
                        cin >> dir;
                        while (dir != "v" and dir != "h") {
                            cout << "Please enter a correct orientation:\n";
                            cin >> dir;
                        }

                        dir += char(X);
                        dir += char(Y);
                        dir = idc + dir;
                        param = { {"block", dir, "", ""} };
                    }
                    if (auto res2 = cli.Post("/makeMove", param)) {
                        (((res2->body)[0] == '0')? notMoved = true: notMoved = false);
                        if (notMoved) cout << "That move is not possible, try again...\n";
                    } else {
                        cout << "connection to server was lost, quitting..." << endl;
                        return 0;            
                    }
                }
            } else
                cout << "player " << char((res->body)[0]+1) << "'s turn.\nplease be patient..." << endl;
        } else {
            cout << "connection to server was lost, quitting..." << endl;
            return 0;
        }
        
        usleep(3 * microsecond);
    }
    return 0;
}