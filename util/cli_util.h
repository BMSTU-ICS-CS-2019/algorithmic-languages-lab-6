#ifndef LAB_6_CLI_UTIL_H
#define LAB_6_CLI_UTIL_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T>
inline static T cli_read(const string &message) {
    cout << message << endl;
    T value;
    cin >> value;

    return value;
}

#endif //LAB_6_CLI_UTIL_H
