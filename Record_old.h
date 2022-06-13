#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <boost/serialization/access.hpp>

class Record {
public:
    // state
    unsigned int id;
    unsigned int patientOwner;
    unsigned int authorDoctor;
    unsigned int recordType; // 0 for un-set, 1 for text, 2 for image
    std::string dateMade;
    std::string title; 

    
    // constructors and destructors
    Record(); // default const
    Record(unsigned int patientOwner); // patient owner only
    Record(unsigned int patientOwner, unsigned int authorDoctor); //patient and author
    Record(std::string title, std::string date, unsigned int authorDoctor, unsigned int patientOwner, unsigned int recordType);

    virtual ~Record(); // virtual for inheritance by TextRecord and ImgRecord

    // methods
    unsigned int getId();
    unsigned int getOwner();
    void setOwner(unsigned int);
    unsigned int getAuthor();
    void setAuthor(unsigned int);
    unsigned int getType();
    void setType(unsigned int);
    std::string getDate();
    void setDate(std::string);
    std::string getTitle();
    void setTitle(std::string);

    virtual int open() = 0;

private:
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
    }
    
};

#endif