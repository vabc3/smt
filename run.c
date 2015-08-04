#include <stdint.h>
#include "pipcd.h"
#include "zbd.h"

int main (){
	PipcdInit();
	PipcdShow(zbd);
	//PipcdClear();
	return 0;
}
