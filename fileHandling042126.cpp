#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::string filename;
    int num;

    //asks user for the filename
    std::cout << "Enter filename to create: ";
    std::cin >> filename;

    //used constructor to open file
    std::ofstream outFile(filename);

    //if outfile was not opened, print error and stop the code
    if (!outFile) {
        std::cout << "Error creating file!" << std::endl;
        return 1;
    }

    //ask for input numbers
    std::cout << "Enter integers (enter -1 to stop): " << std::endl;

    //constinously read input unless input is -1, if so, it breaks out
    while (true) {
        std::cin >> num;
        if (num == -1) break;

        //since output file is a stream, we used the insertion operator to append
        //since we don really need the data to persist after every run, using << is simpler
        outFile << num << std::endl;
    }

    //close the file
    outFile.close();

    //read the file
    std::ifstream inFile(filename);

    //if file not opened print error
    if (!inFile) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    //used vector to store the numbers
    //vector was used since size is not defined and thus array cant be used without handling memory
    std::vector<int> numbers;
    int value;

    //will loop until reading inFile fails
    //in other words, loop will continue until no more items are left
    while (inFile >> value) {
        numbers.push_back(value);
    }

    //close the inFile
    inFile.close();

    //calculate sum
    int sum = 0;
    std::cout << "\nNumbers in file: ";
    for (int n : numbers) {
        std::cout << n << " ";
        sum += n;
    }

    //print an extra line to compensate
    std::cout << std::endl;

    //calculate average
    double average = 0.0;
    if (!numbers.empty()) {
        average = (double)sum / numbers.size();
    }

    //display sum and average
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;

    return 0;
}