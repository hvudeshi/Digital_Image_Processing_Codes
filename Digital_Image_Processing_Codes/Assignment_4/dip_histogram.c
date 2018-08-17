/*
	Author: Hardik Udeshi
	Description: Take any image as your input. Calculate its histogram and display it on GNU Plot.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>
void main()
{
	//input variables
	char output_file[100],input_file[100];
	unsigned char *image;
	int *image_out;
	int pix,npix,scan,nscan, *fp1,midx,midy,npix_out,nscan_out;

	//File pointer
	FILE *fp2;

	//npix and nscan
	printf("Give npix nscan \n");
	scanf("%d %d",&npix,&nscan);

	//input image array
	image = (unsigned char *)calloc(npix,sizeof(unsigned char));

	//input file
	printf("Give me input file \n");
	scanf("%s",input_file);

	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);
	float x,y,r;

	//size of output npix and nscan
	npix_out = npix;
	nscan_out = nscan;

	//output int image array
	image_out = (int *)calloc(256,sizeof(int));

	memset(image_out,0,256*sizeof(int));

	//opening the input file
	fp1=open(input_file,O_RDONLY);

	if(fp1<0)
	{
		printf("Error in Opening the File.\n");
		exit(1);
	}

	//opening the output file with write mode
	fp2 = fopen(output_file,"w");

	if(fp2<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}

	//for loop for no. of rows
	for(scan=0;scan<nscan;scan++)
	{
		//reading the input file
		read(fp1,&image[0],npix*sizeof(unsigned char));

		//for loop for no. of cols
		for(pix=0;pix<npix;pix++)
		{
			//hashing
			image_out[(int)image[pix]]++;
		}
		
	}

	//for loop for printing into the file
	for(scan=0;scan<256;scan++)
	{
		fprintf(fp2, "%d %d\n",scan,image_out[scan]);
	}

	//closing the files
	close(fp1);
	close(fp2);


}
