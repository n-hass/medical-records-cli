#include "Doctor.h"
#include "Patient.h"
#include <stdexcept>
#include <iostream>


/**
 * default constructor, initialises
 */
Doctor::Doctor(){
    this->setRole(2);
    specialisation = "null";
    practise = "null";
}

/**
 * specialisation set by user
 */
std::string Doctor::getSpecialisation(){
    return specialisation;
}

/**
 * change the specialisation by string input
 */
void Doctor::setSpecialisation(std::string specialisation){
    this->specialisation = specialisation;
}

/**
 * practise set by user
 */
std::string Doctor::getPractise(){
    return practise;
}

/**
 * change the practise by string input
 */
void Doctor::setPractise(std::string practise){
    this->practise = practise;
}


/**
 * access a patient by validating with this doctor's id.
 * Must be in a try/catch in main function.
 */
Patient* Doctor::accessPatient(unsigned int targetID){
    Patient* patient = nullptr;
    patient = Patient::accessPatient(this->uid, targetID);
    
    if (patient != nullptr){
        return patient;
    } else {
        throw "Access denied. Patient has not consented to this doctor's access";
    }
}

/**
 * Implementation of get records. 
 * accesses patient and if successful, 
 * returns a pointer to their records.
 */
NicksObjVector<Record*> * Doctor::getRecords(unsigned int patientID) {
    Patient* target;
    try {
        target = accessPatient(patientID);
    } catch (const char* msg) {
        throw msg;
    }

    return target->getMyRecords();
}

/**
 * Implementation of print details.
 * far simpler than patient.
 */
void Doctor::printDetails() {
    std::cout << "Name: "<<this->getName()<<"\nPractise: "<<this->getPractise()<<"\nSpecialisation: "<<this->getSpecialisation()<<std::endl;
}

Doctor::~Doctor(){
    
}