#include "types.h"
#include "user.h"

int main (){
int i = 1;

while(1){

	printf(1, "%d\n", i);
	if(i == 2){
		pause();
	}
	if(i == 3){
		resume();
	}
	sleep(100);
	i++;
}

exit();
}
