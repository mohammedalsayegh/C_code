// Name: Mohammed Alsayegh
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define size_parsing 3

int main() 
{
    uint8_t arr_n[] = {0b101, 0b001, 0b111, 0b001, 0b111, 0b000, 0b001, 0b010, 0b001, 0b011, 0b111, 0b001};

    int i;
    unsigned int len = sizeof(arr_n);
    uint8_t buf=0;
    uint8_t bitwise_location = 8;
    uint8_t bit_left=0;
    uint8_t bit_fill_left=0;
    uint8_t buf_cycle=0;
    bool buf_full=false;

    for (i = 0; i < len; ++i) 
    {
        if (bitwise_location < size_parsing) {
            buf_full = true;
            buf_cycle++;
            bit_left = bitwise_location;
            bit_fill_left = arr_n[i] >> (size_parsing - bit_left);
            buf |= bit_fill_left;

            printf("Value: %hhu\n", buf);

            buf = 0;
            bitwise_location = 8 - (size_parsing - bit_left);
            if (!(buf_cycle % size_parsing)) buf_cycle = 0;
        } else {
            if (buf_cycle < size_parsing && buf_full == true) buf |= arr_n[i - 1] << (bitwise_location);
            buf_full = false;
            bitwise_location = bitwise_location - size_parsing;
            buf |= arr_n[i] << (bitwise_location);
        }
    }

    if (buf_cycle % size_parsing) 
    {
        --i;
        buf |= arr_n[i] << (bitwise_location);
        printf("Value: %hhu\n", buf);
    }  

    return 0;
}