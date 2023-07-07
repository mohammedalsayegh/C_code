// Author Name: Mohammed Hashem Alsayegh
//
// This code clones a folder from a remote Git repository into a local directory, using sparse checkout.
//
// The code takes the following command-line arguments:
//
//     --rurl: The URL of the remote Git repository.
//     --branch: The branch of the remote repository to clone.
//     --localdir: The path to the local directory to clone the repository into.
//     --folder: The name of the folder to clone.
//     --distance_folder: The path to the destination folder where the cloned folder will be copied.
//
// For example, to clone the "print_hello_color" folder from the "Rust_code" repository on GitHub into the "tmp/clone" directory and then copy the cloned folder to the current directory, you would run the following command:
//
//    ./git_clone_folder --rurl "https://github.com/mohammedalsayegh/Rust_code" --branch "main" --localdir "./tmp/clone" --folder "print_hello_color" --distance_folder "./"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN_MODE
  #define win_linux_mode_start "bash -c \""
  #define win_linux_mode_end "\""
#else
  #define win_linux_mode_start ""
  #define win_linux_mode_end ""
#endif

struct args {
  char *rurl;
  char *branch;
  char *localdir;
  char *folder;
  char *distance_folder;
};

void git_sparse_clone_folder(char *rurl, char *branch, char *localdir, char *folder, char *distance_folder) {

  // Create the local directory if it doesn't exist
  char command[1024];
  sprintf(command, "%smkdir -p \"%s\"%s", win_linux_mode_start, localdir, win_linux_mode_end);
  system(command);

  // Change to the local directory & Initialize a git repository
  sprintf(command, "%scd \"%s\" && git init && pwd%s", win_linux_mode_start, localdir, win_linux_mode_end);
  printf("\033[32m1: %s\033[0m\n", command);
  system(command);

  // Add the remote repository
  sprintf(command, "%scd \"%s\" && git remote add -f origin \"%s\" && pwd%s", win_linux_mode_start, localdir, rurl, win_linux_mode_end);
  printf("\033[32m2: %s\033[0m\n", command);
  system(command);

  // Enable sparse checkout
  sprintf(command, "%scd \"%s\" && git config core.sparseCheckout true && pwd%s", win_linux_mode_start, localdir, win_linux_mode_end);
  printf("\033[32m3: %s\033[0m\n", command);
  system(command);

  // Add the folder to the sparse-checkout file
  sprintf(command, "%scd \"%s\" && echo \"%s\" > .git/info/sparse-checkout && pwd%s", win_linux_mode_start, localdir, folder, win_linux_mode_end);
  printf("\033[32m4: %s\033[0m\n", command);
  system(command);

  // Pull the master branch from the remote repository
  sprintf(command, "%scd \"%s\" && git pull origin \"%s\" && pwd%s", win_linux_mode_start, localdir, branch, win_linux_mode_end);
  printf("\033[32m5: %s\033[0m\n", command);
  system(command);

  // This command copies the folder from the tmp directory to the destination directory.
  sprintf(command, "%scp -r \"%s/%s\" \"%s\" && pwd%s", win_linux_mode_start, localdir, folder, distance_folder, win_linux_mode_end);
  printf("\033[32m6: %s\033[0m\n", command);
  system(command);

  // This command remove the folder tmp directory
  sprintf(command, "%srm -rv ./tmp && pwd%s", win_linux_mode_start, win_linux_mode_end);
  printf("\033[32m7: %s\033[0m\n", command);
  system(command);
}

int main(int argc, char *argv[]) {
  struct args args;
  int i;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--rurl") == 0) {
      args.rurl = argv[i + 1];
    } else if (strcmp(argv[i], "--branch") == 0) {
      args.branch = argv[i + 1];
    } else if (strcmp(argv[i], "--localdir") == 0) {
      args.localdir = argv[i + 1];
    } else if (strcmp(argv[i], "--folder") == 0) {
      args.folder = argv[i + 1];
    } else if (strcmp(argv[i], "--distance_folder") == 0) {
      args.distance_folder = argv[i + 1];
    }
  }

  // Check to make sure that the user has provided all of the required arguments
  if (args.rurl == NULL || args.branch == NULL || args.localdir == NULL || args.folder == NULL || args.distance_folder == NULL) {
    printf("\033[31mError: Missing required command-line arguments\033[0m\n");
    exit(1);
  }

  git_sparse_clone_folder(args.rurl, args.branch, args.localdir, args.folder, args.distance_folder);

  return 0;
}

// ./git_clone_folder --rurl "https://github.com/mohammedalsayegh/Rust_code" --branch "main" --localdir "./tmp/clone" --folder "print_hello_color" --distance_folder "./"