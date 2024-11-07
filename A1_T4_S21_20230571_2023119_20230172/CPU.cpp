#include "CPU.h"
#include <iostream>
#include <iomanip>
using namespace std;



void CPU::loadProgram(const std::vector<string>& program, int startAddress) {
    for (size_t i = 0; i < program.size(); ++i) {
        string instruction = program[i];

        // Convert the hex string to an integer
        int value = stoi(instruction, nullptr, 16);
        mem.loadData(startAddress + i, value);  // Store in memory
        cout << "Loaded Memory[" << startAddress + i << "] = " << instruction << endl;
    }
    count = startAddress;

}

void CPU::execute() {
    bool choice = true;
    cout << "\n_________________________________OPERATIONS:_________________________________" << endl;
    while (choice) {
        // Fetch the opcode from memory using the current program counter (count)
        int opcode1 = mem.getData(count);
        int opcode2 = mem.getData(count+1);
        int opcode = (opcode1 << 8) | opcode2;  // Shift byte1 to the higher byte and combine with byte2

        int rotateSteps = opcode1 & 0x0F;

        int firstDigit = (opcode1 & 0xF0) >> 4;// Extract the first hex digit
        if (firstDigit == 0)
            break;
        int regNumber= opcode1 & 0x0F;
        int value = mem.getData(count + 1);

        switch (firstDigit) {
            case 1: // LOAD
                cout << "\n-Load operation."<< "\n";
                instr.executeLoad(reg, regNumber, value,mem);
                count += 2;
                break;

            case 2: // LOAD immediate
                cout << "\n-Load Immediate operation." << "\n";
                instr.executeLoadImmediate(reg, regNumber , value);
                count += 2;
                break;

            case 3: // STORE
                cout << "\n-Store operation." << "\n";

                // Execute the store operation
                instr.executeStore(reg, opcode2, regNumber, mem);
                count += 2;
                break;


            case 4: // MOVE
                cout << "\n-Move operation.\n";
                instr.executeMove(reg, opcode2);
                count += 2;
                break;

            case 5: // ADD (two's complement)
                cout << "\n-Add operation (two's complement).\n";
                alu.executeAddTwosComplement(reg, mem.getData(count), mem.getData(count + 1), opcode1);
                count += 2;
                break;

            case 6: // ADD (floating point)
                cout << "\n-Add operation (floating point).\n";
                alu.executeAddFloatingPoint(reg, mem.getData(count), mem.getData(count + 1), opcode1);
                count += 2;
                break;

            case 7: // OR
                cout << "\n-OR operation.\n";
                instr.executeOr(reg, mem.getData(count), mem.getData(count + 1));
                count += 2;
                break;

            case 8: // AND
                cout << "\n-AND operation\n";
                instr.executeAnd(reg, mem.getData(count), mem.getData(count + 1));
                count += 2;
                break;

            case 9: // XOR
                cout << "\n-XOR operation.\n";
                instr.executeXor(reg, mem.getData(count), mem.getData(count + 1));
                count += 2;
                break;

            case 10: // Rotate Right
                cout << "\n-Rotate Right operation.\n";
                instr.executeRotateRight(reg, opcode1, rotateSteps);
                count += 2;
                break;

            case 11: // Conditional Jump (Equal)
                cout << "\n-Conditional Jump (Equal)."<< "\n";
                instr.executeConditionalJump(reg, opcode2, count, mem);
                continue;  // Skip the normal increment of count to jump to the specified address

            case 12:
                choice = instr.executeHalt();
                break;

            case 13: // Conditional Jump (Greater Than)
                cout << "\n-Conditional Jump (Greater Than)."<< "\n";
                instr.executeConditionalJumpGreaterThan(reg, opcode2, count, mem);
                break;


            default:
                cout << "\nError! Unrecognized instruction : " << opcode1 << ", at address: " << count << endl;
                choice = false;// Terminate on unknown instruction
                count += 2; // Move to next instruction
                break;
        }
    }
}

void CPU::displayStatus(int startAddress) {
    cout << "_______________________________Register Address_______________________________\n";

    // Print header for register addresses
    for (int col = 0; col < 16; col++) {
        cout << "R" << setw(2) << setfill('0') << hex << uppercase << col << "  ";
    }
    cout << endl;

    // Print register values in hexadecimal with two digits in a 16x2 matrix
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 16; col++) {
            int index = row * 16 + col;

            // Check if index is valid; assuming a register count of 32
            if (index < 16) {
                cout << setw(2) << setfill('0') << hex << uppercase << (reg.getData(col) & 0xFF) << "   ";
            } else {
                cout << "     ";  // Empty space for invalid indexes
            }
        }
        cout << endl;
    }

    cout << "________________________________Memory Address________________________________\n";

// Print column headers for 16 addresses in a row
    for (int col = 0; col < 16; col++) {
        cout << "M" << hex << uppercase << setw(2) << setfill('0') << col << "  ";
    }
    cout << endl;

    int numRows = 16;  // For simplicity, assuming 256 addresses (16 rows * 16 columns)
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < 16; col++) {
            int address = row * 16 + col;

            if (address < startAddress) {
                // Print zeros for addresses before startAddress
                cout << "00   ";
            } else {
                // Print actual memory content for addresses at or after startAddress
                cout << setw(2) << setfill('0') << hex << uppercase
                     << (mem.getData(address) & 0xFF) << "   ";
            }
        }
        cout << endl;
    }
}
