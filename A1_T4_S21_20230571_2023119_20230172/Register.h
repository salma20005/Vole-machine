
#ifndef A1_T4_S21_20230571_2023119_20230172_REGISTER_H
#define A1_T4_S21_20230571_2023119_20230172_REGISTER_H
#include<string>
#include<stdexcept>
class Memory;
class Register {
private:
    // Making a vector of register of size 16
    static constexpr int size = 16;
    int registers[size] ={0};
public:
    Register();
    int getData(int number);
    void setData(int number , int value);

};
#endif //A1_T4_S21_20230571_2023119_20230172_REGISTER_H
