#ifndef _MEM_H_
#define _MEM_H_

#define PAGE_SIZE	4096
#define MEM_DESC_SIZE	4800

void dump_memmap(void);
void init_memmap(void);
struct EFI_MEMORY_DESCRIPTOR *get_allocatable_area(unsigned long long size);
void exit_boot_services(void *IH);

#endif
