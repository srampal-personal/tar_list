# tar_list
Exercise in C programming; listing files within a unix tar archive without using standard utilities like 'tar'

    tar_list.c: Utility to list out all files/ directories contained within a standard 
    Unix/posix tar archive alongwith the timestamps when last modified. 

    Compiled and tested using gcc on ubuntu 14.04 and a .tar file
       Example:  gcc tar_list.c -o tar_list
    Compiled and tested using cc on ubuntu 14.04
       Example:  cc tar_list.c -o tar_list
    Should work with most ANSI C compilers

    Can be used with a .tar file, will not work with other archive file types including 
    compressed archives

    Warns if file name does not end with ".tar" but proceeds anyway

