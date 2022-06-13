#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"
#include "Patient.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

class Doctor : public User {
private:
    // state
    std::string specialisation;
    std::string practise;


    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        using boost::serialization::make_nvp;
        // User state
        ar & make_nvp("uid",uid);
        ar & make_nvp("name",name);
        ar & make_nvp("userRole",userRole);
        ar & make_nvp("password",password);
        //ar & make_nvp("userIdCount", userIdCounter);

        // Doctor state
        ar & make_nvp("specialisation",specialisation);
        ar & make_nvp("practise",practise);
    }

public:
    // constructors and destructors
    Doctor(); // default

    ~Doctor(); // default

    // methods
    std::string getSpecialisation();
    void setSpecialisation(std::string);
    std::string getPractise();
    void setPractise(std::string);
    Patient* accessPatient(unsigned int patientID);
    void printDetails();

    NicksObjVector<Record*> * getRecords(unsigned int patientID);

    

};

#endif