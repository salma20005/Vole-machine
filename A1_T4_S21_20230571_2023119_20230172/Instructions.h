
#ifndef A1_T4_S21_20230571_2023119_20230172_INSTRUCTIONS_H
#define A1_T4_S21_20230571_2023119_20230172_INSTRUCTIONS_H

#include "Register.h"
#include "Memory.h"

class Instructions {

public:
    int extractRegisterNumber(int opcode);
    int extractMemoryAddress(int opcode);
    void executeLoad(Register &reg, int regNumber,int value,Memory &mem);
    void executeLoadImmediate(Register &reg, int regNumber , int value);
    void executeStore(Register &reg, int opcode, int regNumber , Memory &mem);
    void executeMove(Register &reg, int opcode);
    void executeOr(Register &reg, int opcode1, int opcodeResult);
    void executeAnd(Register &reg, int opcode1, int opcodeResult);
    void executeXor(Register &reg, int opcode1, int opcodeResult);
    void executeRotateRight(Register &reg, int opcode, int numBits);
    void executeConditionalJump(Register &reg, int opcode, int &programCounter);
    void executeConditionalJumpGreaterThan(Register &reg, int opcode, int &programCounter, Memory &mem);
    bool executeHalt();
};


#endif //A1_T4_S21_20230571_2023119_20230172_INSTRUCTIONS_H
