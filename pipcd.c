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

// pin setup
static int sclk 	= 0;
static int din 		= 1;
static int dc 		= 2;
static int cs 		= 3;
static int rst 		= 4;
static int contrast = 45;

extern uint8_t pcd8544_buffer[];

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
	
	LCDdisplay();
}

void PipcdClear()
{
	LCDclear();
	LCDdisplay();
}
