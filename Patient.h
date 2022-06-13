#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"
#include "NicksObjVector.hpp"
#include "Record.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <iostream>
#include <vector>

class Patient : public User {
private:
    // state
    std::string address;
    std::string dob;
    std::string phoneNum;
    std::string bloodType;
    std::string emergencyContact;

    NicksObjVector<Record*> records; // vector of records
    NicksObjVector<unsigned int> authDoctors; // vector of ids of authenticated doctors


    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        using boost::serialization::make_nvp; using namespace std;
        // User state
        //cout << "uid" << endl;
        ar & make_nvp("userUid",uid);
        //cout << "name" << endl;
        ar & make_nvp("userFullName",name);
        //cout << "role" << endl;
        ar & make_nvp("userRole",userRole);
        //cout << "pass" << endl;
        ar & make_nvp("userPassword",password);
        //cout << "count" << endl;

        //ar & make_nvp("userIdCount", userIdCounter);

        // Patient state
        //cout << "address" << endl;
        ar & make_nvp("userAddress",address);
        //cout << "dob" << endl;
        ar & make_nvp("userDob",dob);
        //cout << "phone" << endl;
        ar & make_nvp("userPhoneNum",phoneNum);
        //cout << "blooc" << endl;
        ar & make_nvp("userBloodType",bloodType);
        //cout << "PatientEmergency" << endl;
        ar & make_nvp("emergencyContact",emergencyContact);
        //cout << "records" << endl;
        ar & make_nvp("patientRecords",records);
        //cout << "auths" << endl;
        ar & make_nvp("authDoctors",authDoctors);
    }


public:
    
    // constructors
    Patient();

    // methods
    std::string getAddress();
    void setAddress(std::string);
    std::string getDOB();
    void setDOB(std::string);
    std::string getPhone();
    void setPhone(std::string);
    std::string getBlood();
    void setBlood(std::string);
    std::string getEmergency();
    void setEmergency(std::string);
    int newRecord();
    NicksObjVector<unsigned int> * getAuthDoctors();
    bool testDocAuth(unsigned int docID);
    void consent(unsigned int docID);
    void revokeConsent(unsigned int docID);
    NicksObjVector<Record*> * getRecords(unsigned int patientID);
    NicksObjVector<Record*> * getMyRecords();
    void printDetails();

    // public static methods
    static Patient* accessPatient(unsigned int docID, unsigned int patientID);


    // destructors
    ~Patient();

};

#endif