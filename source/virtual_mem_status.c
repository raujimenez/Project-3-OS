#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <asm/pgtable.h>
#include <asm/page.h>

asmlinkage int virtual_mem_status(unsigned long v_mem, int pid)
{
	//get task_struct
	struct task_struct *task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if(!task)
	{
		printk(KERN_INFO "could not find process with pid %d\n",pid);
		return 0;
	}	
	//get memory struct
	struct mm_struct *process_mem = task->active_mm;
	
	//get memory offset through "walking"
	pgd_t *global = pgd_offset(process_mem, v_mem);
	pud_t *upper = pud_offset(global, v_mem);
	pmd_t *middle = pmd_offset(upper, v_mem);
	pte_t *ptep = pte_offset_kernel(middle, v_mem);
	
	//check flags
	if(pte_present(*ptep))
		printk(KERN_INFO "PRESENT IN MEMORY\n");
	else
		printk(KERN_INFO "NOT PRESENT IN MEMORY, ON DISK\n");
	if(pte_young(*ptep))
		printk(KERN_INFO "REFERENCED\n");
	else
		printk(KERN_INFO "NOT REFERENCED\n");
	if(pte_dirty(*ptep))
		printk(KERN_INFO "DIRTY\n");
	else
		printk(KERN_INFO "NOT DIRTY\n");
	return 0;
}
