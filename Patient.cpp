#include "global.h"
#include "Patient.h"
#include "Doctor.h"
#include "Logger.hpp" // assumes a global logger is accessable at index 0
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;


/**
 * default constructor, initialises
 */
Patient::Patient() {
    this->setRole(1);

    address = "null";
    dob = "null";
    phoneNum = "null";
    bloodType = "null";
    emergencyContact = "null";

    // create the patient directory to keep their records
    fs::path pPath ( database::path+"/patients/"+std::to_string(this->getUid()) );
    fs::create_directories(pPath);
}

std::string Patient::getAddress(){
    return address;
}

void Patient::setAddress(std::string address){
    this->address = address;
}

std::string Patient::getDOB() {
    return dob;
}

void Patient::setDOB(std::string dob){
    this->dob = dob;
}

std::string Patient::getPhone(){
    return phoneNum;
}

void Patient::setPhone(std::string phoneNum){
    this->phoneNum = phoneNum;
}

std::string Patient::getBlood(){
    return bloodType;
}

void Patient::setBlood(std::string bloodType){
    this->bloodType = bloodType;
}

std::string Patient::getEmergency(){
    return emergencyContact;
}

void Patient::setEmergency(std::string emergencyContact){
    this->emergencyContact = emergencyContact;
}

/**
 * returns the position of the new record to be used in main
 */
int Patient::newRecord() {
    Record * a = new Record (this->getUid());
    records.push(a);
    return records.indexOf(a);
}


/**
 * returns a pointer to this patient's records with checking of patient ID
 */
NicksObjVector<Record*>* Patient::getRecords(unsigned int patientID) {
    if (patientID != this->uid) {
        return nullptr;
    } else {
        return getMyRecords();
    }
}

/**
 * returns a pointer to this patient's records with only session validation check
 */
NicksObjVector<Record*>* Patient::getMyRecords() {
    if (checkSessionValidation() == false) {
        throw "patient session not validated";
    }
    return &records;
}

/**
 * returns a pointer to the authorised doctors vector
 */
NicksObjVector<unsigned int>* Patient::getAuthDoctors(){
    return &authDoctors;
}


/**
 * search authorised doctors to see if a doc is authorised
 */
bool Patient::testDocAuth(unsigned int docID) {
    if (authDoctors.indexOf(docID) == -1) {
        return false;
    }
    return true;
}

/**
 * adds an ID to the authorised doctors
 */
void Patient::consent(unsigned int docID) {

    if (checkSessionValidation() == false) {
        // not logged in
        return;
    }

    User* theDoc = User::findByID(docID);

    if (theDoc->getRole() == 1) {
        throw "ID provided is not a doctor";
    }

    if (authDoctors.indexOf(docID) == -1){
        authDoctors.push(docID);
        return;
    } else {
        throw "Doctor already has access";
    }
    
}


/**
 * removes an ID (if found) from the authorised doctors
 */
void Patient::revokeConsent(unsigned int docID) {
    if (checkSessionValidation() == false) {
        // not logged in
        return;
    }

    int index =  authDoctors.indexOf(docID);
    if (index == -1) {
        return;
    }

    authDoctors.pop(index);

}

/**
 * static. return a pointer to a patient if the docID provided is in it's auth vector
 */
Patient* Patient::accessPatient(unsigned int docID, unsigned int patientID) {
    Patient* target = nullptr;

    for (int i=0; i<allUsers.size();i++) {
        if (allUsers[i]->getRole() == 1) { // if is a patient

            if (allUsers[i]->getUid() == patientID) { // if this is the patient queried

                if ( ((Patient*) allUsers[i])->testDocAuth(docID) ) { // if the doctor is authorised

                    if (allUsers[i]->login(allUsers[i]->password) == false) { // validate the patient session
                        Logger::all[0]->log_fatal( "implicit login failed for ID "+std::to_string(allUsers[i]->getUid()) );
                    } 
                    target = (Patient*)allUsers[i]; // type cast the the user ptr to target as a patient
                    break;
                }

            }
            
        }
    }

    return target;
}

/**
 * implementation of printDetails. more extenseive than doctor
 */
void Patient::printDetails() {
    std::cout << "Name: "<<this->getName()<<"\nPhone number: "<<this->getPhone()<<"\nEmergency contact: "<<this->getEmergency()<<std::endl;
}

Patient::~Patient(){
    // records are deleted automatically by the NicksObjVector destructor
}