#include "Register.h"
#include <iostream>
using namespace std;


Register::Register(){};

int Register::getData(int number) {
    // Checking the validity of register numbers (0-15)
    if (number < 0 || number >= size) {
        cout << "Invalid register number" << endl;
        return -1;
    }
    return registers[number];
}

void Register::setData(int number, int value) {
    if (number < 0 || number >= size) {
        cout << "Invalid register number" << endl;
        return;
    }
    // Checking the validity of the hexadecimal number
    if (value < 0x00 || value > 0xFF) {
        cout << "Value out of range (must be between 00 and FF)" << endl;
        return;
    }
    // Add the value in the register vector
    registers[number] = value;
}


