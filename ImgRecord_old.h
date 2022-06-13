#ifndef IMG_RECORD_H
#define IMG_RECORD_H

#include "Record.h"

class ImgRecord : public Record {
    private:
    // state
    std::string pathToFile;
    
    public:
    ImgRecord(); // default constructor

    // methods
    int open(); // open the text editor to this file

    // destructor
    ~ImgRecord(); // default destructor
};

#endif