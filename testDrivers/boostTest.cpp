#include <iostream>
#include <fstream>
#include "NicksObjVector.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace fs=std::filesystem;
using namespace std;

// extern std::string exec(const char* cmd, bool silent);



int main(int writeOut){

    // fs::path pathDir ("/Volumes/GD/testdir/oh yes") ;

    NicksObjVector<int> a {5,3,1,5,6};

    // new file
    if (writeOut) {
        std::ofstream ofs( "archive.dat" );
        boost::archive::text_oarchive arOut (ofs);
        
        // Save the data
        arOut & a;

        ofs.close();
    }

    NicksObjVector<int> b;


    // load file
    std::ifstream ifs( "archive.dat" );
    boost::archive::text_iarchive arIn (ifs);
    
    // Save the data
    arIn & b;

    ifs.close();

    for (int i=0; i<a.size(); i++) {
        if (a[i] != b[i]){
            cout << "no match" << endl;
        }
    }



    return 0;
}   