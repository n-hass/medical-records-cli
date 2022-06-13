#include "Logger.hpp"
#include <iostream>
#include <filesystem>

using std::cin; using std::cout; using std::endl;
namespace fs = std::filesystem;

int main() {

    Logger log;

    log.start("/Users/nh/Desktop", "test.log");

    char test[65] = "abcd test";

    log << test;

    log.insertBreak();

    bool a = fs::exists("/Users/nh/Desktop/testFile123.dat");
    cout << a << endl;


    return 0;
}