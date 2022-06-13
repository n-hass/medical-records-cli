#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;


void cinWithExit(unsigned int* input, unsigned int defaultVal) {

    string str;
    char ch[129] = "";
    cin >> ch;

    for (int i=0; i<128; i++){
        if (ch[i] == 27) { // 27 is the ASCII code of escape key, this detects if escape was pressed
            *input = defaultVal;
            return;
        } else if (ch[i] == '\0'){ break; } // break at end of line
        else if ( ch[i] >= 48 && ch[i] <= 57 ) {  // check if number was an ascii 0-9, a + or -.
            str += ch[i]; 
        } 
        else { break; };
    }

    try { 
        *input = abs( std::stoi(str) );
    } catch (std::invalid_argument e) {
        *input = defaultVal;
    }
    return;
}

int main() {

    unsigned int a;

    cinWithExit(&a, 202050);
    
    cout << a << endl;


    return 0;
}