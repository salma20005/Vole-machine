#include "Memory.h"

using namespace std;

// Constructor with start address
Memory::Memory(int startAddr) {
    start_address = startAddr;
}

// Function to load data at the memory vector
void Memory::loadData(int address, int value) {
    memory_vec[address] = value;
}

int Memory::getData(int address) {
    return memory_vec[address];
}
