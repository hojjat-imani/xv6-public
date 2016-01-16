#include "types.h"
#include "user.h"
#include "fcntl.h"

int main (){
  int pid, i;

  pid = fork();
  if(pid == 0){

	for(i=0; i<100; i++){
		printf(1, "%d\n", i);
		if(i == 2){
			pause(open("procFile", O_CREATE|O_RDWR));
			exit();
		}
		sleep(100);
	}	
  } else if(pid > 0){  	
	wait();
	resume(open("procFile", O_RDONLY));
	wait();
	exit();
  } else {
    printf(1, "fork() failed\n");
    exit();
  }

exit();
}
