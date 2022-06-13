#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Record.h"
#include "NicksObjVector.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

class User { 
public:
    // constructors
    User();
    // destructors
    virtual ~User();

    // public methods
    unsigned int getUid();
    std::string getName();
    void setName(std::string);
    unsigned int getRole();
    void setRole(unsigned int); // 1 for patient, 2 for doctor
    bool validatePassword(std::string); // returns true or false if the parameter matches the user's password
    bool checkSessionValidation();
    void setUid(unsigned int);

    virtual void printDetails() = 0; // prints details about the user
    virtual NicksObjVector<Record*> * getRecords(unsigned int patientID) = 0; // returns a pointer to an array of records. either for this-> or another 

    bool login(std::string password);
    void logout();

    bool changePassword(std::string newPass); // if logged in, change password to provided str
    void changePasswordInteractive(std::string oldPass); // optionally skip the initial interactive password confirmation by calling function with the correct password

    // operators
    bool operator==(const User& rhs);

    // public static functions
    static User* findByID(unsigned int id);

    // public static variables
    static NicksObjVector<User*> allUsers;
    static unsigned int userIdCounter;

    // public state
    unsigned int uid;
    std::string name;
    unsigned int userRole;
    std::string password;


private:
    // private class variables

    // private state
    bool sessionValidated;

    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize (Archive & ar, const unsigned int version) {
        using boost::serialization::make_nvp;
        // User state
        ar & make_nvp("UserUid",uid);
        ar & make_nvp("userFullName",name);
        ar & make_nvp("userRole",userRole);
        ar & make_nvp("userPassword",password);
        //ar & make_nvp("userIdCounter",userIdCounter);
        // ar & make_nvp("sessionValidated",sessionValidated);
    }
};

#endif