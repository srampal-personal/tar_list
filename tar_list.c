/*******
    tar_list.c: Utility to list out all files/ directories contained within a standard 
    Unix/posix tar archive alongwith the timestamps when last modified. 

    Compiled and tested using gcc on ubuntu 14.04 on 64b x86
       Example:  gcc tar_list.c -o tar_list
    Compiled and tested using cc on ubuntu 14.04
       Example:  cc tar_list.c -o tar_list
    Should work with most ANSI C compilers

    Usage: ./tar_list <tar_file>

    Can be used with a .tar file, will not work with other archive file types including 
    compressed archives

    Warns if file name does not end with ".tar" but proceeds anyway

    See also: tar_list_unit_tests.c which contains unit tests and test harness for this utility
********/


#include <stdio.h> 
#include <fcntl.h> 
#include <string.h> 
#include <sys/mman.h> 
#include <stdlib.h>
#include <time.h>

#define TAR_HDR_SIZE  ((unsigned int) 512)
#define MMAP_LENGTH   ((unsigned int) 10000000000)

/* Posix tar header format */
struct tarhdr {
  char name[100];   
  char stuff1[24];
  char size[12];    
  char mtime[12];
  char stuff2[364];
} ;

struct tarhdr *tar;

/* Check if the file name string has a ".tar" extension */
/* Return True if file name does not end in ".tar" */

unsigned file_extension_check(char *input_file) 
{

  char *test_ext;
  unsigned input_name_length = strlen(input_file);

  if (input_name_length >= 4) {
      test_ext = input_file + input_name_length - 4;
      if (strcmp(test_ext, ".tar") != 0) {
          return(1);
      }
  }
  else {
      return(1);
  } 
  return(0);
}


int main(int argc, char **argv){
  
  if (argc < 2) {
      printf("Usage: tar_list <tarfile>\n");
      exit(0);
  }

  int fd=open( argv[1], O_RDONLY );

  if(fd == -1) {
      fprintf(stderr, "Error opening file %s exitting ...\n", argv[1]);
      exit(-1);
  }

  /* Put out a warning if file name does not end with .tar but proceed anyway */
  /* (could potentially add more tar format sanity checks for robustness) */

  if(file_extension_check(argv[1])) {
          printf("Warning: Input file name does not have .tar extension.\n");
          printf("Proceeding anyway ...\n");
  }

  /* Using memory mapped file I/O */ 
  tar=mmap(NULL, MMAP_LENGTH, PROT_READ, MAP_PRIVATE, fd, 0);

  if (tar == MAP_FAILED) {
      fprintf(stderr, "Memory error mapping file exitting ...\n");
      exit(-1);
  }

  long length;
  time_t  epoch_time;
  int i = 0;

  /* Move from file to file, rounding up for each file's last block of 512 bytes */

  while(tar->name[0]) {

    /* get length from octal string */
    length = strtol(tar->size, NULL, 8);

    /* get unix epoch_time converting from octal string */
    epoch_time = strtol(tar->mtime, NULL, 8);

    i++;
    printf("%d) %s  %s", i, tar->name,  ctime(&epoch_time));

    tar+=1+((length+(TAR_HDR_SIZE-1))/TAR_HDR_SIZE) ;
  }

  close(fd);
  exit(0);

}

