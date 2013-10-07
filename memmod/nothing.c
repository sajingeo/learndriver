#include "nothing.h"

int memory_init(void)
{
int result;

result = register_chrdev(memory_major, "memory", &memory_fops);
if(result <0) {
   printk ("<1>memory :cannot obtain number%d\n",memory_major);
   return  result;
}

memory_buffer = kmalloc(5, GFP_KERNEL);
if (!memory_buffer)
{
result = -ENOMEM;
goto fail;
}
memset (memory_buffer, 0 , 5);

printk("<1>Inserting memory module \n");
return 0;

fail:
memory_exit();
return result;
}

void memory_exit(void)
{
unregister_chrdev(memory_major, "memory");

if(memory_buffer)
{
kfree(memory_buffer);
printk("<1> Removing memory module \n");
}
}

int memory_open(struct inode *inode,struct file *filp)
{
return 0;
}

int memory_release(struct inode *inode,struct file *filp)
{
return 0;
}

ssize_t memory_read(struct file *filp,char * buf,size_t count, loff_t *f_pos)
{
printk("buffer:%s",memory_buffer);
printk("<1>writeing %d %d",count,*f_pos);
copy_to_user(buf,memory_buffer,5);

  if (*f_pos < 5) { 
    *f_pos+=1; 
    return 1; 
  } else { 
    return 0; 
  }
}

ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
  if(count == 2)
{
  printk("<1> copying %d %s",count,memory_buffer);
  copy_from_user(memory_buffer,buf,3);
}
  return 1;
}


