#ifndef TEXT_RECORD_H
#define TEXT_RECORD_H

#include "Record.h"
#include <boost/serialization/access.hpp>

class TextRecord : public Record {
private:
    // state
    std::string pathToFile;

    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // Record state
        ar & id;
        ar & patientOwner;
        ar & authorDoctor;
        ar & recordType;
        ar & dateMade;
        ar & title;
        // TextRecord state
        ar & pathToFile;
    }
    
public:
    TextRecord(); // default constructor
    TextRecord(unsigned int patientOwner, unsigned int authorDoctor);

    // methods
    int open(); // open the text editor to this file

    // destructor
    ~TextRecord(); // default destructor

};

#endif