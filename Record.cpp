#include "global.h"
#include "TextEditor.h"
#include "Record.h"
#include "Patient.h"

#include <iostream>
#include <vector>
#include <limits>

unsigned int database::recordCount = 1;

Record::Record() {
    id = database::recordCount;
    database::recordCount = database::recordCount + 1;
    recordType = 1; // text record

    if (database::path == "null"){
        throw "database path error";
    }

    pathToFile = "null";
}

Record::Record(unsigned int patientOwner) : Record::Record() {
    this->patientOwner = patientOwner;

    pathToFile = database::path + "/patients/" + std::to_string(patientOwner) +"/"+ std::to_string(this->getId())+".txt";
}

Record::Record(unsigned int patientOwner, unsigned int authorDoctor) : Record::Record() {
    this->patientOwner = patientOwner;
    this->authorDoctor = authorDoctor;

    pathToFile = database::path + "/patients/" + std::to_string(patientOwner) +"/"+ std::to_string(this->getId())+".txt";
}

int Record::open() {
    if (pathToFile == "null") {
        return -1;
    }
    TextEditor *editor = new TextEditor(); // creates a new instance of a text editor
    int returnCode = editor->open(pathToFile); // passes return code of whichever editor was used

    delete editor; // deletes instance of text editor
    return returnCode;
}

void Record::printDetails() {
    using namespace std;
    while (true) { 
        system("clear");
        cout <<"Title: "<< this->getTitle() <<"\nMade by: "<< User::findByID(this->getAuthor())->getName() <<" (ID: " << this->getAuthor() << ")" <<"\n";
        cout << "Date made: " << this->getDate() << "\nRecord ID: " << this->getId() <<"\n"<<endl;
        cout << "Enter 'o' to view record or anything else to close\n ––> ";
        char optView; 
        //cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> optView;
        if (optView == 'o' || optView == 'O'){
            // open record
            this->open();
        } else {
            break;
        }
        system("clear");
    }
}

unsigned int Record::getId() {
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