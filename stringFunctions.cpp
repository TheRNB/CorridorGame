#include <string>

bool stringIsInt (std::string input) {
    if ((int)input.size() == 0) return false;
    for (int i = 0; i < (int)input.size(); ++i) {
        if (input[i] < '0' or input[i] > '9')
            return false;
    }
    return true;
}

int string2Int (std::string input) {
    int tmp = 0;
    for (int i = 0; i < (int)input.size(); ++i) {
        tmp *= 10;
        tmp += int(input[i]-'0');
    }
    return tmp;
}