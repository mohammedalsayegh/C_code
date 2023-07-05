# Random Data Generator

This program generates random data and writes it to a CSV file.

## Usage

./random_data_generator -r <number of rows> -u <number of u64 values> -f <number of f64 values> -s <number of string values> -c <number of char values>


For example, to generate 100 rows of data with 10 u64 values, 10 f64 values, 10 string values, and 10 char values, you would run the following command:

```
./random_data_generator -r 100 -u 10 -f 10 -s 10 -c 10

```

## Output

The output of the program is a CSV file with the following columns:

* u64_values
* f64_values
* string_values
* char_values

## Notes

* The number of rows, u64 values, f64 values, string values, and char values must be greater than 0.
* The maximum value for each of the number of rows, u64 values, f64 values, string values, and char values is UINT32_MAX (4294967295).