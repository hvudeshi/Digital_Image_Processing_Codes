/*
	Author: Hardik Udeshi
	Description: Rotate an image. Take any image as your input, also take in the image size as your
				input. Ask the user for the rotation angle. Your output should be the rotated version
				of the image.
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
	int pix,npix,scan,nscan, npix_out,nscan_out,*fp1,*fp2,cnt,temp,x,y,a,b,i,x0,y0,xx,yy;
	float theta;
	double rads;

	//input npix and nscan
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

	//angle of rotation
	printf("Angle of rotation:\n");
	scanf("%f",&theta);
	
	//Converting to radians
	rads = theta*22/(7*180);
	
	//New size of an image 
	npix_out = ceil(abs(npix*cos(rads))+abs(nscan*sin(rads))) + 1;
	nscan_out = ceil(abs(npix*sin(rads))+abs(nscan*cos(rads))) + 1;

	printf("New size:%d %d\n",npix_out,nscan_out);

	x0 = nscan/2;
	y0 = npix/2;

	
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



	//opening input file
	fp1 = open(input_file,O_RDONLY);
	if(fp1<0)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	//for loop for reading the input file
	for(scan=0;scan<nscan;scan++)
	{
		read(fp1,&image[scan][0],npix*sizeof(unsigned char));
	}

	//closing input file
	close(fp1);

	//creating output file
	fp2 = creat(output_file,0666);

	if(fp2<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}	

	//for loop for rows of new image
	for(scan=0;scan<nscan_out;scan++)
	{	
		//for loop for columns of new image
		for(pix=0;pix<npix_out;pix++)
		{
			//shifting the origin
			x = nscan_out/2-scan;
			y = pix - npix_out/2;

			//calculating new x and y co-ordinates after rotating
			xx = (int)(x*cos(-rads) - y*sin(-rads));
			yy = (int)(x*sin(-rads) + y*cos(-rads));

			xx = nscan/2-xx;
			yy = yy+npix/2;

			//checking if any of the following conditions satisfy then assigning it 255
			if(xx<0 || xx>=nscan || yy<0 || yy>=npix)
				image_out[scan][pix]=255;				

			//else part
			else
				image_out[scan][pix]=image[xx][yy];
		}
	}

	//for loop for writing to output file
	for(scan=0;scan<nscan_out;scan++)
	{
		write(fp2,&image_out[scan][0],npix_out*sizeof(unsigned char));
	}

	//closing output file
	close(fp2);

}