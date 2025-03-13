#include <mem.h>
#include <common.h>
#include <efi.h>
#include <fbcon.h>

unsigned char mem_desc[MEM_DESC_SIZE];
unsigned long long mem_desc_num;
unsigned long long mem_desc_unit_size;
unsigned long long map_key;

void dump_memmap(void* ptr)
{
    putc('d');
    puth(mem_desc_num, 16);
	struct EFI_MEMORY_DESCRIPTOR *p = (struct EFI_MEMORY_DESCRIPTOR *)ptr;
	unsigned int i;

	for (i = 0; i < mem_desc_num; i++) {
		puth((unsigned long long)p, 16);
		putc(' ');
		puth(p->Type, 2);
		putc(' ');
		puth(p->PhysicalStart, 16);
		putc(' ');
		puth(p->VirtualStart, 16);
		putc(' ');
		puth(p->NumberOfPages, 16);
		putc(' ');
		puth(p->Attribute, 16);
		puts("\r\n");

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + mem_desc_unit_size);
	}
}

struct EFI_MEMORY_DESCRIPTOR *get_allocatable_area(unsigned long long size)
{
	struct EFI_MEMORY_DESCRIPTOR *p =
		(struct EFI_MEMORY_DESCRIPTOR *)mem_desc;
	unsigned long long i;

	for (i = 0; i < mem_desc_num; i++) {
		if ((p->Type == EfiConventionalMemory) &&
		    ((p->NumberOfPages * PAGE_SIZE) >= size))
			break;

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + mem_desc_unit_size);
	}

	return p;
}
