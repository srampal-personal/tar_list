# tar_list
Exercise in C programming. List files and timestamps within a [unix tar archive][1] without using standard utilities like 'tar'

### Repo contents

* tar_list.c:
 
    Utility to list out all files/ directories contained within a standard 
    Unix/posix tar archive alongwith the timestamps when last modified. 

    Compiled and tested using gcc and cc  on ubuntu 14.04 and a .tar file
       Example:  gcc tar_list.c -o tar_list
       Example:  cc tar_list.c -o tar_list
    Should work with most ANSI C compilers

    Usage: ./tar_list <tar_file>

    Can be used with a .tar file, will not work with other archive file types including 
    compressed archives

    Warns if file name does not end with ".tar" but proceeds anyway

    Example output generated for test input file ./unit_tests/a.tar is in ./unit_tests/test1_output.txt

* tar_list:
 
   Linux 64b x86 executable binary for tar_list.c. Note: for other targets/ platforms, you will need to compile/ cross-compile and generate the executable binary for the desired target platform 

* tar_list_unit_tests.c:

    Unit tests for tar_list utility. Tests tar_list output for known tar files and other positive and negative test cases. Uses a simple test harness framework. Assumes name of main utility is tar_list.  
    
* tar_list_unit_tests:
 
    Linux 64b x86 executable binary unit test harness. Example usage

user@ubuntu:~/tar_list$ ./tar_list_unit_tests  
All Tests Passed  
Tests run: 3

* unit_tests:
 
    Directory containing supporting files for unit tests
 

 [1]: https://en.wikipedia.org/wiki/Tar_%28computing%29 

