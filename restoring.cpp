#include <cstdint>
#include <iostream>
#include <bitset>
#include <limits>

void restoringDivision(uint32_t dividend, uint32_t divisor, uint32_t& quotient, uint32_t& remainder, int& count) {
    uint64_t AQ = static_cast<uint64_t>(dividend);
    int n = 32;
    while (n > 0) {
        AQ <<= 1;
        int32_t temp = static_cast<int32_t>((AQ >> 32) & 0xFFFFFFFF); // 32 górne bity
        temp -= divisor;
        // przywrócenie bitów do AQ
        AQ &= 0xFFFFFFFF; // Wyczyszczenie górnych 32 bitów AQ
        AQ |= (static_cast<uint64_t>(static_cast<uint32_t>(temp)) << 32); // wynik odejmowania w górnych 32 bitach
        if (temp >= 0) {
            AQ |= 1; // AQ[0]=1
        } else {
            AQ &= ~1; // AQ[0]=0
            // Przywrócenie AQ 
            temp += static_cast<int64_t>(divisor);
            AQ &= 0xFFFFFFFF; // Wyczyszczenie górnych 32 bitów AQ
            AQ |= (static_cast<uint64_t>(static_cast<uint32_t>(temp)) << 32);
        }
        n--;
        count++;
    }
    quotient = AQ & 0xFFFFFFFF; // dolne 32 bity
    remainder = (AQ >> 32) & 0xFFFFFFFF; //górne 32 bity
}

int main(){
    int count=0;
    uint32_t dividend = 0;
    uint32_t divisor = 0;
    uint32_t quotient = 0;
    uint32_t remainder = 0;
    std::cin>>dividend;
    std::cin>>divisor;
    restoringDivision(dividend, divisor, quotient, remainder,count);
    std::cout << "Iloraz: " << quotient << std::endl;
    std::cout << "Reszta: " << remainder << std::endl;
    std::cout << "Ilosc iteracji: " << count << std::endl;
}