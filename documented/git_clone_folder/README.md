# GIT Clone Folder
This code clones a folder from a remote Git repository into a local directory, using sparse checkout. The code takes the following command-line arguments:

* --rurl: The URL of the remote Git repository.
* --branch: The branch of the remote repository to clone.
* --localdir: The path to the local directory to clone the repository into.
* --folder: The name of the folder to clone.
* --distance_folder: The path to the destination folder where the cloned folder will be copied.

For example, to clone the "print_hello_color" folder from the "Rust_code" repository on GitHub into the "tmp/clone" directory and then copy the cloned folder to the current directory, you would run the following command:

```
./git_clone_folder --rurl "https://github.com/mohammedalsayegh/Rust_code" --branch "main" --localdir "./tmp/clone" --folder "print_hello_color" --distance_folder "./"
```

# instructions  
to compile for linux:
```
gcc git_clone_folder.c -o git_clone_folder
```
and to compile for windwos:
```
gcc git_clone_folder.c -o git_clone_folder -DWIN_MODE
```