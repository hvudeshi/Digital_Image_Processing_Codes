/*
	Author: Hardik Udeshi
	Description: Calculate and save 8x8 Haar Transform Basis Images.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//Matrix Multiplication
float** multiply(float **mat1, float** mat2,int n1, int m1, int n2, int m2)
{
    int i, j, k;

    //Dynamically Allocating memory to an array
    float** res = (float**)malloc(n1*sizeof(float*));
	for(i=0;i<m2;i++)
	{
		res[i] = (float*)malloc(m2*sizeof(float));
	}


    //Matrix Multiplication logic
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < m2; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < n2; k++)
            {
                res[i][j] += mat1[i][k]*mat2[k][j];
                
            }
            
        }
    }


    //returning matrix
    return res;

}

//Transpose of an matrix
float** transpose(float **mat,int N, int M)
{
	int i,j;

	//Dynamically Allocating memory to an array
	float** res = (float**)malloc(M*sizeof(float*));
	for(i=0;i<M;i++)
	{
		res[i] = (float*)malloc(N*sizeof(float));
	}


	//Transpose
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			res[i][j] = mat[j][i];
		}
	}

	//returning matrix
	return res;
}

//Computing p
int compute_p(int n)
{
	int cnt=0;
	if (n == 0)
      return 0;
  while (n != 1)
  {
      n = n/2;
      cnt++;
  }

  return cnt;
}

void main()
{
	int N;
	FILE *fplog, *fp1;	//File for storing output

	char output_file[100], output_image_file[100];

	//ASking user for N
	printf("\nEnter N:");
	scanf("%d",&N);
	
	//output file
	printf("Give me output file \n");
	scanf("%s",output_file);
	printf("Output file is %s\n",output_file);

	//output image file
	printf("Give me output image file \n");
	scanf("%s",output_image_file);
	printf("Output file is %s\n",output_image_file);

	//opening the file 
	fplog = fopen(output_file,"w");
	if(fplog<0)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	//opening the file 
	fp1 = creat(output_image_file,0667);
	if(fplog<0)
	{
		printf("Error in creating file\n");
		exit(1);
	}	

	fprintf(fplog,"\nThe value of N is %d\n",N);

	int i,j,n,p;

	float t=0;

	//Dynamically Allocating memory to an arrays
	float** res = (float**)malloc(N*sizeof(float*));
	for(i=0;i<N;i++)
	{
		res[i] = (float*)malloc(N*sizeof(float));
	}

	float** H = (float**)malloc(N*sizeof(float*));
	for(i=0;i<N;i++)
	{
		H[i] = (float*)malloc(N*sizeof(float));
	}

	float** HT = (float**)malloc(N*sizeof(float*));
	for(i=0;i<N;i++)
	{
		HT[i] = (float*)malloc(N*sizeof(float));
	}

	fprintf(fplog,"\n");

	fprintf(fplog,"\nThe Haar Matrix is as follows-\n");

	//Forming H matrix
	for(i=0;i<N;i++)
	{
		H[0][i]=1/(sqrt(N));

		fprintf(fplog,"%f\t",H[0][i]);
	}	

	fprintf(fplog,"\n");

	t=0;
	for(i=0;i<N;i++)
	{
		t=(float)i/N;
		//printf("\n%d\n",t);
		if(t<0.5)
		{
			H[1][i] = 1/(sqrt(N));
		}

		else
		{
			H[1][i] = -1/(sqrt(N));
		}

		fprintf(fplog,"%f\t",H[1][i]);
		
		
	}

	fprintf(fplog,"\n");


	for(i=2;i<N;i++)
	{
		t=0;
		int j,n,p;
		for(j=0;j<N;j++)
		{
			p = compute_p(i);
			t=(float)j/N;
			n = i - pow(2,p);

			//printf("\n %d %d\n",n,p);
			if(t>=(float)(n/pow(2,p)) && t<(float)((n+0.5)/pow(2,p)))
			{
				H[i][j] = sqrt(pow(2,p))/(sqrt(N));
			}

			else if(t>=(float)((n+0.5)/pow(2,p)) && t<(float)((n+1)/pow(2,p)))
			{
				H[i][j] = sqrt(pow(2,p))*(-1)/(sqrt(N));
			}

			else
			{
				H[i][j]=0;
			}

			fprintf(fplog,"%f\t",H[i][j]);
			

		}

		fprintf(fplog,"\n");
	}


	//Transpose of H Matrix
	fprintf(fplog,"\nThe Transpose Matrix is as follows-\n");
	HT = transpose(H,N,N);

	for(int k=0;k<N;k++)
	{
		for(int l=0;l<N;l++)
		{
			fprintf(fplog,"%f\t",HT[k][l]);
		}
		fprintf(fplog,"\n");
	}

	//Dynamically Allocating memory for columns of H
	float** Hr = (float**)malloc(1*sizeof(float*));
	for(i=0;i<1;i++)
	{
		Hr[i] = (float*)malloc(N*sizeof(float));
	}


	//Dynamically Allocating memory for rows of HT
	float** HTc = (float**)malloc(N*sizeof(float*));
	for(i=0;i<N;i++)
	{
		HTc[i] = (float*)malloc(1*sizeof(float));
	}

	float** final_res;

	unsigned char** basis_image = (unsigned char**)malloc(N*N*sizeof(unsigned char*));
	for(i=0;i<N*N;i++)
	{
		basis_image[i] = (unsigned char*)malloc(N*N*sizeof(unsigned char));
	}

	int cnt=0;


	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			cnt++;
			for (int k = 0; k < N; ++k)
			{
				Hr[0][k] = H[j][k];
				HTc[k][0] = HT[k][i];
			}

			//Hr=transpose(HTc,N,1);
			//Multiplying hi and hjT
			final_res = multiply(HTc,Hr,N,1,1,N);

			//Writing into the log file
			fprintf(fplog,"\nBasis Image: %d\n",cnt);
			for(int k=0;k<N;k++)
			{
				for(int l=0;l<N;l++)
				{
					if(final_res[k][l]==0)
					{
						final_res[k][l]=150;
					}

					else if(final_res[k][l]<0)
					{
						final_res[k][l]=0;
					}

					else
					{
						final_res[k][l]=255;	
					}

					basis_image[k+N*i][l+N*j]=(unsigned char)final_res[k][l];
					fprintf(fplog,"%f\t",final_res[k][l]);
				}

				fprintf(fplog,"\n");
			}




		}
	}


	for(i=0;i<N*N;i++)
	{
		write(fp1,&basis_image[i][0],N*N*sizeof(unsigned char));
	}

	//closing the file
	close(fplog);
	close(fp1);

}

