/*
	Name	:	pipcd.c
	Created	:	Tue Aug  4 20:37:17 CST 2015
	Author	:	Karata Liu, vabc3h@gmail.com
	
	
	Pix buffer:
	Each byte represent 8 verical pixel line, 1 for non-transpancy.
	So the figure is described with 84 * (48 / 8) = 504 bytes.
*/

#include <stdio.h>
#include "wiringPi.h"
#include "PCD8544.h"
#include "pipcd.h"
#include "font.c"

// pin setup
static int sclk 	= 0;
static int din 		= 1;
static int dc 		= 2;
static int cs 		= 3;
static int rst 		= 4;
static int contrast = 45;

extern uint8_t pcd8544_buffer[];
static inline int char_get_uni(const char *a);

int PipcdInit(){
	// check wiringPi setup
	if (wiringPiSetup()==-1) return -1;
	
	// init and clear lcd
	LCDInit(sclk, din, dc, cs, rst, contrast);
	LCDclear();
	LCDdisplay();
	
	return 0;
}

void PipcdShow(const uint8_t data[]){
	uint32_t i;
	for (i = 0; i < LCDWIDTH * LCDHEIGHT / 8; i++  )
	{
		pcd8544_buffer[i] = data[i];
	}
}

// 84 , 48  16 x 16 -> 5 x 3

void PipcdDraw(const uint8_t data[], int x, int y){
	uint8_t i,j;
	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
			int p2 = i*16 + j;
			int p1 = p2 + i * (84-16);
			p1 += 16 * x + 84 * 2 * y;
			pcd8544_buffer[p1] = data[p2];
		}
	}
}

void PipcdRefresh(){
	LCDdisplay();
}

void PipcdClear()
{
	LCDclear();
	LCDdisplay();
}

void PipcdLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	LCDdrawline(x0, y0, x1, y1, 1);
	PipcdRefresh();
}

static inline int char_get_uni(const char *a) {
	if ((*a) & 0x80)
		return ((((*a << 4) & 0xf0) | (*(a + 1) >> 2 & 0x0f)) << 8)
			| (((*(a + 1) << 6) & 0xc0) | (*(a + 2) & 0x3f));
	else
		return (*a);
}

void PipcdDrawChar(const char* ch, int x, int y){
	PipcdDraw(font+char_get_uni(ch)*32, x, y);
	PipcdRefresh();
}


void PipcdDrawString(const char* ch){
	LCDclear();
	char* p = ch;
	int idx = 0;
	while(*p && idx < 15){
		//printf("p=%d,idx=%d\n",p,idx);
		PipcdDrawChar(p,  idx % 5, idx / 5);
		if((*p)&0x80)p+=2;
		idx++;p++;
	}
	
	PipcdRefresh();
	printf("Done\n");
}