#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <float.h>


void main()
{
    int i;
    for(i=0;i<10;i++)
        printf("%f\n",FLT_MIN);
}