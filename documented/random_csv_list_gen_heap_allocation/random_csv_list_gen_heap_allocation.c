// Name: Mohammed Hashem Alsayegh

// This program generates random data and writes it to a CSV file.

// The `rand_str()` function generates a random string of characters.
// This function uses the `char charset[]` array to generate a random string of characters.
// The `fix_char()` function replaces any characters that can mess with printf format with spaces.
// This function uses the `const char *bad_characters` string to find any characters that need to be replaced.
// The `struct Options` struct stores the options for the program.
// This struct has six fields: rows, u64_count, f64_count, string_count, char_count, and thread_count.
// The `generate_data()` function generates the random data and writes it to the CSV file.
// This function iterates over the rows and generates random data for each row.
// The `main()` function parses the command-line arguments, checks the validity of the arguments, prints out the value of options, and calls `generate_data()`.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

// This function generates a random string of characters.
// The `char charset[]` array is used to generate a random string of characters.
char *rand_str(char *str, int len) {
  char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int rand_num;

  for (int i = 0; i < len; i++) {
    rand_num = rand() % (sizeof(charset) - 1);
    str[i] = charset[rand_num];
  }

  str[len] = '\0';
  return str;
}

// This function replaces any characters that can mess with printf format with spaces.
// The `const char *bad_characters` string is used to find any characters that need to be replaced.
void fix_char(char *c) {
  /* Create a regular expression that matches any characters that can mess with
   * printf format. */
  const char *bad_characters = "%$#@()<>{}|;:\"'\\\\";

  /* Replace all of the bad characters with spaces. */
  for (int i = 0; c[i] != '\0'; i++) {
    if (strchr(bad_characters, c[i]) != NULL) {
      c[i] = ' ';
    } else if (c[i] == '\'') {
      c[i] = '\\';
      c[i + 1] = '\'';
      i++;
    }
  }
}

// This struct stores the options for the program.
struct Options {
  int rows;
  int u64_count;
  int f64_count;
  int string_count;
  int char_count;
  int thread_count;
};

struct Options options = {
  .rows = 10,
  .u64_count = 2,
  .f64_count = 2,
  .string_count = 2,
  .char_count = 2,
  .thread_count = 2,
};

struct RowData {
  uint64_t *u64_values;
  double *f64_values;
  char **string_values;
  char *char_values;
};

void generate_data(struct Options options) {
  // Allocate memory for all rows of data.
  struct RowData *rows = malloc(sizeof(struct RowData) * options.rows);

  // Iterate over all rows of data.
  for (int i = 0; i < options.rows; i++) {
    // Allocate memory for the u64_values array in the current row.
    rows[i].u64_values = malloc(sizeof(uint64_t) * options.u64_count);

    // Allocate memory for the f64_values array in the current row.
    rows[i].f64_values = malloc(sizeof(double) * options.f64_count);

    // Allocate memory for the string_values array in the current row.
    rows[i].string_values = malloc(sizeof(char *) * options.string_count);

    // Allocate memory for the char_values array in the current row.
    rows[i].char_values = malloc(sizeof(char) * options.char_count);

    // Generate random data for the current row and store it in the corresponding arrays.
    for (int j = 0; j < options.u64_count; j++) {
      rows[i].u64_values[j] = rand();
    }

    for (int j = 0; j < options.f64_count; j++) {
      rows[i].f64_values[j] = (double) rand() / RAND_MAX;
    }

    for (int j = 0; j < options.string_count; j++) {
      rows[i].string_values[j] = malloc(20);
      rand_str(rows[i].string_values[j], 20);
    }

    for (int j = 0; j < options.char_count; j++) {
      rows[i].char_values[j] = rand() % 256;
      fix_char(&rows[i].char_values[j]);
    }
  }

  // Open the CSV file.
  FILE *fp = fopen("output.csv", "a");

  // Write the data for all rows to the CSV file.
  for (int i = 0; i < options.rows; i++) {
    for (int j = 0; j < options.u64_count; j++) {
      fprintf(fp, "\"%d\", ", rows[i].u64_values[j]);
    }

    for (int j = 0; j < options.f64_count; j++) {
      fprintf(fp, "\"%f\", ", rows[i].f64_values[j]);
    }

    for (int j = 0; j < options.string_count; j++) {
      fprintf(fp, "\"%s\", ", rows[i].string_values[j]);
    }

    for (int j = 0; j < options.char_count; j++) {
      fprintf(fp, "\"%c\", ", rows[i].char_values[j]);
    }
    fprintf(fp, "\n");

    // Free the memory that was allocated for the current row.
    free(rows[i].u64_values);
    free(rows[i].f64_values);
    for (int j = 0; j < options.string_count; j++) {
      free(rows[i].string_values[j]);
    }
    free(rows[i].string_values);
    free(rows[i].char_values);
  }

  // Free the memory that was allocated for all rows.
  free(rows);

  // Close the CSV file.
  fclose(fp);
}

int main(int argc, char *argv[]) {

  // Parse the command-line arguments.
  int i;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {
      options.rows = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-u") == 0) {
      options.u64_count = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-f") == 0) {
      options.f64_count = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-s") == 0) {
      options.string_count = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-c") == 0) {
      options.char_count = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-t") == 0) {
      options.thread_count = atoi(argv[++i]);
    }
  }

  // Check to make sure that the user has provided valid command-line arguments.
  assert(options.rows > 0 && options.rows <= UINT32_MAX);
  assert(options.u64_count > 0 && options.u64_count <= UINT32_MAX);
  assert(options.f64_count > 0 && options.f64_count <= UINT32_MAX);
  assert(options.string_count > 0 && options.string_count <= UINT32_MAX);
  assert(options.char_count > 0 && options.char_count <= UINT32_MAX);
  assert(options.thread_count > 0 && options.thread_count <= UINT32_MAX);

  // Print out the value of options.
  printf("rows: %d\n", options.rows);
  printf("u64_count: %d\n", options.u64_count);
  printf("f64_count: %d\n", options.f64_count);
  printf("string_count: %d\n", options.string_count);
  printf("char_count: %d\n", options.char_count);
  printf("thread_count: %d\n", options.thread_count);

  generate_data(options);

  return 0;
}