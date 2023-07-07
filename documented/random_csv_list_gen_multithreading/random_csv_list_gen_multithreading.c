// Author Name: Mohammed Hashem Alsayegh

// This program generates random data alllocated it in the heap for each thread seperatly and writes it to multiple CSV files with each file end with its own thread ID.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

struct RowData {
  uint64_t *u64_values;
  double *f64_values;
  char **string_values;
  char *char_values;
};

struct thread_status {
  /* The exit code of the thread. */
  int exit_code;
};

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
  .rows = 1,
  .u64_count = 1,
  .f64_count = 1,
  .string_count = 1,
  .char_count = 1,
  .thread_count = 1,
};

int get_number_of_cores() {
  /* This function runs the `wmic cpu get NumberOfCores /Format:List` command
   * to get the number of cores. The function then parses the output of the
   * command to extract the number of cores. Finally, the function returns the
   * number of cores.
   */

  char *cmd = "wmic cpu get NumberOfCores /Format:List";
  FILE *fp;
  char buffer[1024];
  int number_of_cores = 0;

  /* Open the command pipe. */

  fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    return 1;
  }

  /* Read the output of the command one line at a time. */

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    /* Look for the line that contains the number of cores. */
    char *match = strstr(buffer, "NumberOfCores=");
    if (match != NULL) {
      /* Extract the number of cores from the line. */
      match += strlen("NumberOfCores=");
      number_of_cores = atoi(match);
      break;
    }
  }

  /* Close the command pipe. */

  pclose(fp);

  /* Return the number of cores. */

  return number_of_cores;
}

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
char fix_char(char c) {
  /* Create a list of characters that can mess with printf format. */
  const char bad_characters[] = "%$#@()<>{}|;:,\"'\\";

  /* Check if the character is a bad character. */
  bool is_bad_character = false;
  for (int i = 0; bad_characters[i] != '\0'; i++) {
    if (c == bad_characters[i]) {
      is_bad_character = true;
      break;
    }
  }

  /* If the character is a bad character, then return a space. */
  if (is_bad_character) {
    return ' ';
  } else if (c == '"') {
    return ' ';
  } else {
    return c;
  }
}

/*
 * This function is the thread function.
 * It sets the exit code of the thread to 10 and then calls `pthread_exit()`.
 */
void *thread_func(void *arg) {
  /* Get the status of the thread. */
  struct thread_status *status = arg;

  pthread_t thread_id = pthread_self();
  printf("Thread %lu is running...\n", thread_id);

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
      char c = rand() % 256;
      rows[i].char_values[j] = fix_char(c);
    }
  }

  // Use sprintf to create a template for the file name
  char filename[100];
  sprintf(filename, "output_%lu.csv", thread_id);

  // Open the CSV file.
  FILE *fp = fopen(filename, "w+");

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
      fprintf(fp, "\"%c \", ", rows[i].char_values[j]);
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

  /* Set the exit code of the thread. */
  status->exit_code = 10;

  /* Exit the thread. */
  pthread_exit(status);
}

void generate_data(struct Options options) {
  /* The number of threads to create. */
  int num_threads = options.thread_count;

  /* The array of thread statuses. */
  struct thread_status status[num_threads];

  /* The array of thread IDs. */
  pthread_t threads[num_threads];

  /* Create the threads. */
  for (int i = 0; i < num_threads; i++) {
    pthread_create(&threads[i], NULL, thread_func, &status[i]);
  }

  /* Wait for the threads to exit. */
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Print out the status values of the threads. */
  for (int i = 0; i < num_threads; i++) {
    printf("Thread %d exited with status %d\n", i, status[i].exit_code);
  }

  /* Execute the coopy all csv files into single file command line. */
  system("copy /y /b output_*.csv output.csv");

  /* Execute delete files that were generated command line. */
  system("dir .\\output_*.csv");
  system("del .\\output_*.csv");
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
  assert(options.rows >= 0 && options.rows <= UINT32_MAX);
  assert(options.u64_count >= 0 && options.u64_count <= UINT32_MAX);
  assert(options.f64_count >= 0 && options.f64_count <= UINT32_MAX);
  assert(options.string_count >= 0 && options.string_count <= UINT32_MAX);
  assert(options.char_count >= 0 && options.char_count <= UINT32_MAX);
  assert(options.thread_count > 0 && options.thread_count <= get_number_of_cores());

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
