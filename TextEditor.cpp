#include "TextEditor.h"
#include <iostream>
#include <cstring>

extern std::string exec(const char* cmd, bool silent);


std::string TextEditor::editorPath = "null"; // default val

TextEditor::TextEditor(){

    if (editorPath == "null"){
        int emacsTest = std::system("which emacs >null");
        int nanoTest = std::system("which nano >null");

        if (emacsTest == 0){
            editorPath = exec("which emacs",true);
            editorPath.erase( (editorPath.length()-1)); // remove null terminating from str


        } else if (nanoTest == 0){
            editorPath = exec("which nano",true);
            editorPath.erase( (editorPath.length()-1)); // remove null terminating from str

        } else {
            throw "no viable text editor installed. Install either emacs or nano.";
        }
    }

}

int TextEditor::open(std::string pathToTextFile){

    std::string cmdStr = editorPath + " " + pathToTextFile;

    char* cmdChar;
    cmdChar = &cmdStr[0];
    
    int res = system(cmdChar);

    return res;
}

TextEditor::~TextEditor(){
    
}