# Random Data Generator

This program generates random data and writes it to multiple CSV files. The data is generated in separate threads, so each file will contain the data for a single thread.

## Instructions

1. To run the program, you will need to provide the following command-line arguments:

    * `-r` The number of rows of data to generate.
    * `-u` The number of uint64_t values to generate for each row.
    * `-f` The number of double values to generate for each row.
    * `-s` The number of string values to generate for each row.
    * `-c` The number of char values to generate for each row.
    * `-t` The number of threads to use.

    For example, to generate 100 rows of data with 10 uint64_t values, 10 double values, 10 string values, and 10 char values per row using 10 threads, you would run the following command:

        $ ./random_data_generator -r 100 -u 10 -f 10 -s 10 -c 10 -t 10

2. The program will print out the value of the options that you provided.
3. The program will then generate the random data and write it to the CSV files.
4. The program will exit.

## Example

The following is an example of the output of the program:

    rows: 100
    u64_count: 10
    f64_count: 10
    string_count: 10
    char_count: 10
    thread_count: 10

The program will then generate 10 CSV files, one for each thread. Each file will contain the random data for the corresponding with option settings.

Sure, here is a section explaining the code:

## Code Explanation

The code is divided into two main functions: `thread_func()` and `generate_data()`.

The `thread_func()` function is the thread function. It is responsible for generating the random data and writing it to a CSV file. The function takes a pointer to a `struct thread_status` as its argument. The `struct thread_status` struct contains the exit code of the thread.

The `generate_data()` function is responsible for creating the threads and waiting for them to exit. The function takes a `struct Options` struct as its argument. The `struct Options` struct contains the options for the program, such as the number of rows of data to generate, the number of uint64_t values to generate per row, and the number of threads to use.

The code also contains the following functions:

* `rand_str()`: This function generates a random string of characters.
* `fix_char()`: This function replaces any characters that can mess with printf format with spaces.