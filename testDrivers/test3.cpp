#include <filesystem>
#include <iostream>
#include <charconv>
#include "NicksObjVector.hpp"

namespace fs = std::filesystem;
using namespace std;

int main() {

    // char label[17];
    // label[0] = 'A';
    // int num = 58;
    // cout << label << endl;

    // std::to_chars(label + 1, label + 15, num);
    // cout << label << endl;

   NicksObjVector<int> a = {5,4,3,2,1};

   for (int i=0; i<a.size(); i++) {
       cout << "size: " << a.size() << endl;
       cout << a[i] << endl;
   }

    return 0;
}