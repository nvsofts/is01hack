#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

#define MODULES_DISABLED_ADDR (0x8059CCCC)
#define SECURITY_OPS_ADDR (0x805C111C)
#define DEFAULT_SECURITY_OPS_ADDR (0x80507508)
#define PROCNAME "modules_enabler"

static int proc_read(char *page, char **start, off_t offset, int count, int *eof, void *data)
{
  *((unsigned int *)(MODULES_DISABLED_ADDR)) = 0;
  printk(KERN_INFO "modules_enabler: Hacked! Have fun!\n");
  
  *eof = 1;
  
  return 0;
}

static int __init modules_enabler_module_init( void )
{
  struct proc_dir_entry *entry;
  
  printk(KERN_INFO "modules_enabler is loaded\n");
  printk(KERN_INFO "modules_enabler v1.10 by NV\n");
  
  entry = create_proc_entry(PROCNAME, 0400, NULL);
  if (entry) {
    entry->read_proc = proc_read;
    entry->owner = THIS_MODULE;
  }
  
  *((unsigned int *)(SECURITY_OPS_ADDR)) = DEFAULT_SECURITY_OPS_ADDR;
  printk(KERN_INFO "modules_enabler: Deckard LSM is disabled now.\n");
  
  return 0;
}

static void __exit modules_enabler_module_exit( void )
{
  remove_proc_entry(PROCNAME, NULL);
  
  printk(KERN_INFO "modules_enabler is removed\n");
}

module_init(modules_enabler_module_init);
module_exit(modules_enabler_module_exit);

MODULE_DESCRIPTION("modules_enabler");
MODULE_LICENSE("BSD");
