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

	int i,j,k,l;
    int fp1, fp2;
    double a;
    char input_image1[100],input_image2[100];
    unsigned char image1[1000],image2[1000];

    int npix,nscan,pix,scan,i1,i2;

    double MSE=0;

	//Input Image File
	printf("Give size of image \n");
    scanf("%d%d",&npix,&nscan);

    printf("Give input image name \n");
    scanf("%s",input_image1);

    printf("Give input image name \n");
    scanf("%s",input_image2);

    fp1= open(input_image1,O_RDONLY);

    if (fp1<0)
    {
        printf("Error in opening %s image \n",input_image1);
        exit(1);
    }

    fp2= open(input_image2,O_RDONLY);

    if (fp2<0)
    {
        printf("Error in opening %s image \n",input_image2);
        exit(1);
    }


    for(scan=0;scan<nscan;scan++)
    {
    	read(fp1,&image1[0],npix*sizeof(unsigned char));
    	read(fp2,&image2[0],npix*sizeof(unsigned char));

    	for(pix=0;pix<npix;pix++)
    	{
    		MSE+=((double)image1[pix]-(double)image2[pix])*((double)image1[pix]-(double)image2[pix]);
    	}
    }

    close(fp1);
    close(fp2);


    MSE = MSE/(512*512);


    printf("%f\n",MSE);
    
}