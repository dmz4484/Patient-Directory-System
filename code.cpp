//
//  main.cpp
//  Dania Zein
//  CSC 350
//  Programming Project
//  This project is a patient directory for a small clinic. It will include a list of patients and their attributes. The goal is to have an organized platform for the doctors and staff of the clinic to be able to access all of the information about their patients.

//  10/27/24 - Programming Phase 4: Initial Implementation

//  11/26/24 - Final Project


#include <iostream>
#include <vector>
#include <string>
using namespace std;

//patient struct definition
struct Patient{
    string name;            //the patient's name
    string ID;              //the patient's ID
    string sex;             //the patient's sex in M/F format
    string DOB;             //the patient's date of birth in YYYY-MM-DD format
    int age;                //the patient's age
    bool isAdult;           //if the patient is not a minor (under 18) Yes - true, No - false
    string diagnoses[5];    //the patient's diagnoses (up to 10)
};

//hard coded directory (current patients)
vector<Patient> patients = {
    {"Diane Woodruff", "03327", "F", "1967-02-22", 57, true, {"Stroke", "Diabetes"}},
    {"Adam Scott", "05521", "M", "1993-10-13", 31, true, {"Hypertension"}},
    {"Bill Walker", "11562", "M", "2007-09-12", 17, false, {"Influenza", "Fever", "Sore Throat"}},
    {"Jordan Terrance", "00221", "M", "2005-03-07", 19, true, {"COVID-19", "Pneumonia"}},
    {"Emily Terrance", "00222", "F", "2012-01-24", 12, false, {"COVID-19"}},
    {"Max Terrance", "00223", "M", "1978-05-30", 46, true, {"COVID-19"}}
};

void displayMenu();
void create();
void read();
void update();
void del();


int main()
{
    string response;
    while(response != "E")
    {
        cout<<endl;

        displayMenu();
        
        //input response
        cout<<"Enter a letter (C, R, U, D, or E) to access the directory: ";
        cout<<"\n";
        getline(cin, response);
        
        //input validation
        if(response == "R" || response == "r" || response == "read" || response == "Read")
        {
            cout<<endl;
            cout<<"Reading patient records:"<<endl;
            read();
            cout<<endl<<"\nThe patient records have been printed"<<endl;
        }
        else if(response == "C" || response == "c" || response == "create" || response == "Create")
        {
            cout<<endl;
            cout<<"Creating patient record:"<<endl;
            create();
            cout<<endl<<"\nThe patient has been added to the records. There are now "<<patients.size()<<" patients in the directory."<<endl;
        }
        else if(response == "U" || response == "u" || response == "update" || response == "Update")
        {
            cout<<endl;
            cout<<"Updating patient records:"<<endl;
            update();
        }
        else if(response == "D" || response == "d" || response == "delete" || response == "Delete")
        {
            cout<<endl;
            cout<<"Deleting patient records:"<<endl;
            del();
        }
        else if(response == "E" || response == "e" || response == "exit" || response == "Exit")
        {
            cout<<endl<<"You will now exit the patient directory"<<endl;
            break;
        }
        else //if response is not letter or not listed letter
        {
            cout<<"Invalid input. Please enter only a single letter option (C, R, U, D, or E)"<<endl;
        }
    }
    cout<<endl;
    return 0;
}


//FUNCTIONS
// Menu -- Print patient directory menu options
void displayMenu()
{
    //cout<<"\t\t\tPatient Directory Menu"<<endl;
    cout<<"---------------- Patient Directory Menu ----------------"<<endl;
    cout<<"1. Create a new patient in the directory ('C') "<<endl;
    cout<<"2. Read all the current patients in the directory ('R') "<<endl;
    cout<<"3. Update a patient's records in the directory ('U')"<<endl;
    cout<<"4. Delete a patient's records from the directory ('D')"<<endl;
    cout<<"5. Exit the Patient Directory \t('E')"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<endl;
}

// CREATE Menu Option 1 -- Adds a new Patient Record
void create()
{
    string newname, newID, newsex,newDOB, newdiagnoses[5], newagestr, newisAdultstr, input;
    int newage;
    bool newisAdult;
    char newisAdultchr, sex;
    
    //inputting new patient details
    cout<<"When prompted, enter the appropriate information of the patient to add to the directory."<<endl;
    cout<<"\nEnter the patient's name (FirstName LastName): ";
    getline(cin, newname);
    
    cout<<"\nEnter the patient's identification number (ID): ";
    getline(cin, newID);
    
    cout<<"\nEnter the patient's sex (M/F): ";
    getline(cin, newsex);
    sex = toupper(newsex[0]);
    switch(sex){
        case 'M':
            newsex = "M";
            break;
        case 'F':
            newsex = "F";
            break;
        default:
            cout<<"Invalid input. \nThe patient's sex will default to Male."<<endl;
            newsex = "M";
            break;
    }
    
    cout<<"\nEnter the patient's date of birth (YYYY-MM-DD): ";
    cin>>newDOB;
    //validating date of birth input
    string format = "-";
    size_t isfound = newDOB.find(format);
    if(isfound == string::npos){
        cout<<"Invalid input. \nThe patient's age will default to 1994-01-01"<<endl;
        newDOB = "1994-01-01";
    }
    
    cout<<"\nEnter the patient's age (Type an integer number): ";
    cin>>newagestr;
    //validating age input
    try{
        newage = stoi(newagestr);
    }
    catch(...){
        cout<<"Invalid input for age. The age will default to 30."<<endl;
        newage = 30;
    }
    
    cout<<"\nEnter the patient's diagnoses one by one. \nWhen complete, type 'C': ";
    cin.ignore();
    cout<<endl;
    for(int i = 0; i< 5; i++){
        cout<<"Enter diagnoses number "<<i+1<<" : ";
        getline(cin, input);
        if(input == "C" || input == "c"){
            //newdiagnoses[i] = "";
            break;
        }
        newdiagnoses[i] = input;
    }
    
    cout<<"\nEnter if the patient is an adult or not. If they are an adult, type 'Y' if not, type 'N': ";
    getline(cin, newisAdultstr);
    newisAdultchr = toupper(newisAdultstr[0]);
    switch(newisAdultchr){
        case 'Y':
            newisAdult = true;
            break;
        case 'N':
            newisAdult = false;
            break;
        default:
            cout<<"Invalid input. The patient will be set to not an adult by default."<<endl;
            newisAdult = false;
            break;
    }
    
    //adding the new patient to the directory
    Patient newpatient = {newname, newID, newsex, newDOB, newage, newisAdult, {}};
    for (int i = 0; i < 5; i++) {
        newpatient.diagnoses[i] = newdiagnoses[i];
    }
    patients.push_back(newpatient);
    
}


// READ Menu Option 2 -- Prints all Patient Records
void read()
{
    cout<<"Patient Records"<<endl;
    cout<<"------------------------------";
    for(int i = 0; i< patients.size(); i++){
        cout<<endl<<endl;
        
        cout<<"Patient "<<i+1<<" Records: "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"Name: "<<patients[i].name<<endl;
        cout<<"ID: "<<patients[i].ID<<endl;
        cout<<"Sex: "<<patients[i].sex<<endl;
        cout<<"Date of Birth: "<<patients[i].DOB<<endl;
        cout<<"Age: "<<patients[i].age<<endl;
        
        cout<<"Is Adult: ";
        if(patients[i].isAdult){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
        
        cout<<"Diagnoses: ";
        for(int j = 0; j < 5; j++ )
        {
            if(!(patients[i].diagnoses[j].empty()))
            {
                cout<<patients[i].diagnoses[j];
                for(int k = j+1; k<5; k++)
                {
                    if(!(patients[i].diagnoses[k].empty()))
                    {
                        cout<<", ";
                        break;
                    }
                }
            }
        }
    }
}

// UPDATE Menu Option 3 -- Updates a Patient Record
void update()
{
    cout<<"Which patient's records would you like to update?"<<endl;
    cout<<"Enter the patient's ID: ";
    string upID, confirm, choice;
    getline(cin, upID);
    bool found = false;
    bool iA = false;
    string name, sex, DOB, isAdult, diagnoses[5], tmpage, diaginput;
    char tmpiA;
    int age;
    
    //cin.ignore();
    
    //searching the database for the patient
    for(int x = 0; x< patients.size(); x++){
        if(upID == patients[x].ID){
            found = true;
            cout<<endl;
            cout<<"This ID matches patient "<<x+1<<". Are you sure you want to update this patient's records? Y/N? ";
            getline(cin, confirm);
            
            if(confirm == "y" || confirm == "Y"){
                cout<<"What would you like to update?\nThe patient's name (N), sex (S), DOB (D), age (A), if they are an adult (I), or their diagnoses (G)?  ";
                
                getline(cin,choice);
                
                //updating patient name
                if(choice == "N" || choice == "n"){
                    cout<<"What would you like to change patient "<<x+1<<"'s name to? \nPlease enter: (FirstName LastName)"<<endl;
                    getline(cin, name);
                    patients[x].name = name;
                    cout<<"Patient "<<x+1<<"'s name has been updated."<<endl;
                }
                //updating patient sex
                else if(choice == "s" || choice == "S"){
                    cout<<"What would you like to change patient "<<x+1<<"'s sex to? \nPlease enter: (M/F)"<<endl;
                    getline(cin, sex);
                    if(sex == "M" || sex == "m"){
                        patients[x].sex = "M";
                        cout<<"Patient "<<x+1<<"'s sex has been updated."<<endl;
                    }
                    else if(sex == "F" || sex == "f"){
                        patients[x].sex = "F";
                        cout<<"Patient "<<x+1<<"'s sex has been updated."<<endl;
                    }
                    else{
                        cout<<"Invalid input."<<endl;
                    }
                }
                //updating patient date of birth
                else if(choice == "D" || choice == "d"){
                    cout<<"What would you like to change patient "<<x+1<<"'s DOB to? \nPlease enter: (YYYY-MM-DD)"<<endl;
                    getline(cin, DOB);
                    //validating date of birth input
                    string format = "-";
                    size_t isfound = DOB.find(format);
                    if(isfound == string::npos){
                        cout<<"Invalid input."<<endl;
                        return;
                    }
                    else{
                        patients[x].DOB = DOB;
                        cout<<"Patient "<<x+1<<"'s DOB has been updated."<<endl;
                    }
                }
                //updating patient age
                else if(choice == "A" || choice == "a"){
                    cout<<"What would you like to change patient "<<x+1<<"'s age to? \nPlease enter: (Type an integer number)"<<endl;
                    getline(cin,tmpage);
                    try{
                        age = stoi(tmpage);
                        patients[x].age = age;
                        cout<<"Patient "<<x+1<<"'s age has been updated."<<endl;
                    }
                    catch(...){
                        cout<<"Invalid input."<<endl;
                    }
                }
                //updating patient adult status
                else if(choice == "I" || choice == "i"){
                    cout<<"What would you like to change patient "<<x+1<<"'s status to? \nIf they are an adult, type 'Y' if not, type 'N'"<<endl;
                    getline(cin, isAdult);
                    tmpiA = toupper(isAdult[0]);
                    switch(tmpiA){
                        case 'Y':
                            iA = true;
                            break;
                        case 'N':
                            iA = false;
                            break;
                        default:
                            cout<<"Invalid input."<<endl;
                            break;
                    }
                    patients[x].isAdult = iA;
                    cout<<"Patient "<<x+1<<"'s adult status has been updated."<<endl;
                }
                //updating patient diagnoses
                else if(choice == "g" || choice == "G"){
                    cout<<"What would you like to change patient "<<x+1<<"'s diagnoses to? \n Enter them one by one, when complete, type 'C': '"<<endl;
                    int count = 0;  // To track the number of diagnoses entered

                    while (count < 5) {
                        cout << "Enter diagnosis number " << count + 1 << ": ";
                        getline(cin, diaginput);

                        if (diaginput == "C" || diaginput == "c") {
                            break;  // Stop when 'C' is entered
                        }

                        diagnoses[count] = diaginput;  // Store the diagnosis
                        count++;  // Increment the count
                    }
                    
                    for (int i = 0; i < 5; i++) {
                        patients[x].diagnoses[i] = diagnoses[i];
                    }
                    cout<<"Patient "<<x+1<<"'s diagnoses has been updated."<<endl;
                }
                //input validaition
                else{
                    cout<<"Invalid input. Please only enter a single letter option (N, S, D, A, I , or G). "<<endl;
                    return;
                }
                cout<<endl<<"\nThe patient's records have been updated"<<endl;
                return;
            }
            else if(confirm == "n" || confirm =="N"){
                cout<<"The patient's records will not be updated."<<endl;
                break;
                //return;
            }
            else{
                cout<<"Invalid input. Please only enter a single letter option. Yes(Y) or No (N)."<<endl;
                return;
            }
        }
    }
    //input validation
    if(!found){
        cout<<"Unable to update patient. \nThis ID does not match a patient in the database."<<endl;
    }
    
}

// DELETE Menu Option 4 -- Deletes a Patient Record
void del()
{
    //read();
    string confirm;

    cout<<"Which patient would you like to delete?"<<endl;
    cout<<"Enter the patient's ID: ";
    string delID;
    getline(cin, delID);
    bool found = false;
    
    //searching the database for the patient
    for(int x = 0; x< patients.size(); x++){
        if(delID == patients[x].ID){
            found = true;
            cout<<endl;
            cout<<"This ID matches patient "<<x+1<<". Are you sure you want to remove this patient's records from the directory? Y/N? ";
            getline(cin, confirm);
            if(confirm == "y" || confirm == "Y"){
                cout<<"yes";
                patients.erase(patients.begin()+x);
                cout<<endl<<"\nThe patient's records have been deleted"<<endl;
                return;
            }
            else if(confirm == "n" || confirm =="N"){
                cout<<"The patient will not be deleted from the database."<<endl;
                return;
            }
            else{
                cout<<"Invalid input. Please only enter a single letter option. Yes(Y) or No (N)."<<endl;
                return;
            }
        }
    }
    //input validation
    if(!found){
        cout<<"Unable to delete patient. \nThis ID does not match a patient in the database."<<endl;
    }
}
