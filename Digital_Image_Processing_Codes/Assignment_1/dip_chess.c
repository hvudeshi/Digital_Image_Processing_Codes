/*
	Author: Hardik Udeshi
	Description: Create a chessboard image. Take the image size as your input.

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
	int pix,npix,scan,nscan, *fp1,cnt,temp,x,y,a,b,i;

	//input npix and nscan
	printf("Give npix nscan \n");
	scanf("%d %d",&npix,&nscan);

	///allocate memory to image and image1
	image=(unsigned char *)calloc(npix,sizeof(unsigned char));
	image1=(unsigned char *)calloc(npix,sizeof(unsigned char));

	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);


	//Creating output file
	fp1 = creat(output_file,0666);
	if(fp1<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}



	//for loop for rows of an image
	for(pix=0;pix<npix;pix++){
		image[pix]=((pix*8/npix)&1)?0:255;
		image1[pix]=((pix*8/npix)&1)?255:0;
			
	}

	scan_new=0;
	//filling the whole chess board from the previously generated rows(image and image2)
	while(scan_new<nscan) //repeat untill all rows are filled
	{
		//dividing nscan in 8 parts and fill odd parts with image
		for(scan=0;scan<nscan/8;scan++){
			write(fp1,&image[0],npix*sizeof(unsigned char));
			scan_new++;	
		}

		//dividing nscan in 8 parts and fill even parts with image2
		for(scan=0;scan<nscan/8;scan++){
			write(fp1,&image1[0],npix*sizeof(unsigned char));
			scan_new++;	
		}
		
	}

	free(image);



	//closing the file
	close(fp1);
}
