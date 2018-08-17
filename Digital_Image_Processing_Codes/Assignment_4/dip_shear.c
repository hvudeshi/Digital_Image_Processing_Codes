/*
	Author: Hardik Udeshi
	Description: Shear an image. Take any image and the shearing angle as an input. Your output
				should be the sheared version of the input image.
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
	unsigned char *image,*image_out;
	int pix,npix,scan,nscan, *fp1,*fp2,nscan_out,npix_out,cnt=0;

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
	float rads,theta;
	
	//shear angle
	printf("Give Shear angle: \n");
	scanf("%f",&theta);
	
	//converting to radians
	rads = (theta)*22/(7*180);
	
	//new size of the output image
	npix_out = npix+nscan*tan(fabs(rads));
	nscan_out = nscan;

	printf("New Size:%d %d\n",npix_out,nscan_out);

	//output image array
	image_out = (unsigned char *)calloc(npix_out,sizeof(unsigned char));

	//opening the input file
	fp1=open(input_file,O_RDONLY);

	if(fp1<0)
	{
		printf("Error in Opening the File.\n");
		exit(1);
	}

	//creating the output file
	fp2 = creat(output_file,0666);

	if(fp2<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}

	//for theta>=0
	if(theta>=(float)0)
	{
		//for loop for number of rows
		for(scan=nscan_out;scan>0;scan--)
		{
			//reading the input file
			read(fp1,&image[0],npix*sizeof(unsigned char));
			
			//for loop for number of cols
			for(pix=scan*tan(rads);pix<npix_out;pix++)
			{
				//checking if either of the conditions are satisfied
				if((pix-scan*tan(rads))>=0 && (pix-scan*tan(rads))<npix)
					image_out[pix] = image[(int)(pix-scan*tan(rads))];

				//else
				else
					image_out[pix] = 0;

			}
			//writing into the file
			write(fp2,&image_out[0],npix_out*sizeof(unsigned char));
		}

	}

	//if theta is less than 0
	else
	{
		//for loop for no. of rows
		for(scan=nscan_out-1;scan>=0;scan--)
		{
			//reading the input file
			read(fp1,&image[0],npix*sizeof(unsigned char));
			cnt = npix -1;

			//for loop for no. of cols
			for(pix=npix_out - (pix-scan*tan(rads));pix>0;pix--)
			{
				if(cnt>=0)
					image_out[pix] = image[cnt];

				else
					image_out[pix] = 0;

				cnt--;

			}
			//writing into the file
			write(fp2,&image_out[0],npix_out*sizeof(unsigned char));
		}

	}
	//closing the files
	close(fp1);
	close(fp2);


}
