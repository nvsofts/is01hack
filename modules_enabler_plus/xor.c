#include <stdio.h>
#include <string.h>

void encode(char *ptr, size_t size)
{
  size_t i;

  for (i = 0; i < size; i++) {
    ptr[i] ^= 0x65;
  }
}

int main(void)
{
  size_t i;
  size_t len;
  char buf[1024];
  
  fgets(buf, 1024, stdin);
  
  len = strlen(buf);
  encode(buf, len);
  
  printf("len: %u\n", len);
  for (i = 0; i < len; i++) {
    printf("0x%X ", buf[i]);
  }
  
  return 0;
}
