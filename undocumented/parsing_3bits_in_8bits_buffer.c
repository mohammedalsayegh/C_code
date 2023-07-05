// Name: Mohammed Alsayegh

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define size_parsing 3
#define size_buffer 8

int main() {

    uint8_t arr_n[] = {0b101, 0b001, 0b111, 0b001, 0b111, 0b000, 0b001, 0b010, 0b001, 0b011, 0b111, 0b001}; // test parsing 3-bit (167,158,10,47)
    //uint8_t arr_n[] = {0b00101, 0b00001, 0b00111, 0b00001, 0b00111, 0b00000, 0b00001, 0b00010, 0b00001, 0b00011, 0b00111, 0b00001}; //test parsing 5-bit, (40,78,19,128,34,8,206)
    //uint8_t arr_n[] = {0b0000101, 0b0000001, 0b0000111, 0b0000001, 0b0000111, 0b0000000, 0b0000001, 0b0000010, 0b0000001, 0b0000011, 0b0000111, 0b0000001}; //test parsing 7-bit (10,4,56,16,224,0,130,2,12,56)

    int i;
    unsigned int len = sizeof(arr_n);

    uint8_t buf = 0;
    uint8_t bitwise_location = size_buffer;
    uint8_t bit_left = 0;
    uint8_t bit_fill_left = 0;
    uint8_t buf_cycle = 0;
    bool buf_full = false;

    // Loop through each byte of the array
    for (i = 0; i < len; ++i) {

        if (buf_cycle < size_parsing && buf_full == true) buf |= arr_n[i - 1] << (bitwise_location);

        // Update the buffer if the bit parsed size is greater than the remaining space
        if (bitwise_location < size_parsing) {
            printf("Im here! \t");
            buf_full = true;
            buf_cycle++;
            bit_left = bitwise_location;
            bit_fill_left = arr_n[i] >> (size_parsing - bit_left);
            buf |= bit_fill_left;

            printf("Value: %hhu\n", buf);

            buf = 0;
            bitwise_location = size_buffer - (size_parsing - bit_left);
            if (!(buf_cycle % size_parsing)) buf_cycle = 0;

        } else {

            bitwise_location -= size_parsing;
            buf |= arr_n[i] << (bitwise_location);
            buf_full = false;
        }
    }

    // If there are any remaining bits in the last byte, shift them into the buffer
    if (buf_cycle % size_parsing) {
        --i;
        buf |= arr_n[i] << (bitwise_location);
        printf("Value: %hhu\n", buf);
    }  

    return 0;
}