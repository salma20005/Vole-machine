
#ifndef A1_T4_S21_20230571_2023119_20230172_CPU_H
#define A1_T4_S21_20230571_2023119_20230172_CPU_H

#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "Instructions.h"
#include<iostream>
#include<vector>
using namespace std;
class CPU {
private:
    Instructions instr;
    Memory& mem;  // Store reference to Memory
    Register reg;
    ALU alu;

public:
    int count;
    void displayStatus(int startAddress); // Make sure this matches the function in CPU.cpp
    CPU(Memory& memory) : mem(memory), count(0) {} // Initialize mem with provided Memory reference

    void loadProgram(const vector<string>& program, int startAddress);
    void execute();
};


#endif //A1_T4_S21_20230571_2023119_20230172_CPU_H
