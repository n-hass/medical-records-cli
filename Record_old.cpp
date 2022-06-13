#include "Record.h"
#include "Patient.h"

// std::string Record::databasePath = "null";

Record::Record(){
    id = Patient::recordCount;
    Patient::recordCount++;
    recordType = 0;
}

Record::Record(unsigned int patientOwner){
    this->patientOwner = patientOwner;
}

Record::Record(unsigned int patientOwner, unsigned int authorDoctor){
    this->patientOwner = patientOwner;
    this->authorDoctor = authorDoctor;
}

Record::Record(std::string title, std::string dateMade, unsigned int authorDoctor, unsigned int patientOwner, unsigned int recordType){
    id = Patient::recordCount;
    Patient::recordCount++;

    this->recordType = recordType;
    this->authorDoctor = authorDoctor;
    this->patientOwner = patientOwner;
    this->dateMade = dateMade;
    this->title = title;
}

unsigned int Record::getId(){
    return id;
}

unsigned int Record::getAuthor(){
    return authorDoctor;
}
void Record::setAuthor(unsigned int authorDoctor){
    this->authorDoctor = authorDoctor;
}

std::string Record::getDate(){
    return dateMade;
}

void Record::setDate(std::string dateMade){
    this->dateMade = dateMade;
}

std::string Record::getTitle(){
    return title;
}

void Record::setTitle(std::string title){
    this->title = title;
}

unsigned int Record::getOwner(){
    return patientOwner;
}

void Record::setOwner(unsigned int patientOwner){
    this->patientOwner = patientOwner;
}

unsigned int Record::getType(){
    return recordType;
}

void Record::setType(unsigned int recordType){
    this->recordType = recordType;
}

Record::~Record(){

}