#include "global.h"
#include "TextRecord.h"
#include "TextEditor.h"
#include "Record.h"

#include <iostream>

TextRecord::TextRecord(){

    setType(1); // type 1 for all text records

    if (database::path == "null"){
        throw "database path error";
    }

    pathToFile = database::path + "/patients/" + std::to_string(this->getOwner()) +"/"+ std::to_string(this->getId())+".txt";

}

TextRecord::TextRecord(unsigned int patientOwner, unsigned int authorDoctor) : Record(patientOwner,authorDoctor){
    setType(1); // type 1 for all text records
    
    if (database::path == "null"){
        throw "database path error";
    }

    pathToFile = database::path + "/patients/" + std::to_string(this->getOwner()) +"/"+ std::to_string(this->getId())+".txt";
}

int TextRecord::open(){
    TextEditor *editor = new TextEditor();

    int returnCode = editor->open(pathToFile);

    delete editor;

    return returnCode;
}

TextRecord::~TextRecord(){

}