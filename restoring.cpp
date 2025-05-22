#include <cstdint>
#include <iostream>
#include <bitset>
#include <limits>

void restoringDivision(uint32_t dividend, uint32_t divisor, uint32_t& quotient, uint32_t& remainder) {
    uint64_t AQ = static_cast<uint64_t>(dividend);
    int n = 32;
    while (n > 0) {
        AQ <<= 1;
        int64_t temp = static_cast<int64_t>((AQ >> 32) & 0xFFFFFFFF); // Extract the upper 32 bits as signed
        temp -= static_cast<int64_t>(divisor);
        // Put the result back into AQ
        AQ &= 0xFFFFFFFF; // Clear the upper 32 bits
        AQ |= (static_cast<uint64_t>(static_cast<uint32_t>(temp)) << 32); // Set the upper 32 bits to the result
        if (temp >= 0) {
            AQ |= 1; // Set the least significant bit (bit 0) to 1
        } else {
            AQ &= ~1; // Clear the least significant bit (bit 0)
            // Restore the previous value by adding divisor back
            temp += static_cast<int64_t>(divisor);
            AQ &= 0xFFFFFFFF; // Clear the upper 32 bits again
            AQ |= (static_cast<uint64_t>(static_cast<uint32_t>(temp)) << 32);
        }
        n--;
    }
    quotient = AQ & 0xFFFFFFFF; // Extract the lower 32 bits of AQ
    remainder = (AQ >> 32) & 0xFFFFFFFF; // Extract the upper 32 bits of AQ
}

int main(){
    uint32_t dividend = 101;
    uint32_t divisor = 2;
    uint32_t quotient = 0;
    uint32_t remainder = 0;
    restoringDivision(dividend, divisor, quotient, remainder);
    std::cout << "Quotient: " << quotient << std::endl;
    std::cout << "Remainder: " << remainder << std::endl;
}