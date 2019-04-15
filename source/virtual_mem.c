#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/fs.h>
#include <asm/page.h>

asmlinkage int virtual_mem(int pid){
	//get task_struct of pid
	struct task_struct *process_ts;
	process_ts = pid_task(find_vpid(pid), PIDTYPE_PID); //reused from project1
	if(!process_ts)
	{
		printk(KERN_INFO "could not find process with pid %d",pid); 
		return 1;
	}
	//get memory struct
	struct mm_struct *process_mem = process_ts->active_mm;
	
	//get number of virtual memories
	int num_mem = process_mem->map_count;
	printk(KERN_INFO "\nThe # of virtual memory areas = %d\n", num_mem);
	
	//get list sorted of all virtual memories, this way its easier to traverse.
	struct vm_area_struct *list_virtualmem = process_mem->mmap;
	
	//traverse
	int i = 0;
	unsigned long total = 0;
	struct vm_area_struct *i_vm; //traveler pointer
	for(i_vm = list_virtualmem; i < num_mem; i++)
	{
		printk(KERN_INFO "Virtual memory (%d)\n", i);
		
		//find size of each area
		unsigned long vma_size = i_vm->vm_end - i_vm->vm_start;
		printk(KERN_INFO "Size = (end - start) = %lu - %lu = %lu\n", i_vm->vm_end, i_vm->vm_start, vma_size);	
		total += vma_size;
		
		//determine permissions
		unsigned long permissions = i_vm->vm_flags;
		if(permissions & 1) //read
			printk(KERN_INFO "Read permission = allowed\n");
		else
			printk(KERN_INFO "Read permission = denied\n");
		if(permissions & 2) //write
			printk(KERN_INFO "Write permission = allowed\n");
		else 
			printk(KERN_INFO "Write permission = denied\n");
		if(permissions & 4)
			printk(KERN_INFO "Execute permission = allowed\n");
		else
			printk(KERN_INFO "Execute permission = denied\n");		
		
		//get file name
		if(i_vm->vm_file != NULL)
		{
			char *file_name = d_path(&(i_vm->vm_file->f_path), (char *)__get_free_page(GFP_TEMPORARY), PAGE_SIZE); 
			printk(KERN_INFO "File Name: %s\n",file_name);		
		} 	
		//check bounds
		if(i != num_mem-1)  
			i_vm = i_vm->vm_next;
	}
	printk(KERN_INFO "Total size = %lu\n", total);
	
	return 1;
}
