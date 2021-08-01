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

std::string int2String (int num) {
    std::string result;
    while (num > 0) {
        result = char((num%10)+'0') + result;
        num /= 10;
    }

    if ((int)result.size() == 0) result = "0";

    return result;
}

int stringFind(std::string base, std::string query) {
    int pos;
    for (int i = 0; i <= (int)base.size()-(int)query.size(); ++i) {
        bool isPresent = true;
        for (int j = 0; j < (int)query.size(); ++j) {
            if (base[i+j] != query[j]) {
                isPresent = false;
                break;
            }
        }
        if (isPresent == true) {
            pos = i;
            break;
        }
    }
    return pos;
}
