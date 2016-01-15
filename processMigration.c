#include "processMigration.h"
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

char buf[12];

void save(int fd) {
//cprintf("prc number: %d\n", proc->pid);
//cprintf("cpu id: %d\n", cpu->id);
    cprintf("saving (file descriptor: %d)\n", fd);
    mWrite(fd, "process data", 12);
    mClose(fd);
    cprintf("\nend of save.\n");
}

void load(int fd) {
    cprintf("loading (file descriptor: %d)\n", fd);
    mRead(fd, buf, 12);
    cprintf("%s", &buf);
    mClose(fd);
    cprintf("\nend of load.\n");
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