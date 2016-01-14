#include "processMigration.h"
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

void save (void){
cprintf("save called!\n");
cprintf("prc number: %d\n", proc->pid);
cprintf("cpu id: %d\n", cpu->id);
}

void load (void){
cprintf("load called!\n");
}
