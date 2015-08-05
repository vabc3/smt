#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pipcd.h"

#define N 256
#define SFX(t) ((t+42)%84)
#define SFY(t) ((24-t)%48)

static int x = 0, y = 0, angle = 90, d = 1;
static double ang = M_PI_2;

void show();

int main()
{
    int ox, oy;
    PipcdInit();

    setbuf(stdout, NULL);
    printf("Welcome to LOGO\n");
    char line[N];
    while(fgets(line, N, stdin)){
        char cmd;
        int v = 0;
        sscanf(line, "%c %d", &cmd, &v);
        
        switch(cmd){
            case 'q'    : exit(0);
            case 'f'    :
                ox = x; oy = y;
                x += v * cos(ang); 
                y += v * sin(ang);
                if(d) PipcdLine(SFX(ox), SFY(oy), SFX(x), SFY(y));
                break;
            case 'r'    : 
                angle = (angle - v) % 360;
                ang = (angle / 180.0 * M_PI);
                break;
            case 'd'    : d = 1; break;
            case 'u'    : d = 0; break;
        }
        
        show();
    }

    return 0;
}

inline void show(){
    // 84, 48 | 0,0=>42,24
    printf("[%d, %d] Angle:%d\tDown:%d\n", x, y, angle, d);
    printf("{%d %d}\n", SFX(x), SFY(y));
}

