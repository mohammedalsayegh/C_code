# Random Data Generator

This program generates random data and writes it to a CSV file.

## Usage

```
random_data_generator -r <rows> -u <u64_count> -f <f64_count> -s <string_count> -c <char_count> -t <thread_count>
```

where:

* `-r` is the number of rows of data to generate.
* `-u` is the number of uint64_t values to generate for each row.
* `-f` is the number of double values to generate for each row.
* `-s` is the number of string values to generate for each row.
* `-c` is the number of char values to generate for each row.

For example, to generate 10 rows of data with 2 uint64_t values, 2 double values, 2 string values, and 2 char values per row, you would run the following command:


random_data_generator -r 10 -u 2 -f 2 -s 2 -c 2


## Output

The program will write the generated data to a CSV file called `output.csv`. The CSV file will contain one row for each row of data that was generated. The columns in the CSV file will be the names of the variables that were generated.