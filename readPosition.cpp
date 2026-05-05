#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//function to write data into file
void writeData() {
    //open file in output mode
    fstream file("data.txt", ios::out);

    //check if file opened successfully
    if (!file) {
        cout << "error opening file for writing\n";
        return;
    }

    //write multiple lines into file
    file << "first line\n";
    file << "second line\n";
    file << "third line\n";

    //display current position after writing
    cout << "position after writing: " << file.tellp() << endl;

    //ask user if they want to overwrite at specific position
    char choice;
    cout << "overwrite at specific position? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int pos;
        string text;

        //ask for position
        cout << "enter position: ";
        cin >> pos;

        //move write pointer
        file.seekp(pos);

        //ask for new text
        cout << "enter text to overwrite: ";
        cin.ignore();
        getline(cin, text);

        //overwrite text
        file << text;
    }

    //close file
    file.close();
}

//function to read data from file
void readData() {
    //open file in input mode
    fstream file("data.txt", ios::in);

    //check if file opened successfully
    if (!file) {
        cout << "error opening file for reading\n";
        return;
    }

    string line;

    //read file line by line
    while (getline(file, line)) {
        cout << "read: " << line << endl;

        //display current read position
        cout << "current read position: " << file.tellg() << endl;
    }

    //ask user what to do next
    char choice;
    cout << "go back to beginning? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        //clear eof flag and move pointer to beginning
        file.clear();
        file.seekg(0);

        //read first line again
        getline(file, line);
        cout << "first line again: " << line << endl;
    } else {
        int pos;

        //ask for specific position
        cout << "enter position to move to: ";
        cin >> pos;

        //clear eof flag and move pointer
        file.clear();
        file.seekg(pos);

        //read from that position
        getline(file, line);
        cout << "line from that position: " << line << endl;
    }

    //close file
    file.close();
}

int main() {
    //write data
    writeData();

    cout << "---------------------\n";

    //read data
    readData();

    return 0;
}