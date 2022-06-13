#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


#include "Patient.h"
#include "Doctor.h"
#include "Record.h"
#include "TextRecord.h"
#include "ImgRecord.h"


#include "NicksObjVector.hpp"

using namespace std;
namespace fs=boost::filesystem;

// extern std::string exec(const char* cmd, bool silent);


class DataFiles {
    public:
    std::string msg;
};

class Hop {

    public:
    Hop();
    ~Hop() {};
    int a;
    int b;
    static int init;
    int getC() { return c;}

    private:
    int c;
};

class Foo : public Hop {
    public:
    int extra;

    vector<DataFiles> files;

    Foo() {
        extra = 5;
    }
    ~Foo() {

    }
    
};

int Hop::init = 0;

Hop::Hop(){
    a = init;
    c = init;
    init++;
    
}


int main_playground(){

    fs::create_directories("/Volumes/GD/testdir");
    fs::current_path("/Volumes/GD/testdir");

    vector<Hop*> all;
    Hop* a = new Hop;
    Hop* b = new Hop; 
    Hop* c = new Foo;
    Hop* d = new Foo;


    all.push_back(a);
    all.push_back(b);
    all.push_back(c);
    all.push_back(d);
    
    for (int i=0; i<all.size(); i++){
        cout << all[i]->a << all[i]->getC() << endl;
    }

    NicksObjVector<int> nums;

    nums.push(1);
    nums.push(2);
    nums.push(3);


    cout << "saving" << endl;
    // new file
    std::ofstream ofs( "numArchive.dat");
    boost::archive::text_oarchive outArch (ofs);
    
    // Save the data
    outArch & nums;

    ofs.close();


    NicksObjVector<int> numsTwo;

    std::ifstream ifs( "numArchive.dat");

    boost::archive::text_iarchive inArch (ifs);

    inArch & numsTwo;

    for (int i=0; i<numsTwo.len(); i++){
        cout << numsTwo[i] << endl;
    }


    return 0;
}   

int main_context_users_out() {

    NicksObjVector<Patient*> dbPatients;

    Patient* patA = new Patient();
    dbPatients.push(patA);

    patA->setName("Patty Andreas");
    Record::databasePath = "/Volumes/GD";
    TextRecord* aNewRecord = new TextRecord();

    aNewRecord->setTitle("A test of 1");
    aNewRecord->setAuthor(9000);
    
    patA->newRecord(aNewRecord);

    cout << dbPatients[0]->getName()<<" "<< ((Patient*)dbPatients[0])->getRecords()->len()<<" "<< (*(((Patient*)dbPatients[0])->getRecords()))[0]->getTitle() << endl;

    fs::current_path("/Volumes/GD/testdir");
    std::ofstream ofs( "numArchive.dat");
    boost::archive::text_oarchive outArch (ofs);
    
    // Save the data
    outArch & dbPatients;

    ofs.close();

    return 0;
}

int main_context_users_in() {

    NicksObjVector<Patient*> dbPatients;

    // load in
    fs::current_path("/Volumes/GD/testdir");

    cout << "loading fstream" << endl;
    std::ifstream ifs("patientArchive.dat");

    cout << "parsing archive" << endl;
    boost::archive::text_iarchive inArch (ifs);

    cout << "deserialising" << endl;
    inArch & dbPatients;

    cout << dbPatients[0]->getName()<<" "<< ((Patient*)dbPatients[0])->getRecords()->len()<<" "<< (*(((Patient*)dbPatients[0])->getRecords()))[0]->getTitle() << endl;

    return 0;
}

int main() {
    
    cout << "1 - in\n2 - out" << endl;
    int opt;
    cin >> opt;
    if (opt == 1){
        main_context_users_in();
    } else if (opt == 2) {
        main_context_users_out();
    }

    return 0;
}