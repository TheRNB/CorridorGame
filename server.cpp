#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "player.h"
#include "board.h"

using namespace httplib;
using namespace std;

int main() {
    httplib::Server svr;
    std::cerr << "TEST1" << std::endl;
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
    });
    std::cerr << "TEST2" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 1;
}