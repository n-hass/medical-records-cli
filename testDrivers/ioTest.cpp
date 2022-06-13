#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "NicksObjVector.hpp"

using std::cout; using std::cin; using std::endl; using std::string; using std::vector; using std::getline;

void streamReset() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * forces an input which can parsed to the typename provided
 * Rejects bad input, prompts for another line
 */
template<typename T>
void cinForceType(T*input) {
    streamReset();
    cin >> *input;

    while (cin.fail()){
        cout << "Input invalid. Try again: \n -–> ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> *input;
    } 
}

/**
 * Allows input but detects if escape key was pressed 
 * if it was, sets the input to the provided default value
 *  
 */
void cinWithExit(int* input, int defaultVal) {

    string str;
    char ch[129] = "";
    cin >> ch;

    for (int i=0; i<128; i++){
        if (ch[i] == 27) { // 27 is the ASCII code of escape key, this detects if escape was pressed
            *input = defaultVal;
            return;
        } else if (ch[i] == '\0'){ break; } // break at end of line
        else if ( (ch[i] >= 48 && ch[i] <= 57) || (ch[i] == 43 || ch[i] == 45) ) {  // check if number was an ascii 0-9, a + or -.
            str += ch[i]; 
        } 
        else { break; };
    }

    try { 
        *input = std::stoi(str);
    } catch (std::invalid_argument e) {
        *input = defaultVal;
    }
    return;
}
/**
 * overload for unsigned int
 */
void cinWithExit(unsigned int* input, unsigned int defaultVal) {

    string str;
    char ch[129] = "";
    cin >> ch;

    for (int i=0; i<128; i++){
        if (ch[i] == 27) { // 27 is the ASCII code of escape key, this detects if escape was pressed
            *input = defaultVal;
            return;
        } else if (ch[i] == '\0'){ break; } // break at end of line
        else if ( (ch[i] >= 48 && ch[i] <= 57) || (ch[i] == 43 || ch[i] == 45) ) {  // check if number was an ascii 0-9, a + or -.
            str += ch[i]; 
        } 
        else { break; };
    }

    try { 
        if (std::stoi(str) < 0) { throw "not unsigned"; }
        *input = abs ( std::stoi(str) );
    } catch (...) {
        *input = defaultVal;
    }
    return;
}

/**
 * Allows input but detects if escape key was pressed 
 * if it was, sets the input to the provided default value
 *  
 */
void cinWithExit(string* input, string defaultVal) {
    string str;
    char ch[257];
    cin >> ch;

    for (int i=0; i<128; i++){
        if (ch[i] == 27) { // 27 is the ASCII code of escape key, this detects if escape was pressed
            *input = defaultVal;
            return;
        } else if (ch[i] == '\0'){ break; } // break at end of line
        else { str += ch[i]; } // add the character to the string if valid
    }

    *input = str;
    return;
}

/**
 * Gets user input, only accepts if it was part of the validator list parameter
 */
template <typename T> 
T getValidInput(std::initializer_list<T> valsIn){ // input checking function passinng in an initialiser list of values
    std::vector<T> vals (valsIn);
    int n = vals.size();

    T input;
    cin >> input;

    if (cin.fail()) {
        cout << "Input invalid. Try again: \n -–> ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = getValidInput<T>(valsIn);
    }

    bool invalid = true;
    for (int i=0; i<n; i++){
        if (input == vals[i]){
            invalid = false;
        }
    }
    if (invalid){
        cout << "Input invalid. Try again: \n -–> ";
        input = getValidInput<T>(valsIn);
    }

    return input;
}

/**
 * Gets user input, only accepts if it was part of the vector parameter
 */
template <typename T>
T getValidInput(std::vector<T> vals){ // input checker function passing in vector of valid values
    int n = vals.size();

    T input;
    cin >> input;

    if (cin.fail()) {
        cout << "Input invalid. Try again: \n -–> ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = getValidInput<T>(vals);
    }

    bool invalid = true;
    for (int i=0; i<n; i++){
        if (input == vals[i]){
            invalid = false;
        }
    }
    if (invalid){
        cout << "Input invalid. Try again: \n -–> ";
        input = getValidInput<T>(vals);
    }

    return input;
}

/**
 * Gets user input, only accepts if it was part of the vector parameter
 */
template <typename T>
T getValidInput(NicksObjVector<T> vals){ // input checker function passing in vector of valid values
    int n = vals.len();

    T input;
    cin >> input;

    if (cin.fail()) {
        cout << "Input invalid. Try again: \n -–> ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = getValidInput<T>(vals);
    }

    bool invalid = true;
    for (int i=0; i<n; i++){
        if (input == vals[i]){
            invalid = false;
        }
    }
    if (invalid){
        cout << "Input invalid. Try again: \n -–> ";
        input = getValidInput<T>(vals);
    }

    return input;
}

/**
 * Gets user input as a bool. 
 * accepts y, n (and capitalised), 1, 0, true and false
 */
bool getBoolInput(){
    string input;
    cin >> input;

    if (input == "y") { return true; }
    if (input == "n") { return false; }
    if (input == "yes") { return true; }
    if (input == "no") { return false; }
    if (input == "1") { return true; }
    if (input == "0") { return false; }
    if (input == "Y") { return true; }
    if (input == "N") { return false; }
    if (input == "Yes") { return true; }
    if (input == "No") { return false; }
    if (input == "true") { return true; }
    if (input == "false") { return false; }
    if (input == "True") { return true; }
    if (input == "false") { return false; }        

    streamReset();

    cout << "Input invalid. Enter y, n, 1 or 0\n -–> " << endl;

    bool out = getBoolInput();

    return out;
}


int main() {

    cout << "Run the IO test?" << endl;

    if (getBoolInput()) {
        cout << "Choose betweeen 1 and 5" << endl;
        int a;
        a = getValidInput<int>({1,2,3,4,5});

        cout << "A: " << a << endl;


        string in;

        cout << "enter a letter between a and d" << endl;
        std::vector<string> b {"a","b","c","d"};
        in = getValidInput<string>(b);
        cout << in << endl;
        
        cout << "enter an int or exit" << endl;
        cinWithExit(&a, 0);
        cout << a << endl;


        unsigned int c;
        cout << "enter an unsigned int or exit" << endl;
        cinWithExit(&c, 0);
        cout << c << endl;

        
        cout << "enter a string or exit" << endl;
        cinWithExit(&in, "default");
        cout << in << endl;
    }   

    return 0;
}