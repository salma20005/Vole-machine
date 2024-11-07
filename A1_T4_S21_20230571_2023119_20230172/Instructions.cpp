#include "Instructions.h"
#include "Memory.h"
#include <iostream>
#include <iomanip>

using namespace std;

int extractSourceRegister(int opcode) {
    return (opcode >> 4) & 0xF;
}

int extractDestinationRegister(int opcode) {
    return opcode & 0xF;
}
int Instructions::extractRegisterNumber(int opcode) {
    int registerNumber = (opcode >> 4) & 0xF;  // Extract register number from the opcode
    cout << "Extracted Register Number: " << registerNumber << " from Opcode: " << hex << opcode << endl;
    return registerNumber;
}

int Instructions::extractMemoryAddress(int opcode) {
    return opcode & 0xFF;
}

void Instructions::executeLoad(Register &reg, int regNumber, int memoryAddress, Memory &memory) {
    int value = memory.getData(memoryAddress);  // Get data from memory address
    cout << "Get " << value << " from memory address " << hex << memoryAddress << endl;

    reg.setData(regNumber, value);  // Set the value in the specified register
    cout << "Register R" << hex << regNumber << " set to " << value << endl;
}


void Instructions::executeLoadImmediate(Register& reg, int regNumber , int value) {
    reg.setData(regNumber, value);  // Set the value to the correct register
    cout << "Register R" << hex << uppercase << regNumber
         << " set to " <<hex << uppercase << value << endl;
}

// 3005
void Instructions::executeStore(Register &reg, int opcode, int regNumber, Memory &mem) {
    int address = extractMemoryAddress(opcode);
    int dataToStore = reg.getData(regNumber);    // Get the data to be stored from the specified register

    cout << "Register R" << regNumber << " contains " << hex << dataToStore << endl;
    mem.loadData(address, dataToStore);          // Store the value in memory at the extracted address
    cout << "Stored value " << dataToStore << " from Register R" << regNumber << " to Memory Address "  << address << endl;
}


void Instructions::executeMove(Register &reg, int opcode) {

    int sourceR = extractSourceRegister(opcode);
    int destinationR = extractDestinationRegister(opcode);
    int data = reg.getData(sourceR);
    reg.setData(destinationR, data);
    cout << "Moved value from Register R" << sourceR << " to Register R" << destinationR << endl;
}

void Instructions::executeOr(Register &reg, int opcode, int opcodeResult) {
    int sourceR = extractSourceRegister(opcode);
    int destinationR = extractDestinationRegister(opcode);
    int resultR = extractDestinationRegister(opcodeResult);
    int result = reg.getData(sourceR) | reg.getData(destinationR);
    reg.setData(resultR, result);
    cout << "Performed OR on R" << sourceR << " and R" << destinationR << ", result stored in R" << resultR << endl;
}

void Instructions::executeAnd(Register &reg, int opcode, int opcodeResult) {
    int resultR = extractDestinationRegister(opcodeResult);
    int sourceR = extractSourceRegister(opcode);
    int destinationR = extractDestinationRegister(opcode);
    int result = reg.getData(sourceR) & reg.getData(destinationR);
    reg.setData(resultR, result);
    cout << "Performed AND on R" << sourceR << " and R" << destinationR << ", result stored in R" << resultR << endl;
}


void Instructions::executeXor(Register &reg, int opcode, int opcodeResult) {
    int resultR = extractDestinationRegister(opcodeResult);
    int sourceR = extractSourceRegister(opcode);
    int destinationR = extractDestinationRegister(opcode);
    int result = reg.getData(sourceR) ^ reg.getData(destinationR);
    reg.setData(resultR, result);
    cout << "Performed XOR on R" << sourceR << " and R" << destinationR << ", result stored in R" << resultR << endl;
}

void Instructions::executeRotateRight(Register &reg, int opcode, int numBits) {
    int R = extractSourceRegister(opcode);
    unsigned int data = reg.getData(R);
    int rotatedData = (data >> numBits) | (data << (8 - numBits));
    rotatedData &= 0xFF;  // Ensure it stays within 8 bits
    reg.setData(R, rotatedData);
    cout << "Rotated R" << R << " right by " << numBits << " bits, new value: " << hex << rotatedData << endl;
}

void Instructions::executeConditionalJump(Register &reg, int opcode, int &programCounter,Memory &mem) {
    // Extract the register and memory address from the opcode
    int regAddress = extractSourceRegister(opcode);
    int memAddress = extractMemoryAddress(opcode);
    int value1 = reg.getData(regAddress);
    int value2 = mem.getData(0);

    cout << "Comparing value in register R" << regAddress << " (" << value1 << ") with value at memory address 00 (" << value2 << ")" << endl;

    if (value1 == value2) {
        programCounter = memAddress;  // Update programCounter to jump to the target address
        cout << "Jumped to address " << hex << memAddress << " as R" << regAddress << " = M00" << endl;
    } else {
        programCounter += 2;  // No jump, proceed to next instruction
        cout << "No jump; moved to next instruction" << endl;
    }
}

void Instructions::executeConditionalJumpGreaterThan(Register &reg, int opcode, int &programCounter, Memory &mem) {
    // Extract the register and memory address from the opcode
    int regAddress = extractSourceRegister(opcode);
    int memAddress = extractMemoryAddress(opcode);
    int value1 = reg.getData(regAddress);
    int value2 = mem.getData(0);

    cout << "Comparing value in register R" << regAddress << " (" << value1 << ") with value at memory address 00 (" << value2 << ")" << endl;

    if (value1 > value2) {
        programCounter = memAddress;  // Update programCounter to jump to the target address
        cout << "Jumped to address " << hex << memAddress << " as R" << regAddress << " > M00" << endl;
    } else {
        programCounter += 2;  // No jump, proceed to next instruction
        cout << "No jump; moved to next instruction" << endl;
    }

}


bool Instructions::executeHalt() {
    cout << "program stopped due to C000.\n" << endl;
    return false;
}
