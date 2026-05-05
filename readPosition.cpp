#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//function to display entire file content
void displayFile() {
    //open file in input mode
    fstream file("data.txt", ios::in);

    //check if file opened
    if (!file) {
        cout << "error opening file\n";
        return;
    }

    string line;

    cout << "\nfinal file content:\n";

    //read and display all lines
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

//function to write data into file
void writeData() {
    //open file in output mode
    fstream file("data.txt", ios::out);

    if (!file) {
        cout << "error opening file for writing\n";
        return;
    }

    string line;

    //ask user for multiple lines
    cout << "enter lines to write to file (type END to stop):\n";

    while (true) {
        getline(cin, line);

        if (line == "END") {
            break;
        }

        file << line << endl;
    }

    //display position after writing
    cout << "position after writing: " << file.tellp() << endl;

    //ask for overwrite
    char choice;
    cout << "overwrite at specific position? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int pos;
        string text;

        cout << "enter position: ";
        cin >> pos;

        //move write pointer
        file.seekp(pos);

        cin.ignore();

        cout << "enter text to overwrite: ";
        getline(cin, text);

        file << text;
    }

    file.close();
}

//function to read data from file
void readData() {
    //open file
    fstream file("data.txt", ios::in);

    if (!file) {
        cout << "error opening file for reading\n";
        return;
    }

    string line;

    //read line by line
    while (getline(file, line)) {
        cout << "line: " << line << endl;
        cout << "at position: " << file.tellg() << endl;
        cout << endl;
    }

    char choice;
    cout << "go back to beginning? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        file.clear();
        file.seekg(0);

        getline(file, line);
        cout << "first line again: " << line << endl;
    } else {
        int pos;

        cout << "enter position to move to: ";
        cin >> pos;

        file.clear();
        file.seekg(pos);

        getline(file, line);
        cout << "line from that position: " << line << endl;
    }

    file.close();
}

int main() {
    //write data
    writeData();

    cout << "---------------------\n";

    cin.ignore();

    //read data
    readData();

    //final display before program ends
    displayFile();

    return 0;
}