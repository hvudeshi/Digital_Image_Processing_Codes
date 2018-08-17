/*
	Author: Hardik Udeshi
	Description: Create a gradient of grayscale intensities (0 to 255). Take the image size as your
				 input. The size of the image, given as input, should still produce a proper gradient.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

void main()
{
	//input variables
	char output_file[100],output_file1[100];
	unsigned char *image,*image1;
	int pix,npix,scan,nscan, *fp1,cnt=0,temp,x,y,a,b,i,cnt1=0;

	//inputs npix and nscan
	printf("Give npix nscan \n");
	scanf("%d %d",&npix,&nscan);

	//output image array
	image = (unsigned char *)calloc(npix,sizeof(unsigned char));

	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);

	//creating output file
	fp1 = creat(output_file,0666);
	if(fp1<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}


	temp=0;

	//for loop for rows of an image
	for(scan=0;scan<nscan;scan++)
	{
		cnt++;

		//if nscan is a multiple of 256
		if(nscan%256==0)
		{	
			//Repeating the pixel value till cnt!=nscan/256
			if(cnt==nscan/256)
			{
				cnt=0;
				temp++;
			}

			//for loop for columns of an image
			for(pix=0;pix<npix;pix++)
			{
				image[pix]=temp;
			}
		
		}

		//If nscan is not a multiple of 256
		else
		{
			cnt1++;

			//Repeating the pixel (nscan/256 +1) for nscan%256=0
			if(cnt1<=(nscan/256 + 1)*(nscan%256))
			{
				if(cnt==(nscan/256 + 1))
				{
					cnt=0;
					//printf("\n%d",cnt1);
					temp++;
				}
					
			}


			//for nscan%256!=0
			else
			{
				if(cnt==(nscan/256))
				{
					cnt=0;
					temp++;
				}	
			}
			
			//for loop for columns of an image
			for(pix=0;pix<npix;pix++)
			{
				image[pix]=temp;
			}	
		}
		
		
		write(fp1,&image[0],npix*sizeof(unsigned char));
	}

	close(fp1);
}