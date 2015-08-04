#include "pipcd.h"
#include "font.c"

int main(){
	PipcdInit();
	
	PipcdDraw(font+0x597d*32);
	PipcdRefresh();
	
	return 0;
}
