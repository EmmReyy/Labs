//IMPORTANT NOTE: /n in windows counts as 2 bytes.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void writeData();
void displayFile();
void showWithPositions();
void handleUserActions();

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
    //open file in output mode (this clears existing content)
    fstream file("data.txt", ios::out);

    if (!file) {
        cout << "error opening file for writing\n";
        return;
    }

    string line;

    //ask user to input multiple lines
    cout << "enter lines to write to file (type END to stop):\n";

    while (true) {
        getline(cin, line);

        //stop condition
        if (line == "END") break;

        //write each line into file
        file << line << endl;
    }

    //tellp returns current position of write pointer
    cout << "position after writing: " << file.tellp() << endl;

    file.close();
}

//function to display entire file content
void displayFile() {
    //open file in input mode
    fstream file("data.txt", ios::in);

    if (!file) {
        cout << "error opening file\n";
        return;
    }

    string line;

    cout << "\nfinal file content:\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

//function to read file and show positions
void showWithPositions() {
    //open file in input mode
    fstream file("data.txt", ios::in);

    if (!file) {
        cout << "error opening file for reading\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        cout << "line: " << line << endl;

        //tellg returns current read pointer position
        cout << "at position: " << file.tellg() << endl;

        cout << endl;
    }

    file.close();
}

//function to handle user menu actions
void handleUserActions() {
    int choice;

    while (true) {
        cout << "\nwhat do you want to do now?\n";
        cout << "[1] go back to beginning\n";
        cout << "[2] read at a specific position\n";
        cout << "[3] write at a specific position\n";
        cout << "[4] end\n";
        cout << "enter choice: ";
        cin >> choice;

        if (choice == 4) {
            cout << "ending program...\n";
            break;
        }

        fstream file;

        switch (choice) {

            case 1: {
                file.open("data.txt", ios::in);

                if (!file) {
                    cout << "error opening file\n";
                    break;
                }

                string line;

                file.seekg(0);

                cin.ignore();
                getline(file, line);

                cout << "first line again: " << line << endl;

                file.close();
                break;
            }

            case 2: {
                file.open("data.txt", ios::in);

                if (!file) {
                    cout << "error opening file\n";
                    break;
                }

                int pos;
                string line;

                cout << "enter position: ";
                cin >> pos;

                file.clear();
                file.seekg(pos);

                cin.ignore();
                getline(file, line);

                cout << "line from that position: " << line << endl;

                file.close();
                break;
            }

            case 3: {
                file.open("data.txt", ios::in | ios::out);

                if (!file) {
                    cout << "error opening file\n";
                    break;
                }

                int pos;
                string text;

                cout << "enter position: ";
                cin >> pos;

                file.seekp(pos);

                cin.ignore();
                cout << "enter text to overwrite: ";
                getline(cin, text);

                file << text;

                file.close();
                break;
            }

            default:
                cout << "invalid choice\n";
        }
    }
}