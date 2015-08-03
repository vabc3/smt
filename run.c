#include "wiringPi.h"
#include "PCD8544.h"
#include "zbd.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;
int contrast = 45;

int main ()
{
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
    printf("wiringPi Error\n");
    exit(1);
  }
  
  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();

  //LCDshowLogo();
  LoadBuf(zbd);
  delay(1000);
  LCDclear();
  LCDdisplay();

  return 0;
}
