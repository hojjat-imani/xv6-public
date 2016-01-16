#include "processMigration.h"
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

char buf[PGSIZE];
struct proc *process;

void save(int fd) {
    cprintf("saving (file descriptor: %d)\n", fd);
    mWrite(fd, proc, sizeof(struct proc));
    int i;
    for(i=0; i < proc->sz; i+=PGSIZE){
	char *data = getPgData(proc->pgdir, i);
        cprintf("%s\n", data);
	mWrite(fd, data, PGSIZE);
    }
    mClose(fd);
    cprintf("end of save.\n");
}

void load(int fd) {
    cprintf("loading (file descriptor: %d)\n", fd);
    mRead(fd, process, sizeof(struct proc));
    cprintf("%s\n", process->name);
    
    int i;
    for(i=0; i<process->sz; i+=PGSIZE){
	mRead(fd, buf, PGSIZE);
	cprintf("%s\n", buf);
    }
    
    mClose(fd);
    cprintf("end of load.\n");
}

int mWrite(int fd, void *addr, int n) {
    struct file *f;
    if (fd < 0 || fd >= NOFILE) {
        cprintf("mWrite error 1");
        return -1;
    }
    if ((f = proc->ofile[fd]) == 0) {
        cprintf("mWrite error 2");
        return -1;
    }
    return filewrite(f, addr, n);
}

int mRead(int fd, void* addr, int n){
    struct file *f;
    if (fd < 0 || fd >= NOFILE) {
        cprintf("mRead error 1");
        return -1;
    }
    if ((f = proc->ofile[fd]) == 0) {
        cprintf("mRead error 2");
        return -1;
    }
    return fileread(f, addr, n);
}

int mClose(int fd){
    struct file *f;
    if (fd < 0 || fd >= NOFILE) {
        cprintf("mClose error 1");
        return -1;
    }
    if ((f = proc->ofile[fd]) == 0) {
        cprintf("mClose error 2");
        return -1;
    }
    proc->ofile[fd] = 0;
    fileclose(f);
    return 0;
}
