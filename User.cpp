#include <iostream>
#include <limits>

#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Logger.hpp" // assumes a logger is accessible at index 0

using std::cout; using std::cin; using std::endl; using std::string;

unsigned int User::userIdCounter = 0;
NicksObjVector<User*> User::allUsers;

template<typename T>
extern void cinForceType(T*input);

// class static methods
User* User::findByID(unsigned int id) {
    for (int i=0; i<allUsers.size(); i++) {
        if (allUsers[i]->getUid() == id) {
            return allUsers[i];
        }
    }
    return nullptr;
}


// object methods, construc and destruc
/**
 * base initialisation. 
 * should not be used as User type (enforced by abstraction)!
 */
User::User(){
    userIdCounter++;
    uid = userIdCounter;
    name = "null";
    password = "default";
    userRole = 0;
    sessionValidated = false;

    allUsers.push(this);
}

unsigned int User::getUid(){
    return uid;
}

std::string User::getName(){
    return name;
}

void User::setName(std::string name_in){
    name = name_in;
}

void User::setUid(unsigned int newId){
    uid = newId;
}

unsigned int User::getRole(){
    return userRole;
}

void User::setRole(unsigned int userRole){
    this->userRole = userRole;
}

/**
 * check if paramater matches user password
 */
bool User::validatePassword(std::string inStr){
    if (inStr == password){
        return true;
    } else {
        return false;
    }
}

bool User::checkSessionValidation(){
    return sessionValidated;
}

/**
 * if password param can be validated, then validate this session
 * this 'unlocks' other methods of this user
 */
bool User::login(std::string password){
    if ( validatePassword(password) ){
        sessionValidated = true;
        return true;
    }
    return false;
}

/**
 * remove session validation to prevent unneccesary change
 */
void User::logout(){
    sessionValidated = false;
}

/**
 * change password if session validated
 */
bool User::changePassword(std::string newPass) {
    if (sessionValidated) {
        password = newPass;
        return true;
    }
    return false;
}

/**
 * interactively change passwords with options to exit
 */
void User::changePasswordInteractive(std::string oldPass) {

    if (this->validatePassword(oldPass) == false) {
        cout << "\nEnter your current password to confirm password change\n -–> ";
        // string oldPass;
        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(cin,oldPass);

        while ( this->validatePassword(oldPass) == false ) {
            cout << "Password incorrect. Try again, or press escape key then enter to exit:\n -–> ";
            oldPass = "";
            char ch[129];
            cin.getline(ch,128);
            bool breakLoop = false;
            for (int i=0;i<128;i++){
                if (ch[i] == 27){ // if escape key was entered
                    breakLoop = true;
                    break;
                } 
                else if (ch[i] == '\0'){ break; } 
                else { oldPass += ch[i]; }
            }
            if (breakLoop) { break; }
        }
    }

    if (this->validatePassword(oldPass)) { // if the password was validated, allow change

        while(true){

            system("clear");

            bool validNewPass = false;
            bool breakLoop = false;
            string newPass;
            while (validNewPass == false) {
                cout << "Enter your new password (or submit escape to cancel)\n -–> ";
                char ch[129];
                cin.getline(ch,128);
                for (int i=0;i<128;i++){
                    if (ch[i] == 27){ // if escape key was entered
                        breakLoop = true;
                        break;
                    } else if (ch[i] == '\0') {
                        break;
                    } else if (ch[i] == 32 ) {
                        cout << "Password cannot contain spaces. ";
                        validNewPass = false;
                        break;
                    } else {
                        newPass += ch[i];
                        validNewPass = true;
                    }
                }

                if (breakLoop) { break; }

            }
            if (breakLoop) { break; }
            
            bool success = false;
            
            system("clear");
            cout << "Confirm new password (or submit escape to cancel)\n -–> ";
            while(true) {
                string confirmPass;
                char ch[129];
                cin.getline(ch,128);
                bool breakLoop = false;
                for (int i=0;i<128;i++){
                    if (ch[i] == 27){ // if escape key was entered
                        breakLoop = true;
                        break;
                    } 
                    else if (ch[i] == '\0'){ break; } 
                    else { confirmPass += ch[i]; }
                }
                if (breakLoop) { break; }

                if (confirmPass == newPass){
                    Logger::all[0]->log_info("Password change successful for user "+std::to_string(this->getUid()));
                    this->changePassword(newPass);
                    success = true;
                    break;
                }

                cout << "Passwords don't match. Try again\n -–> ";
            }

            if (success) { break; }
            
        }

    }    
}

/**
 * operator== tests the User uid
 */
bool User::operator==(const User& rhs){
    if (this->uid == rhs.uid){
        return true;
    } else {
        return false;
    }
}

User::~User(){

}