#include <initializer_list>
#include <vector>
#include <iostream>

using namespace std;

int return5th(std::initializer_list<int> vals){

    std::vector<int> valsVec (vals);

    return valsVec[4];

}

int main(){

    int temp;
    cout << "Entering text" << endl;

    cin >> temp;

    system("emacs /Volumes/GD/Drive/Uni/svnRepo/2021/s1/oop/practical-08-11/database/2/12.txt");

    cout << "done with text editing" << endl;

    return 0;
}