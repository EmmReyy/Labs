//IMPORTANT NOTE: /n in windows counts as 2 bytes.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//function declarations
void writeData();            // write multiple lines entered by user into a file
void displayFile();          // display the final content of the file
void showWithPositions();    // read file line by line and show file positions
void handleUserActions();    // main menu for user interactions (read/write/exit)
void readCharAtPosition();   // read a single character at a specific position

int main() {
    //start by writing data into file
    writeData();

    cout << "---------------------\n";

    //display file with positions after writing
    showWithPositions();

    //present user with menu actions (looped until exit)
    handleUserActions();

    //final display before program ends
    displayFile();

    return 0;
}

//function to write data into file
void writeData() {
    //open file in output mode, binary mode, and truncate existing content
    //binary mode ensures positions are exact bytes and no CRLF translation occurs
    fstream file("data.txt", ios::out | ios::binary | ios::trunc);

    if (!file) {   //check if file opened successfully
        cout << "error opening file for writing\n";
        return;
    }

    string line;

    //ask user to input multiple lines
    cout << "enter lines to write to file (type END to stop):\n";

    while (true) {
        getline(cin, line);  // read a full line including spaces

        //stop condition
        if (line == "END") break;

        //write each line into file followed by a newline character '\n'
        //using '\n' is important for predictable byte counts in binary mode
        file << line << "\n";
    }

    //tellp returns current position of write pointer (i.e., file size in bytes after writing)
    cout << "position after writing: " << file.tellp() << endl;

    file.close(); //close file to flush data
}

//function to display entire file content
void displayFile() {
    //open file in input mode and binary mode
    fstream file("data.txt", ios::in | ios::binary);

    if (!file) {   //check if file opened successfully
        cout << "error opening file\n";
        return;
    }

    //skip BOM if present at beginning of file
    //BOM (Byte Order Mark) is 3 bytes at start of UTF-8 file that can interfere with first character
    char first = file.peek();  //look at first byte without extracting
    if ((unsigned char)first == 0xEF) {  
        file.get(); file.get(); file.get(); //discard 3 BOM bytes
    }

    string line;

    cout << "\nfinal file content:\n";

    //read file line by line
    while (getline(file, line)) {
        cout << line << endl;  //print each line to console
    }

    file.close(); //close file
}

//function to read file and show positions
void showWithPositions() {
    //open file in input mode and binary mode
    fstream file("data.txt", ios::in | ios::binary);

    if (!file) {
        cout << "error opening file for reading\n";
        return;
    }

    //skip BOM if present
    char first = file.peek();
    if ((unsigned char)first == 0xEF) {
        file.get(); file.get(); file.get();
    }

    string line;

    //loop until end of file
    while (true) {
        streampos posBefore = file.tellg();  //position before reading line
        cout << "pos before: " << posBefore << endl;

        //read a line from file; if EOF, break loop
        if (!getline(file, line)) break;

        cout << "line: " << line << endl;

        streampos posAfter = file.tellg();   //position after reading line
        cout << "position after reading line: " << posAfter << endl;
    }

    file.close();
}

//read single character at exact position
void readCharAtPosition() {
    //open file in input and binary mode
    fstream file("data.txt", ios::in | ios::binary);

    if (!file) {
        cout << "error opening file\n";
        return;
    }

    //skip BOM if present
    char first = file.peek();
    if ((unsigned char)first == 0xEF) {
        file.get(); file.get(); file.get();
    }

    int pos;
    cout << "enter position: ";
    cin >> pos;  //user enters the byte position

    file.seekg(pos); //move get pointer to the exact position

    char c;
    file.get(c); //read single character

    cout << "character at position " << pos << ": " << c << endl;

    file.close();
}

//function to handle user menu actions
void handleUserActions() {
    int choice;

    while (true) {
        cout << "\nwhat do you want to do now?\n";
        cout << "[1] go back to beginning\n";
        cout << "[2] read character at position\n";
        cout << "[3] write at a specific position\n";
        cout << "[4] end\n";
        cout << "enter choice: ";
        cin >> choice;

        if (choice == 4) {  //exit option
            cout << "ending program...\n";
            break;
        }

        fstream file;

        switch (choice) {

            case 1: {
                //open file in input and binary mode
                file.open("data.txt", ios::in | ios::binary);

                if (!file) {
                    cout << "error opening file\n";
                    break;
                }

                //skip BOM if present
                char first = file.peek();
                if ((unsigned char)first == 0xEF) {
                    file.get(); file.get(); file.get();
                }

                string line;

                file.seekg(0); //go back to beginning of file

                cin.ignore();  //clear leftover newline
                getline(file, line);  //read first line

                cout << "first line again: " << line << endl;

                file.close();
                break;
            }

            case 2: {
                readCharAtPosition(); //call function to read char at specific position
                break;
            }

            case 3: {
                //open file in read/write binary mode
                file.open("data.txt", ios::in | ios::out | ios::binary);

                if (!file) {
                    cout << "error opening file\n";
                    break;
                }

                int pos;
                string text;

                cout << "enter position: ";
                cin >> pos;  //byte position where overwrite starts

                file.seekp(pos); //move put pointer to position

                cin.ignore();  //clear newline from input buffer
                cout << "enter text to overwrite: ";
                getline(cin, text);  //read text to overwrite at position

                file << text;  //overwrite text in file

                file.close();
                break;
            }

            default:
                cout << "invalid choice\n";
        }
    }
}