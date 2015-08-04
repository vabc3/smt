#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    setbuf(stdout, NULL);
    printf("Welcome to LOGO\n");
    char line[255];
    while(scanf("%s",line)==1){
        if(strcmp("bye", line)==0) exit(0);
        printf("%s\n",line);
    }
    
    return 0;
}
