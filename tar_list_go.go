package main

import (
  "fmt"
  "os"
  "unsafe"
  "syscall"
  "strconv"
  "time"
)

/* Posix tar header format */
type tarhdr struct {

  name       [100]uint8
  stuff1     [24]uint8
  size       [12]uint8    
  mtime      [12]uint8
  stuff2     [364]uint8
 
}

var tar *tarhdr 

func main() {

  if len(os.Args) < 2 {
      fmt.Printf("Usage tar_list_go <tar_file>\n")
      return
  }

/*
  tar_file, err := os.Open("./unit_tests/a.tar")
*/
  tar_file, err := os.Open(os.Args[1])

  if err != nil {
      fmt.Printf("Error opening file %s exitting ...\n", os.Args[1])
      return
  }
  defer tar_file.Close()

  stat, err := tar_file.Stat()
  if err != nil {
    fmt.Println(err)
    return
  }


/*
  fmt.Printf("Opened file of size %d \n", int(stat.Size()))  
*/

  mmap, err := syscall.Mmap(int(tar_file.Fd()), 0, int(stat.Size()), syscall.PROT_READ, syscall.MAP_SHARED)
  if err != nil {
    fmt.Println(err)
    return
  }

  tar = (*tarhdr)(unsafe.Pointer(&mmap[0]))

  var i            uint32
  var hdrOffset    uint64

  hdrOffset = 0

  for i=1; tar.name[0] != 0; i++ {

      length, _ := strconv.ParseUint(string(tar.size[0:11]), 8, 64)

      epoch_time, _ := strconv.ParseUint(string(tar.mtime[0:11]), 8, 64)

/*      fmt.Printf("%d) %s length %d\n", i, tar.name, length) */

      fmt.Printf("%d) %s time stamp %s\n", i, tar.name, time.Unix(int64(epoch_time), 0))

      hdrOffset = hdrOffset + (uint64(1+((length+(512-1))/512))) 

      tar = (*tarhdr)(unsafe.Pointer(&mmap[hdrOffset*512]))

  }

}

