/*
	Author: Hardik Udeshi
	Description: Take an image. Find out its histogram and perform histogram equalisation.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>
void main()
{
	//input variables
	char output_file[100],input_file[100],output_final_file[100],output_final_image_file[100];
	unsigned char *image;
	int *image_out, *image_out_final, *image_out1, *image_out_map;
	unsigned char *new_image;
	int pix,npix,scan,nscan, *fp1,midx,midy,npix_out,nscan_out;

	//File pointer
	FILE *fp2,*fp3,*fp4;

	//npix and nscan
	printf("Give npix nscan \n");
	scanf("%d %d",&npix,&nscan);

	//input image array
	image = (unsigned char *)calloc(npix,sizeof(unsigned char));
	new_image = (unsigned char *)calloc(npix,sizeof(unsigned char));

	//input file
	printf("Give me input file \n");
	scanf("%s",input_file);

	//output file
	printf("Give me image histogram file before histogram equalisation: \n");
	scanf("%s",output_file);
	printf("Image histogram file before histogram equalisation is %s\n",output_file);
	

	//output file
	printf("Give me image histogram file after histogram equalisation: \n");
	scanf("%s",output_final_file);
	printf("Image histogram file after histogram equalisation is %s\n",output_final_file);

	//output file
	printf("Give me output image file: \n");
	scanf("%s",output_final_image_file);
	printf("Image histogram file after histogram equalisation is %s\n",output_final_image_file);

	//size of output npix and nscan
	npix_out = npix;
	nscan_out = nscan;

	//output int image array
	image_out = (int *)calloc(256,sizeof(int));

	memset(image_out,0,256*sizeof(int));

	//output int image array
	image_out1 = (int *)calloc(256,sizeof(int));

	memset(image_out1,0,256*sizeof(int));

	//output int image array
	image_out_map = (int *)calloc(256,sizeof(int));

	memset(image_out_map,0,256*sizeof(int));


	//output int image array
	image_out_final = (int *)calloc(256,sizeof(int));

	memset(image_out_final,0,256*sizeof(int));


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

	//opening the output file with write mode
	fp3 = fopen(output_final_file,"w");

	if(fp3<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}

	//opening the output file with write mode
	fp4 = creat(output_final_image_file,0667);

	if(fp4<0)
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

	//for loop for cumulative frequency
	for(scan=0;scan<256;scan++)
	{
		image_out1[scan]=image_out1[scan-1]+image_out[scan];
	}

	printf("Cumulative:%d \n",image_out1[255]);

	//for loop for dividing by cumulative frequency
	for(scan=0;scan<256;scan++)
	{
		image_out_map[scan]=ceil((float)image_out1[scan]/image_out1[255] * 255);
	}


	for(scan=0;scan<256;scan++)
	{
		image_out_final[image_out_map[scan]]+=image_out[scan];
	}

	//for loop for printing into the file
	for(scan=0;scan<256;scan++)
	{
		fprintf(fp3, "%d %d\n",scan,image_out_final[scan]);
	}

	close(fp1);

	//opening the input file
	fp1=open(input_file,O_RDONLY);

	if(fp1<0)
	{
		printf("Error in Opening the File.\n");
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
			//forming the new image
			new_image[pix] = (unsigned char)image_out_map[(int)image[pix]];
		}

		write(fp4,&new_image[0],npix*sizeof(unsigned char));
		
	}


	

	//closing the files
	close(fp1);
	close(fp2);
	close(fp3);
	close(fp4);


}
