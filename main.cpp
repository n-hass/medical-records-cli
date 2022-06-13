// my classes
#include "global.h"
#include "Logger.hpp"
#include "NicksObjVector.hpp"
#include "Patient.h"
#include "Doctor.h"
#include "Record.h"
#include "TextEditor.h"

// std library
#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <type_traits>

// Boost library for archive and serialisation
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_archive_exception.hpp>
#include <boost/serialization/vector.hpp>

using std::cout; using std::cin; using std::endl; using std::string; using std::vector; using std::getline;
namespace fs = std::filesystem;
/* all users and records are created inside a vector or array which is saved and written to file.
*/


/* to load in data from a file, it'll load a text file which will say 
how many patients there were. Then create those x amount of patients.
then how many records for each of those patients. 
then loop through each of those records to fill in their info. 
Then loop through and create num of doctors with their saved state. */

extern string getCwd(); // print

/**
 * cin.ignore and cin.clear for resetting stream.
 */
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

/**
 * userLogin contains CLI which asks the user for an id number to retrieve an object with that id.
 * It prompts for password to that object and if the password can be validated, it returns a pointer to the object.
 * The returned pointer can be assigned to a pointer in the main and then used to access the object for other methods.
 * Should be typecasted for access to doctor or patient methods
 */
User* userLogin() {
    cout << "\nEnter user ID (or escape to cancel): \n ––> ";
    unsigned int targetID;

    cinWithExit(&targetID,0);

    if (targetID == 0) {
        throw "login attempt terminated by user";
    }


    NicksObjVector<unsigned int> userIds; // 
    for (int i=0; i<User::allUsers.size(); i++){
        userIds.push(User::allUsers[i]->getUid());
    }

    while (userIds.indexOf(targetID) == -1){
        cout << "User id not found. Try again, or enter escape to cancel: \n -–> ";
        cinWithExit(&targetID,0);

        if (targetID == 0) {
            throw "login attempt terminated by user";
        }
    }
    int userLoc = userIds.indexOf(targetID);
    
    User* session = User::allUsers[userLoc];

    cout << "Password: ";
    std::string testPass;
    streamReset(); getline(cin,testPass);

    while ( session->validatePassword(testPass) == false ){
        cout << "Password incorrect. Try again, or press escape key then enter to exit:\n -–> ";
        testPass = "";
        char ch[129];
        cin >> ch;

        for (int i=0;i<128;i++){
            if (ch[i] == 27){ // if escape key was pressed
                throw "login attempt terminated by user";
            } else if (ch[i] == '\0'){
                break;
            } else {
                testPass += ch[i];
            }
        }

    }

    if ( session->login(testPass) == false) { // record the logged in status in the object state. must call logout() when finished.
        throw "logic error"; 
    }

    system("clear");

    return session;
}


/**
 * Main
 */
int main(int argc, char* argv[]){
    Logger* log = new Logger; // create the logger object
    log->globalise(); // so can be accessed anywhere in runtime

    system("clear");

    string argDBpath(argv[0]);

    int pathSeperator = argDBpath.find_last_of(fs::path::preferred_separator); // remove the program name from the argv[0] string
    argDBpath.erase(pathSeperator);  


    if (argDBpath != fs::current_path().string()){
        cout << "The location of the database folder cannot be automatically determined.\n";
        cout << "\nPlease review the below directories to set the location of the database directory.\n";
        cout << "1 - " << argDBpath << "\n2 - " << fs::current_path().string() << "\n3 - Enter a new path to the database folder\n ––> ";
        int pathOpt = getValidInput<int>({1,2,3});


        if (pathOpt == 1){
            database::path = argDBpath+"/database";
        } else if (pathOpt == 2){
            database::path = fs::current_path().string()+"/database";
        } else {

            cout << "\nEnter path to database folder (excluding the folder; /Users/.../folderContainingDatabase):\n ––> ";
            string dataPathInput;
            streamReset(); getline(cin,dataPathInput);

            while (true){
                cout << "Is path: '" << dataPathInput << "' correct? (y or n)\n ––> ";
                if (getBoolInput() == false){
                    cout << "\nEnter path to database folder (excluding the folder; /Users/.../folderContainingDatabase):\n ––> ";
                    streamReset(); getline(cin,dataPathInput);
                } else {
                    break;
                }
            }

            database::path = dataPathInput+"/database";

        }
    }

    log->start(database::path, "recordSystem.log");

    NicksObjVector<Patient*> dbPatients; // create the vector to store the patient pointers
    NicksObjVector<Doctor*> dbDoctors; // create the vector to store the doctor pointers

    // deserialise

    try { // try to deserialise patient
        fs::current_path(database::path);
        if (fs::exists(database::path + "/patientArch.dat")) {
            
            log->log_info("Deserialising patients");
            std::ifstream ifs ("patientArch.dat");
            boost::archive::xml_iarchive inPatientArch (ifs,boost::archive::no_header); // will fail here if the file does not exist or is corrupt
            inPatientArch & boost::serialization::make_nvp("dbPatients",dbPatients);
            ifs.close();

        } else {
            log->log_info("Patient archive not found");
        }
    } catch (const boost::archive::archive_exception e) {
        string errMsg = e.what();
        log->log_error("Patient database error: "+ errMsg) ;
    }

    try { // try to deserialise doctor
        fs::current_path(database::path);
        if (fs::exists(database::path + "/docArch.dat")) {

            log->log_info("Deserialising doctors");
            std::ifstream ifs ("docArch.dat");
            boost::archive::xml_iarchive inDocArch (ifs,boost::archive::no_header); // will fail here if the file does not exist or is corrupt
            inDocArch & boost::serialization::make_nvp("dbDoctors",dbDoctors);
            ifs.close();

        } else {
            log->log_info("Doctor archive not found");
        }
    } catch (const boost::archive::archive_exception e) {
        string errMsg = e.what();
        log->log_error("Doctor database error: "+ errMsg);
    }

    
    while (true) {
        system("clear");
        cout << "Welcome." << endl << "\nOptions:\n1 – Login\n2 - Create an account\n3 - Recover user ID number\n4 - Close and quit\n -–> ";
        
        int opt = getValidInput<int>({1,2,3,4});

        if (opt == 1) { // user login
            
            User* loggedInUser = nullptr;

            try {
                loggedInUser = userLogin();
            } catch (const char* msg) {
                cout << "Login cancelled" << endl;
            }

            if (loggedInUser != nullptr) { // if the logged in user is a nullptr, the login failed (no user was found with that ID)
                
                if (loggedInUser->getRole() == 1) { // user is a patient

                    Patient* session = (Patient*) loggedInUser;

                    cout << "Log in complete. Select an option:" << endl;
                    
                    while(true) { // main menu loop
                        cout << std::right << std::setw(50) << session->getName() << ", ID: " << session->getUid() << endl;
                        cout << std::left <<"1 - Update profile\n2 - View my records\n3 - Manage record access consent\n4 - Log out\n -–> ";
                        int input = getValidInput({1,2,3,4});

                        if (input == 1) { // update profile

                            while(true) {
                                system("clear");

                                session->printDetails();                            
                                cout << "\n1 - Change full name\n2 - Change password\n3 - Change phone number\n4 - Change emergency contact\n5 - Exit\n -–> ";
                                int profileOpt = getValidInput({1,2,3,4,5});

                                if (profileOpt == 1){
                                    cout << "\nEnter your new name\n -–> ";
                                    string newName;
                                    cin.ignore(); getline(cin,newName);

                                    session->setName(newName);
                                }

                                if (profileOpt == 2) { // change password

                                    session->changePasswordInteractive(""); // blank string input prompts user to enter old password

                                }

                                if (profileOpt == 3) { // update phone number
                                    cout << "Enter new phone number\n ––> ";
                                    string newNum; 
                                    cin.ignore(); getline(cin,newNum);
                                    session->setPhone(newNum);
                                }

                                if (profileOpt == 4) { // update emergency contact
                                    cout << "Enter new emergency contact details, including name and phone number\n ––> ";
                                    string newEmergency;
                                    cin.ignore(); getline(cin,newEmergency);

                                    session->setEmergency(newEmergency);
                                }

                                if (profileOpt == 5) { break; } // return to the patient menu

                            }

                        }

                        if (input == 2) { // open records
                            NicksObjVector<Record*> *sRcds = session->getMyRecords();

                            while(true) {
                                system("clear");

                                cout << session->getName() << "'s records.\nTotal: " << sRcds->size() << endl << endl;

                                vector<int> recOps;
                                recOps.push_back(-1);
                                for (int i=0; i<sRcds->size(); i++){
                                    cout << i+1 << " - " << (*sRcds)[i]->getTitle() << endl;
                                    recOps.push_back(i+1);
                                }

                                cout << "\nEnter a record number to view, or -1 to exit:\n ––> ";
                                int recOpt;
                                recOpt = getValidInput<int>(recOps);
                                recOpt--; // convert from what was displayed to an index
                                
                                if (recOpt != -2) { // user did not exit
                                    
                                    Record* sltdRec = (*sRcds)[recOpt]; // assign the selected record

                                    sltdRec->printDetails();

                                }

                                if (recOpt == -2) { break; }
                            }

                        }

                        if (input == 3) { // manage record consent

                            while(true) {
                                vector<unsigned int> auths;
                                
                                for (int i=0; i<session->getAuthDoctors()->size(); i++){
                                    auths.push_back(session->getAuthDoctors()->e(i));
                                } 
                                

                                system("clear");

                                cout << "Doctors with access:" << endl;
                                if (session->getAuthDoctors()->size() == 0){
                                    cout << "(none)" << endl;
                                } else {
                                    for (int i=0; i<auths.size(); i++) {
                                        cout << User::findByID( auths[i] )->getName() << " (ID: " << auths[i] << ")" << endl;
                                    }
                                }

                                cout << "\n1 - Add new doctor\n2 - Remove doctor\n3 - exit\n ––> ";
                                int consentOpt = getValidInput<int>({1,2,3});

                                if (consentOpt == 1) { // add a new doctor
                                    cout << "Enter the id number of the doctor: ";
                                    unsigned int idInput;
                                    cinForceType(&idInput);
                                    
                                    string a;
                                    User* theDoc = User::findByID(idInput);
                                    
                                    try {

                                        if (theDoc != nullptr) {
                                            session->consent(idInput);
                                            cout << "Success. " << theDoc->getName() << " (ID: "<<idInput<<") now has access.\n\n(Press enter to continue)";
                                            streamReset();
                                            getline(cin,a);
                                        } else {
                                            cout << "No user with ID " << idInput << "(Press enter to continue)" << endl;
                                            streamReset();
                                            getline(cin,a);
                                        }

                                    } catch (...) {
                                        if (theDoc != nullptr) {
                                            if (theDoc->getRole() == 1) {
                                                cout << "User ID: " << idInput << " is another patient. Patients may not view each other's records.\n\n(Press enter to continue)";
                                                streamReset();
                                                getline(cin,a);
                                            } else {
                                                cout << theDoc->getName() << " (ID: "<<idInput<< ") already has access.\n\n(Press enter to continue)";
                                                streamReset();
                                                getline(cin,a);
                                            }
                                        } else {
                                            log->log_info("Patient attempted consent to an invalid User type");
                                            cout << "No user with ID " << idInput << " found.\n\n(Press enter to continue)"; 
                                            streamReset();
                                            getline(cin,a);
                                        }
                                        
                                    }
                                    
                                }

                                if (consentOpt == 2) {
                                    cout << "\nEnter the ID of the doctor to revoke access for:\n ––> ";

                                    unsigned int idInput = getValidInput<unsigned int>(auths);

                                    cout << "Revoke record access for " << User::findByID(idInput)->getName() << "? (y or n)\n ––> ";

                                    if (getBoolInput()) {
                                        session->revokeConsent(idInput);
                                    }
                                }

                                if (consentOpt == 3) { break; }

                            }

                        }

                        if (input == 4){ // the exit option
                            session->logout();
                            break;
                        }

                        system("clear");
                    }
                
                } 
                else if (loggedInUser->getRole() == 2) { // user is a doctor

                    Doctor* session = (Doctor*) loggedInUser;
                    
                    cout << "Log in complete. Select an option:\n";

                    while(true) { // doctor access menu
                        cout << std::right << std::setw(50) << session->getName() << ", ID: " << session->getUid() << endl;
                        cout << std::left << "1 - Access patient records\n2 - Create new patient profile\n3 - Update my profile\n4 - Log out\n -–> ";
                        int menuOpt = getValidInput({1,2,3,4});

                        if (menuOpt == 1) {
                            system("clear");

                            cout << "Enter patient's ID:\n ––> ";
                            unsigned int targetId;
                            cinForceType(&targetId);

                            Patient* targetPatient = Patient::accessPatient(session->getUid(), targetId); // implicilty calls login on the patient

                            while (targetPatient == nullptr) {
                                cout << "Patient either does not exist or has not consented to you accessing their records.\n\nEnter another ID, or enter anything else to cancel:\n ––> ";
                                
                                cinWithExit(&targetId, 0);

                                if (targetId == 0) {
                                    break;
                                }

                                targetPatient = Patient::accessPatient(session->getUid(), targetId);
                            }

                            if (targetPatient != nullptr) {
                                NicksObjVector<Record*> *targetPatientRecords = targetPatient->getMyRecords();
                                
                                while (true) {

                                    system("clear");
                                    cout << "Patient name: " << targetPatient->getName() << ", ID: " << targetPatient->getUid() << "\nDOB: " << targetPatient->getDOB() << endl;
                                    cout << "––– ––– –––" << endl;
                                    cout << "\nTotal records: " << targetPatientRecords->size() << endl << endl;

                                    vector<int> recOps;
                                    recOps.push_back(-1);
                                    for (int i=0; i<targetPatientRecords->size(); i++){
                                        cout << i+1 << " - " << (*targetPatientRecords)[i]->getTitle() << endl;
                                        recOps.push_back(i+1);
                                    }
                                    cout << targetPatientRecords->size()+1 << " - * Create a record *" << endl;
                                    recOps.push_back(targetPatientRecords->size()+1);

                                    cout << "\nEnter a record number, or -1 to exit:\n ––> ";
                                    int recOpt = getValidInput<int>(recOps);
                                    recOpt--; // convert from what was displayed to an index
                                    // -2 = exit
                                    // -1 = undefined (result is exit, but input shouldnt validate)
                                    // >=0 is open existing record
                                    // len of records+1 = new record

                                    if (recOpt == targetPatientRecords->size()) { // make a new record
                                        int indexNew = targetPatient->newRecord();
                                        Record *newRecord = *targetPatientRecords->get(indexNew);

                                        newRecord->setAuthor(session->getUid());

                                        newRecord->setDate(Logger::timeNow());

                                        cout << "Title of new record:\n ––> ";
                                        string newTitle;
                                        streamReset(); getline(cin,newTitle);
                                        newRecord->setTitle(newTitle);
                                        
                                        newRecord->printDetails();
                                    } else if (recOpt >= 0 && recOpt < targetPatientRecords->size()) { // user chose display existing record
                                        Record* sltdRec = *targetPatientRecords->get(recOpt);

                                        sltdRec->printDetails();
                                    }

                                    if (recOpt == -2) { // logout and exit
                                        targetPatient->logout();
                                        break;
                                    }
                                }
                                

                            }

                        }

                        if (menuOpt == 2) {

                            Patient * newPat = new Patient();
                            dbPatients.push(newPat);
                            
                            newPat->login("default"); // validate the session so doctor can edit patient's profile for them

                            newPat->consent(session->getUid()); // gives this doctor access to the new patient

                            
                            system("clear");
                            cout << "Enter patient's full name:\n ––> ";
                            string str;
                            streamReset(); getline(cin,str);

                            newPat->setName(str);

                            cout << "Create a record for "<< str <<"? (y or n)\n ––> ";

                            if (getBoolInput()) {
                                int indexNew = newPat->newRecord();
                                Record *newRecord = *(newPat->getMyRecords())->get(indexNew);

                                newRecord->setAuthor(session->getUid());

                                newRecord->setDate(Logger::timeNow());

                                cout << "Title of new record:\n ––> ";
                                string newTitle;
                                streamReset(); getline(cin,newTitle); //streamReset();
                                newRecord->setTitle(newTitle);

                                newRecord->printDetails();
                            }

                            newPat->logout();

                            system("clear");
                            cout << "Inform patient their log-in ID is: " << newPat->getUid() << ", and their password is: \"default\"" << endl;
                            cout << "\n\n(Press enter to return to menu)";
                            streamReset();
                            getline(cin, str);
                        }

                        if (menuOpt == 3) { // update profile

                            while(true) {
                                system("clear");

                                session->printDetails();                            
                                cout << "1 - Change full name\n2 - Change password\n3 - Change practise\n4 - Change specialisation\n5 - Exit\n -–> ";
                                int profileOpt = getValidInput({1,2,3,4,5});

                                if (profileOpt == 1){
                                    cout << "\nEnter your new name\n -–> ";
                                    string newName;
                                    streamReset(); getline(cin, newName);

                                    session->setName(newName);
                                }

                                if (profileOpt == 2){
                                    
                                    session->changePasswordInteractive("");

                                }

                                if (profileOpt == 3) { // update practise
                                    cout << "Enter new practise\n ––> ";
                                    string newPrac;
                                    streamReset(); getline(cin,newPrac);
                                    session->setPractise(newPrac);
                                }

                                if (profileOpt == 4) { // update specialisation
                                    cout << "Enter new specialisation\n ––> ";
                                    string newSpecial;
                                    streamReset(); getline(cin,newSpecial);
                                    session->setSpecialisation(newSpecial);
                                }

                                if (profileOpt == 5) { break; } // return to the doctor menu

                            }
                            
                        }

                        if (menuOpt == 4) {
                            session->logout();
                            break;
                        }
                        
                        system("clear");
                    }
                    
                }

            } else {
                cout << "Login failed. Returning to home." << endl;
            }

        } 
        else if (opt == 2) { // create accounts
            cout << "\n1 - Patient\n2 - Doctor\n3 - cancel\n -–> ";
            int accOpt = getValidInput<int>({1,2,3});

            if (accOpt == 1) {
                Patient* newPat = new Patient();
                dbPatients.push(newPat);

                newPat->login("default"); // validate the session with the default password

                cout << "\nEnter your full name:\n ––> ";
                string str;
                streamReset(); getline (cin,str);
                newPat->setName(str);

                newPat->changePasswordInteractive("default");

                system("clear");

                cout << "Enter your home address:\n ––> ";
                getline (cin,str);
                newPat->setAddress(str);

                cout << "\nEnter your date of birth:\n ––> ";
                getline (cin,str);
                newPat->setDOB(str);

                cout << "\nEnter your phone number:\n ––> ";
                getline (cin,str);
                while (true) {
                    try {
                        std::stoi(str);
                        break;
                    } catch (...) {
                        cout << "Invalid input. Try again\n ––> ";
                        getline (cin,str);
                    }
                }

                newPat->setPhone(str);

                cout << "\nEnter the name and phone number of your emergency contact:\n ––> ";
                getline (cin,str);
                newPat->setEmergency(str);


                system("clear");
                cout << "Patient profile completed.\nPlease make note of your ID number for logging in: " << newPat->getUid();
                cout << "\n\n(Press enter to continue)";
                getline (cin,str);

                newPat->logout(); // logout
            }

            if (accOpt == 2) {
                Doctor* newDoc = new Doctor();
                dbDoctors.push(newDoc);

                newDoc->login("default"); // validate the session with the default password

                cout << "\nEnter your full name:\n ––> ";
                string str;
                streamReset();
                std::getline (cin,str);
                newDoc->setName(str);

                newDoc->changePasswordInteractive("default");

                system("clear");

                cout << "Enter your specialisation:\n ––> ";
                std::getline (cin,str);
                newDoc->setSpecialisation(str); 

                cout << "\nEnter the name of your practise:\n ––> ";
                std::getline (cin,str);
                newDoc->setPractise(str);

                system("clear");
                cout << "Doctor profile completed.\nPlease make note of your ID number for logging in: " << newDoc->getUid();
                cout << "\n\n(Press enter to continue)"; 
                std::getline (cin,str);

                newDoc->logout();
            }

            if (accOpt == 3) {
                // do nothing. cli user chose exit
            }
            
        } 
        else if (opt == 3) {
            system("clear");
            cout << "Enter your name:\n ––> ";
            string search;
            streamReset(); getline(cin,search);

            int numResults = 0;

            cout << "Accounts matching the name \""<< search << "\"\n\n";
            for (int i=0; i<User::allUsers.size(); i++) {
                if ( User::allUsers[i]->getName().find(search) != string::npos ) {
                    numResults++;
                    cout << "ID: "<< User::allUsers[i]->getUid() <<", "<< User::allUsers[i]->getName() << endl; // print a search result
                }
            }

            cout << "\n\n(Press enter to return to menu)"; 
            getline (cin,search);

        } 
        else if (opt == 4) {
            break;
        } 

    }
    

    log->insertBreak();
    // set the path to database folder 
    fs::current_path(database::path);

    try {
        // load the patient archive file and serialise 
        log->log_info("serialising patients");

        std::ofstream ofs ("patientArch.dat"); // open file stream
        boost::archive::xml_oarchive outPatientArch (ofs,boost::archive::no_header); // set file as boost xml archive
        outPatientArch & boost::serialization::make_nvp("dbPatients",dbPatients); // write the serialised data to the file
        ofs.close(); // close the file stream

    } catch (const boost::archive::archive_exception e) {

        cout << "patient serialisation error" << endl;
        log->log_error(e.what());

    }

    try {
        // load the doctor archive file and serialise 
        log->log_info("serialising doctors");

        std::ofstream ofs ("docArch.dat"); // open file stream
        boost::archive::xml_oarchive outDocArch (ofs,boost::archive::no_header); // set file as boost xml archive
        outDocArch & boost::serialization::make_nvp("dbDoctors",dbDoctors); // write the serialised data to the file
        ofs.close(); // close the file stream

    } catch (const boost::archive::archive_exception e) {
        cout << "doctor serialisation error" << endl;
        log->log_error(e.what());
    }
    
    // memory management
    dbPatients.deleteAll(); // delete memory holding patients
    dbDoctors.deleteAll(); // delete memory holding doctors

    Logger::deleteAll(); // deletes all heap-allocated logger instances (only one for this program)
    

    cout << "Exiting the patient record system..." << endl;

    return 0;
}