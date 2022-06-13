#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>

class TextEditor {

    private:
    // state
    static std::string editorPath;

    public:
    // constructor
    TextEditor();

    // methods
    int open(std::string pathToTextFile);


    // destructor
    ~TextEditor();

};

#endif