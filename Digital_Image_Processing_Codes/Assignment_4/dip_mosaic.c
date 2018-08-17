/*
	Author: Hardik Udeshi
	Description: Take two images of the same size (preferably the boat image). Mosaic the two
				images side by side. Ask the user from which scan line they would like to mosaic the
				second image with the first one. The empty spaces should be padded properly.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

void main()
{
	//input variables
	char input_file1[100],output_file[100],input_file2[100];
	//unsigned char ** image,**image_out;
	int pix,npix1,scan,nscan1,npix2,nscan2, npix_out,nscan_out,*fp1,*fp2,cnt,temp,x,y,a,b,i,x0,y0,xx,yy,*fp3;
	int p1,s1,p2,s2,cnt1=0,cnt2=0;
	
	//npix and nscan of image1
	printf("Give npix1 nscan1 \n");
	scanf("%d %d",&npix1,&nscan1);

	//npix and nscan of image2
	printf("Give npix2 nscan2 \n");
	scanf("%d %d",&npix2,&nscan2);

	//starting nscan of image2
	printf("Give the starting nscan of the image2:\n");
	scanf("%d",&s2);


	//input1 file
	printf("Give me input1 file \n");
	scanf("%s",input_file1);
	printf("input1 file is %s\n",input_file1);

	//input2 file
	printf("Give me input2 file \n");
	scanf("%s",input_file2);
	printf("input2 file is %s\n",input_file2);

	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);

	//size of new image
	npix_out = npix1+npix2;
	nscan_out = nscan1>(nscan2+s2)? nscan1:(nscan2+s2);


	printf("%d %d",npix_out,nscan_out);

	//image arrays of input1, input2 and output
	unsigned char *image1 = (unsigned char *)calloc(npix1,sizeof(unsigned char));
	unsigned char *image2 = (unsigned char *)calloc(npix2,sizeof(unsigned char));
	unsigned char *image_out = (unsigned char *)calloc(npix_out,sizeof(unsigned char));

	// *image = (unsigned char *)malloc(npix*nscan*sizeof(unsigned char));
	// *image_out = (unsigned char *)malloc(npix_out*nscan_out*sizeof(unsigned char));




	//opening inputfile1
	fp1 = open(input_file1,O_RDONLY);
	if(fp1<0)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	
	//opening input file2
	fp3 = open(input_file2,O_RDONLY);
	if(fp3<0)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	

	//creating output file
	fp2 = creat(output_file,0666);

	if(fp2<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}	

	//for loop for number of rows
	for(scan=0;scan<nscan_out;scan++)
	{
		//reading image1
		if(scan<nscan1)
			read(fp1,&image1[0],npix1*sizeof(unsigned char));
		//initializing image1
		else
		{
			memset(image1,0,npix1*sizeof(unsigned char));
		}

		//reading image2
		if(scan>=s2 && scan<s2+nscan2)
			read(fp3,&image2[0],npix2*sizeof(unsigned char));
		//initializing image2
		else
		{
			memset(image2,0,npix2*sizeof(unsigned char));
		}

		//for loop for number of cols
		for(pix=0;pix<npix_out;pix++)
		{
			//for image1
			if(pix<npix1)
			{
				
				if(scan<=nscan1)
					image_out[pix]=image1[pix];
				else
					image_out[pix]=0;
				
			}

			//for image2
			else
			{
				//checking if scan is not equal to its starting nscan
				if(scan<s2)
				{
					image_out[pix]=0;
				}

				//if it is equal
				else
				{
					//subtracting the starting index
					cnt2=scan-s2;
					if(cnt2<=(nscan2))
					{
						//printf("%d\n", cnt2);
						image_out[pix]=image2[pix-npix1];
					}
					else
						image_out[pix]=0;
				}
			}
		}

		//writing into the file
		write(fp2,&image_out[0],npix_out*sizeof(unsigned char));


	}

	//closing the files
	close(fp1);
	close(fp2);
	close(fp3);

}
