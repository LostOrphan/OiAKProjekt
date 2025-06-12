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

void vlnpd_divide(uint32_t &dividend, uint32_t &divisor, uint32_t& quotient, uint32_t& remainder, int &countIterations) {
    if (divisor == 0) {
        std::cerr << "Error: Division by zero\n";
        quotient = remainder = 0;
        return;
    }
    
    uint64_t R = static_cast<uint64_t>(dividend);
    uint32_t D = divisor;

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
        //tymczasowa zmienna do przechowywania wyniku odejmowania
        int32_t tempDiv = static_cast<uint32_t>((R >> 31) & 0xFFFFFFFF); //bity 62:31
        int32_t difference = tempDiv - divisor;
        R = R<<1;
        if(difference<0){
        }
        else{
            //czyszczenie bitów 63:32
            R &= ~(0xFFFFFFFFULL << 32);
            //bity 62:31  odejmowania
            R |= (static_cast<uint64_t>(static_cast<uint32_t>(difference)) << 32);
            R |= 1;
        }
        if(++count == 32) {
            division_complete = 1;
        }  
        countIterations++;
    }
    // 32 dolne bity
    quotient = static_cast<uint32_t>(R & 0xFFFFFFFF); 
    // 32 górne bity
    remainder = static_cast<uint32_t>(R >> 32);
}

int main() {
    uint32_t dividend = 0;
    uint32_t divisor = 0;
    uint32_t quotient = 0, remainder = 0;
    int countIterations = 0;
    std::cout<<"Podaj dzielna: ";
    std::cin>> dividend;
    std::cout<<"Podaj dzielnik: ";
    std::cin>> divisor;

    vlnpd_divide(dividend, divisor, quotient, remainder,countIterations);
    std::cout << "Iloraz zapisany dziesietnie: " << quotient << "\n";
    std::cout << "Iloraz zapisany binarnie: " << std::bitset<32>(quotient) << "\n";
   
    std::cout << "Reszta zapisana dziesietnie: " << remainder << "\n";
    std::cout << "Reszta zapisana binarnie:: " << std::bitset<32>(remainder) << "\n";

    std::cout << "Liczba iteracji: " << countIterations << "\n";
    return 0;
}