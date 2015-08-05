#include <stdio.h>
#include "pipcd.h"

int main(){
	PipcdInit();
	setbuf(stdout, NULL);
	
	char dat[255];
	
	while(fgets(dat,255,stdin)){
		PipcdDrawString(dat);
	}	
	
	return 0;
}
