#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
namespace fs = boost::filesystem;

class form_mesto
{
public:
    string mesto;
    int year;
    int mounth;
    int day;
    bool visit = false;
    form_mesto(string a_mesto)
    {
        mesto = a_mesto;
    }
    form_mesto(){}
private:
    friend class boost::serialization::access;
    template<class Archieve>
    void serialize(Archieve & ar, const unsigned int version)
    {
        ar & mesto;
        ar & year;
        ar & mounth;
        ar & day;
        ar & visit;
    }
};

class Place
{
private:
    friend class boost::serialization::access;
    template<class Archieve>
    void serialize(Archieve&ar, const unsigned int version)
    {
        ar& mestа;
        ar& person;
    }
public:
    string person;
    vector<form_mesto> mestа;

    Place(string a_person)
    {
        person = a_person;
    }

    void add_place(form_mesto a_mesto)
    {
        mestа.push_back(a_mesto);
    }
};

int mainA()
{
    string input_in_form = "London";
    string input_in_Place = "Eugene";
    form_mesto z = form_mesto(input_in_form);
    Place x = Place(input_in_Place);
    x.add_place(z);

    fs::create_directories("/Volumes/GD/testdir");
    fs::path pth ("/Volumes/GD/testdir");
    fs::current_path(pth);

    std::ofstream ofs("save.dat", std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa & x;

    return 0;
};

int main() {
    fs::current_path("/Volumes/GD/testdir");
    Place x = Place("default");
    std::ifstream ifs("save.dat", std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);
    ia & x;

    

    return 0;
};