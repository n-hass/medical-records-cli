#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

class Record {
public:
    // state
    unsigned int id;
    unsigned int patientOwner;
    unsigned int authorDoctor;
    unsigned int recordType; // 0 for un-set, 1 for text, 2 for image
    std::string dateMade;
    std::string title; 

    // static class vars
    static unsigned int count;
    
    // constructors and destructors
    Record(); // default const
    Record(unsigned int patientOwner); // patient owner only
    Record(unsigned int patientOwner, unsigned int authorDoctor); //patient and author

    ~Record(); 

    // methods
    unsigned int getId();
    unsigned int getOwner();
    void setOwner(unsigned int);
    unsigned int getAuthor();
    void setAuthor(unsigned int);
    unsigned int getType();
    void setType(unsigned int);
    std::string getDate();
    void setDate(std::string);
    std::string getTitle();
    void setTitle(std::string);

    
    void printDetails();
    int open();

    bool operator==(Record& b) {
        if (this->getId() == b.getId()){
            return true;
        }
        return false;
    }

private:
    std::string pathToFile;


    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        using boost::serialization::make_nvp;
        using namespace std;
        // Record state
        //cout << "id" << endl;
        ar & make_nvp("recordId", id);
        //cout << "owner" << endl;
        ar & make_nvp("patientOwner",patientOwner);
        //cout << "doctor" << endl;
        ar & make_nvp("authorDoctor",authorDoctor);
        //cout << "type" << endl;
        ar & make_nvp("recordType",recordType);
        //cout << "date" << endl;
        ar & make_nvp("dateMade",dateMade);
        //cout << "title" << endl;
        ar & make_nvp("recordTitle",title);
        //cout << "path" << endl;
        ar & make_nvp("pathToFile",pathToFile);
    }
    
};

#endif