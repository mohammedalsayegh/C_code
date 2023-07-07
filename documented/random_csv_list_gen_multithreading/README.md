# Random Data Generator

This program generates random data and writes it to multiple CSV files. The data is allocated in the heap for each thread separately and the CSV files are named as output_<thread_id>.csv.

## Usage

To run the program, you need to provide the following command-line arguments:

* `-r` The number of rows of data to generate.
* `-u` The number of uint64_t values to generate in each row.
* `-f` The number of double values to generate in each row.
* `-s` The number of string values to generate in each row.
* `-c` The number of char values to generate in each row.
* `-t` The number of threads to use.

For example, to generate 100 rows of data with 10 uint64_t values, 10 double values, 10 string values, and 10 char values in each row using 4 threads, you would run the following command:

```
./random_data_generator -r 100 -u 10 -f 10 -s 10 -c 10 -t 4
```

## Output

The program will generate the following output:

* The value of the options struct.
* The number of rows, uint64_t values, double values, string values, and char values that were generated.
* The CSV files containing the generated data.

## Notes

* The program uses the `get_number_of_cores()` function to determine the number of threads to use. If the number of threads is greater than the number of cores, then the program will use the number of cores.
* The program allocates memory for the data in the heap for each thread separately. This means that the data will not be shared between threads.
* The program writes the data to CSV files. The CSV files are named as output_<thread_id>.csv.

## Code Explanation

The code is divided into the following sections:

* **Parsing the command-line arguments:** The `main()` function parses the command-line arguments and stores the values in the `options` struct.
* **Checking the validity of the command-line arguments:** The `main()` function checks to make sure that the user has provided valid command-line arguments.
* **Generating the data:** The `generate_data()` function generates the data and writes it to multiple CSV files.
* **The thread function:** The `thread_func()` function is the thread function. It allocates memory for the data in the heap for the current thread and then writes the data to a CSV file.
* **The rand_str()` function:** The `rand_str()` function generates a random string of characters.
* **The fix_char()` function:** The `fix_char()` function replaces any characters that can mess with printf format with spaces.