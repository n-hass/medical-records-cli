#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main() {
    fs::path a ("/Volumes/GD\\testdir");

    cout << fs::path::preferred_separator << endl;

    return 0;
};