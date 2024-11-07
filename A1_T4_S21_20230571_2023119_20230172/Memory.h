
#ifndef A1_T4_S21_20230571_2023119_20230172_MEMORY_H
#define A1_T4_S21_20230571_2023119_20230172_MEMORY_H

#include <vector>
#include <iostream>

using namespace std;

class Memory {
private:
    // Initialize a vector of memory by zeros
    vector<int> memory_vec = vector<int>(256, 0);
    int start_address; // Start address

public:
    // Constructor with a start address parameter
    Memory(int startAddr = 0x0A); // Default is 0x0A if no argument is passed

    // Function to get the data at the calculated address
    int getData(int address);

    // Loads a value into the calculated memory address
    void loadData(int address, int value);
};


#endif //A1_T4_S21_20230571_2023119_20230172_MEMORY_H
