#include <cstdint>
#include <iostream>
#include <bitset>
#include <limits>
int count_leading_zeros(uint16_t value) {
    if (value == 0) return 16;
    return __builtin_clz(value)-16; 
}
int count_leading_zeros(uint8_t value) {
    if (value == 0) return 8;
    return __builtin_clz(value)-24; 
}
void vlnpd(uint8_t dividend, uint8_t divisor, uint8_t& quotient, uint8_t& remainder) {
    if (divisor == 0) {
        std::cerr << "Error: Division by zero\n";
        quotient = remainder = 0;
        return;
    }

    uint16_t R = static_cast<uint16_t>(dividend);
    uint8_t D = divisor;
    int count = 0;
    int division_complete = 0;

    while(division_complete==0){
        int leading_D = count_leading_zeros(D);
        int leading_R = count_leading_zeros(R);
        std::cout<<"leading_D: " << leading_D << std::endl;
        std::cout<<"leading_R: " << leading_R << std::endl;
        
        //Dynamic Shift
        int shift_amount = leading_R - leading_D - 1;
        if (shift_amount > 0) {
            if (shift_amount > 7 - count) {
                shift_amount = 7 - count;
            }
            R <<= shift_amount;
            count += shift_amount;
        }
        //Classic Division Step
        //temporary variable to hold bits 14:7 of R
        uint8_t tempDiv = static_cast<uint8_t>((R >> 7) & 0xFF); // Extract bits 14:7
        int8_t difference = tempDiv - divisor;
        if(difference<0){
            R<<=1;
        }
        else{
            // Clear bits 14:7
            R &= ~(0xFF << 7);
            // Set bits 14:7 to 'difference' (cast to uint8_t to mask lower 8 bits)
            R |= (static_cast<uint16_t>(static_cast<uint8_t>(difference)) << 7);
            // Set bit 0
            R |= 1ULL;
        }
        
        if(++count == 8) {
            division_complete = 1;
        }
    }
    // Extract the lower 8 bits (bits 7:0)
    quotient = static_cast<uint8_t>(R & 0xFF); 
    // Extract the upper 8 bits (bits 15:8)
    remainder = static_cast<uint8_t>(R >> 8);
}
int main(){
        // uint8_t dividend = 6;
    // uint8_t divisor = 2;
    // uint8_t quotient = 0, remainder = 0;
    // vlnpd(dividend, divisor, quotient, remainder);
    return 0;
}