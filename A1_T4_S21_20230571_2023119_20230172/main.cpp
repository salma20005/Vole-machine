#include "CPU.h"
#include "Memory.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Function to load instructions from the entered file
void LoadingInstructions(const string& filename, vector<string>& program) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        // Extract the input as pairs
        for (size_t i = 0; i < line.length(); i += 2) {
            string instruction = line.substr(i, 2);
            program.push_back(instruction);
        }
    }

    infile.close();
}

// Function to display instruction set
void displayInstructions() {
    cout << "[1 RXY] copy content of cell XY to register R\n"
            "[2 RXY] copy bit string XY to register R\n"
            "[3 RXY] copy content of register R to cell XY\n"
            "[4 xRS] copy content of register R to register S\n"
            "[5 RST] Add register S and T and put result in R (using 2's complement)\n"
            "[6 RST] Add register S and T and put result in R (using floating point notation)\n"
            "[7 RST] Bitwise OR register S and T and put result in R\n"
            "[8 RST] Bitwise AND register S and T and put result in R\n"
            "[9 RST] Bitwise XOR register S and T and put result in R\n"
            "[A RxX] Rotate the content of register R cyclically right x steps\n"
            "[B RXY] Jump to cell XY if content of register R equals content of register 0\n"
            "[C xxx] Halt execution\n"
            "[D RXY] Jump to cell XY if content of register R is greater than content of register 0\n"
            "______________________________\n";
}

int main() {
    cout << "___________Welcome!___________\n";
    unsigned int startAddress = 0x0A;  // Default starting address 10
    string choice1, choice2, choice3;

    Memory memory;  // Initialize Memory with default parameters
    CPU cpu(memory);  // Pass the Memory object to CPU

    while (true) {
        cout << "1) Enter file \n2) Display instructions\n3) Display program counter\n4) Exit\n";
        getline(cin, choice1);

        if (choice1 == "1") {
            string fileName;
            cout << "Please enter the instructions file name:\n";
            cin >> fileName;
            cin.ignore();

            while (true) {
                cout << "1) Enter starting address\n2) Use the default (0A)\n";
                getline(cin, choice2);

                if (choice2 == "1") {
                    cout << "Enter starting memory address in hexadecimal: ";
                    string input;
                    getline(cin, input);

                    // Ensure valid hexadecimal input within range
                    while (true) {
                        try {
                            startAddress = stoi(input, nullptr, 16);  // Convert hex input to int
                            if (startAddress > 0xFF || startAddress < 1) {  // Check validity of range
                                throw out_of_range("Out of range");
                            }
                            break;
                        } catch (const invalid_argument&) {
                            cout << "Please enter a valid hexadecimal number\n";
                            getline(cin, input);
                        } catch (const out_of_range&) {
                            cout << "Number out of range (1-FF). Please enter a number within the range:\n";
                            getline(cin, input);
                        }
                    }
                    break;

                } else if (choice2 == "2") {
                    break;
                } else {
                    cout << "Invalid choice!\n";
                }
            }

            vector<string> program;
            LoadingInstructions(fileName, program);
            if (program.empty()) {
                cerr << "No valid instructions loaded from the file." << endl;
                continue;
            }

            // Load program into memory starting from the specified address
            cpu.loadProgram(program, startAddress);
            cpu.execute();
            cpu.displayStatus(startAddress);
            cout << "___________________________\n";

        } else if (choice1 == "2") {
            displayInstructions();

        } else if (choice1 == "3") {
            cout <<"Current program count: " << cpu.count << endl;

        } else if (choice1 == "4") {
            break;

        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
