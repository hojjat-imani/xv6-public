#include "types.h"
#include "user.h"
#include "fcntl.h"

int main (){
int i = 1;

while(1){

	printf(1, "%d\n", i);
	if(i == 1){
		pause(open("procFile", O_CREATE|O_RDWR));
	}
	if(i == 3){
		resume(open("procFile", O_RDONLY));
	}
	sleep(100);
	i++;
}

exit();
}
