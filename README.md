# Project 3 for Operating Systems (CSE 3320)
This project was to test our understanding of VBA in the Linux kernel and how they relate to processes. \
This project will print out all page table information about a process. \
It will also display the status of the page table (referenced, dirty, etc) and display permissions and display file location. 

# Structure of file
We provided all modified files made to the linux kernel. These modified files are stored in the source folder.
Additionally I wrote some tests for the system calls that were added in identifying page tables and process memory.

# Applying the patch
  - Download a Fresh copy of the [2.6.32 linux kernel](https://mirrors.edge.kernel.org/pub/linux/kernel/v2.6/)
  - Extract the Linux kernel 
  - apply the linux kernel patch by issuing the following command from the LINUX_HEAD directory:
    - `patch -p1 < /path/to/patch3`
  - [Recompile](https://medium.freecodecamp.org/building-and-installing-the-latest-linux-kernel-from-source-6d8df5345980) the kernel
  - Reboot Machine and test out the new system calls
  
# What we learned
Please open project3_report.docx for a better and more detailed report.
