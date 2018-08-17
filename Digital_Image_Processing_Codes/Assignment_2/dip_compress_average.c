/*
	Author: Hardik Udeshi
	Description: Reduce the image dimensions. Take any image as your input, also take in the image
				size as your input. Ask the user by what factor they want to reduce the image
				dimensions. Note that this factor will be an integer. You may achieve this by averaging
				over pixels.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

void main()
{
	//input variables
	char input_file[100],output_file[100];
	//unsigned char ** image,**image_out;
	int pix,npix,scan,nscan, npix_out,nscan_out,*fp1,*fp2,cnt,temp,x,y,k,l,i,x0,y0,xx,yy,sum=0;
	float compress;
	double rads;

	//npix and nscan
	printf("Give npix nscan \n");
	scanf("%d %d",&npix,&nscan);

	//input file
	printf("Give me input file \n");
	scanf("%s",input_file);
	printf("input file is %s\n",input_file);

	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);

	//compression factor
	printf("Compression factor:\n");
	scanf("%f",&compress);

	
	//new size of npix and nscan for new image
	npix_out = npix/compress;
	nscan_out = nscan/compress;


	printf("%d %d",npix_out,nscan_out);

	//input image array
	unsigned char **image = (unsigned char **)malloc(nscan * sizeof(unsigned char *));
    for (scan=0; scan<nscan; scan++)
         image[scan] = (unsigned char *)malloc(npix * sizeof(unsigned char));

     //output image array
    unsigned char **image_out = (unsigned char **)malloc(nscan_out * sizeof(unsigned char *));
    for (scan=0; scan<nscan_out; scan++)
         image_out[scan] = (unsigned char *)malloc(npix_out * sizeof(unsigned char));

	// *image = (unsigned char *)malloc(npix*nscan*sizeof(unsigned char));
	// *image_out = (unsigned char *)malloc(npix_out*nscan_out*sizeof(unsigned char));

     //initializing output image array
	for(scan=0;scan<nscan_out;scan++)
	{
		for(pix=0;pix<npix_out;pix++)
		{
			image_out[scan][pix]=255;
		}
	}



	
	//opening the input file
	fp1 = open(input_file,O_RDONLY);
	if(fp1<0)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	//reading the file
	for(scan=0;scan<nscan;scan++)
	{
		read(fp1,&image[scan][0],npix*sizeof(unsigned char));
	}

	//closing file
	close(fp1);

	//creating output file
	fp2 = creat(output_file,0666);

	if(fp2<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}	

	//for loop for rows of an image
	for(scan=0;scan<nscan_out;scan++)
	{
		//for loop for columns of an image
		for(pix=0;pix<npix_out;pix++)
		{
			sum=0;
			x=scan;
			y=pix;

			//for loop for summing the nearby pixels
			for(int k=x*compress;k<x*compress+compress;k++){
				for(int l=pix*compress;l<y*compress+compress;l++){
					sum+=image[k][l];
				}
			}

			//dividing by the total
			image_out[scan][pix]=(int)sum/(compress*compress);
		}
	}

	//writing the output file
	for(scan=0;scan<nscan_out;scan++)
	{
		write(fp2,&image_out[scan][0],npix_out*sizeof(unsigned char));
	}

	//closing file
	close(fp2);

}