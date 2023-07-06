// Author Name: Mohammed Hashem Alsayegh

/**
 * get_number_of_cores.c
 *
 * This function returns the number of cores on the system.
 *
 * @return The number of cores on the system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main() {
  int number_of_cores = get_number_of_cores();
  printf("Number of cores: %d\n", number_of_cores);
  return 0;
}
