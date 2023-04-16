// Name: Mohammed Alsayegh
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define size_parsing 3

void print_binary(uint8_t n)
{
    unsigned i;
    for (i = 1 << 7; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}

int main() {

    uint8_t arr_n[] = {0b101, 0b001, 0b111, 0b001, 0b111, 0b000, 0b001, 0b010, 0b001, 0b011, 0b111, 0b001};

    unsigned int len = sizeof(arr_n);

    printf("len %u\n", len);
    uint8_t buf;

    int i;
    uint8_t bitwise_location = 8;
    uint8_t bit_left=0;
    uint8_t bit_fill_left=0;
    uint8_t buf_cycle=0;
    bool buf_full=false;

    for (i = 0; i < len; ++i) {
        if (bitwise_location < size_parsing) {

            buf_full = true;
            buf_cycle++;
            bit_left = bitwise_location;
            bit_fill_left = arr_n[i] >> (size_parsing - bit_left);
            buf |= bit_fill_left;
            printf("complete: buf[%u]: ",i);
            print_binary(buf);
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

    if (!(buf_cycle % size_parsing)) {
        printf("complete!\n");
        return 0;
    }
    else {
        --i;
        buf |= arr_n[i] << (bitwise_location);
        printf("buf[%u]: ",i);
        print_binary(buf);
        printf("complete!\n");
    }  

    return 0;
}