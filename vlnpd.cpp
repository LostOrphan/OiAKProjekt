#include <cstdint>
#include <iostream>
#include <bitset>
#include <limits>
int count_leading_zeros(uint64_t value) {
    if (value == 0) return 64;
    return __builtin_clzll(value); 
}
int count_leading_zeros(uint32_t value) {
    if (value == 0) return 32;
    return __builtin_clz(value); 
}

void vlnpd_divide(uint32_t dividend, uint32_t divisor, uint32_t& quotient, uint32_t& remainder) {
    if (divisor == 0) {
        std::cerr << "Error: Division by zero\n";
        quotient = remainder = 0;
        return;
    }
    
    uint64_t R = static_cast<uint64_t>(dividend);
    uint32_t D = divisor;
    std::cout << "R start: " << std::bitset<64>(R) << std::endl;
    std::cout << "D start: " << std::bitset<32>(D) << std::endl;
    int count = 0;
    int division_complete = 0;
    
    while(division_complete==0){
        int leading_D = count_leading_zeros(D);
        int leading_R = count_leading_zeros(R);

        //Dynamic Shift
        int shift_amount = leading_R - leading_D-1;
        if (shift_amount > 0) {
            if (shift_amount > 31 - count) {
                shift_amount = 31 - count;
            }
            R=R << shift_amount;
            count = count + shift_amount;
        }
        //Classic Division Step
        //temporary variable to hold bits 62:31 of R
        int32_t tempDiv = static_cast<uint32_t>((R >> 31) & 0xFFFFFFFF); // Extract bits 62:31
        int32_t difference = tempDiv - divisor;
        R = R<<1;
        if(difference<0){
        }
        else{
            //clear bits 62:31
            R &= ~(0xFFFFFFFFULL << 32);
            //Set bits 62:31 to difference
            R |= (static_cast<uint64_t>(static_cast<uint32_t>(difference)) << 32);
            R |= 1;
            std::cout << "R: " << std::bitset<64>(R) << std::endl;
        }
        if(++count == 32) {
            division_complete = 1;
        }   
        std::cout<<"count: " << count << std::endl;
    }
    std::cout << "R end: " << std::bitset<64>(R) << std::endl;
    // Extract the lower 32 bits (bits 31:0)
    quotient = static_cast<uint32_t>(R & 0xFFFFFFFF); 
    // Extract the upper 32 bits (bits 63:32)
    remainder = static_cast<uint32_t>(R >> 32);
}

int main() {
    
     uint32_t dividend = 0;
     uint32_t divisor = 0;
    uint32_t quotient = 0, remainder = 0;
    std::cin>> dividend;
    std::cin>> divisor;

    vlnpd_divide(dividend, divisor, quotient, remainder);
    std::cout << "Quotient: " << quotient << "\n";
    //cout binary
    std::cout << "Quotient: " << std::bitset<32>(quotient) << "\n";
   
    std::cout << "Remainder: " << remainder << "\n";
    //cout binary
    std::cout << "Remainder: " << std::bitset<32>(remainder) << "\n";
    return 0;
}