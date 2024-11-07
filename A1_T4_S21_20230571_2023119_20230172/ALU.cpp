#include "ALU.h"
#include<iostream>
using namespace std;
string ALU::hexToBinary(int hexValue) {
    return bitset<8>(hexValue).to_string();
}
int ALU::binaryToHex(const std::string &binaryStr) {
    return stoi(binaryStr, nullptr, 2);
}
void ALU::executeAddTwosComplement(Register &reg, int opcode1, int opcode2, int opcodeResult) {
    // Extract register numbers for result (R), source (S), and destination (T)
    // Extract register numbers from opcodes
    int resultR = opcode1 & 0xF;       // Destination register from the high nibble of opcode1
    int sourceR1 = (opcode2 >> 4) & 0xF;                 // First source register from the low nibble of opcode1
    int sourceR2 = opcode2 & 0xF;              // Second source register from the low nibble of opcode2

    // Fetch values from the specified source registers
    int value1 = reg.getData(sourceR1);
    int value2 = reg.getData(sourceR2);
    // Debug: Print extracted registers
    cout << "Extracted Registers: " << endl;
    cout << "resultR (destination): R" << resultR << endl;
    cout << "sourceR1: R" << sourceR1 << endl;
    cout << "sourceR2: R" << sourceR2 << endl;

    // Apply sign extension (to handle two's complement values)
    if (value1 & 0x80) value1 -= 0x100;  // If the value is negative, extend the sign
    if (value2 & 0x80) value2 -= 0x100;  // Similarly for the second value

    // Perform the addition
    int result = value1 + value2;

    // Mask to ensure the result is an 8-bit value (ensure it fits in a byte)
    result &= 0xFF;

    // Store the result in register R
    reg.setData(resultR, result);
    cout << "Stored result in R" << resultR << ": " << result << endl;
}

void ALU::executeAddFloatingPoint(Register &reg, int opcode1, int opcode2, int opcodeResult) {
    // Extract register numbers for result (R), source (S), and destination (T)
    // Extract register numbers from opcodes
    int resultR = opcode1 & 0xF;       // Destination register from the high nibble of opcode1
    int sourceR1 = (opcode2 >> 4) & 0xF;    // First source register from the low nibble of opcode1
    int sourceR2 = opcode2 & 0xF;              // Second source register from the low nibble of opcode2

    // Fetch values from the specified source registers
    int value1 = reg.getData(sourceR1);
    int value2 = reg.getData(sourceR2);
    cout << "Extracted Registers: " << endl;
    cout << "resultR (destination): R" << resultR << endl;
    cout << "sourceR1: R" << sourceR1 << endl;
    cout << "sourceR2: R" << sourceR2 << endl;

    // Converting hex to binary strings
    string binary1 = hexToBinary(value1);
    string binary2 = hexToBinary(value2);
    cout << "Binary representations: " << endl;
    cout << "binary1: " << binary1 << endl;
    cout << "binary2: " << binary2 << endl;
    // Parsing sign, exponent, and mantissa from binary representation
    int sign1 = binary1[0] - '0';
    int exp1 = stoi(binary1.substr(1, 3), nullptr, 2) - 4;
    int mantissa1 = stoi(binary1.substr(4), nullptr, 2);

    int sign2 = binary2[0] - '0';
    int exp2 = stoi(binary2.substr(1, 3), nullptr, 2) - 4;
    int mantissa2 = stoi(binary2.substr(4), nullptr, 2);

    // Align exponents by shifting mantissas if necessary
    if (exp1 > exp2) {
        mantissa2 >>= (exp1 - exp2);
        exp2 = exp1;
    } else if (exp2 > exp1) {
        mantissa1 >>= (exp2 - exp1);
        exp1 = exp2;
    }

    // Applying sign to mantissas
    if (sign1) mantissa1 = -mantissa1;
    if (sign2) mantissa2 = -mantissa2;

    // Perform mantissa addition
    int resultMantissa = mantissa1 + mantissa2;
    int resultSign = resultMantissa < 0;
    if (resultSign) resultMantissa = -resultMantissa;

    // Normalize result if mantissa exceeds 4 bits
    int resultExp = exp1;
    while (resultMantissa >= 16) {  // While it exceeds 4 bits, shift right
        resultMantissa >>= 1;
        resultExp++;
    }

    // Handling case where result mantissa might underflow below 4 bits
    while (resultMantissa > 0 && resultMantissa < 8 && resultExp > -4) {
        resultMantissa <<= 1;
        resultExp--;
    }
    // Convert result back to binary representation
    string resultBinary = (resultSign ? "1" : "0") +
                          bitset<3>(resultExp + 4).to_string() +
                          bitset<4>(resultMantissa).to_string();
    int resultHex = binaryToHex(resultBinary);

    // Store the result in the specified register
    reg.setData(resultR, resultHex);
    cout << "Final result in binary: " << resultBinary << endl;
    cout << "Final result in hexadecimal: " << hex << resultHex <<dec << endl;
}
