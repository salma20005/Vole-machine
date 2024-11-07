
#ifndef A1_T4_S21_20230571_2023119_20230172_ALU_H
#define A1_T4_S21_20230571_2023119_20230172_ALU_H
#include "Register.h"
#include <bitset>
#include <string>
using namespace std;
class ALU {
public:

    void executeAddTwosComplement(Register &reg, int opcode1, int opcode2, int opcodeResult);
    void executeAddFloatingPoint(Register &reg, int opcode1, int opcode2, int opcodeResult);
    string hexToBinary(int hexValue);
    int binaryToHex(const std::string &binaryStr);
};

#endif //A1_T4_S21_20230571_2023119_20230172_ALU_H
