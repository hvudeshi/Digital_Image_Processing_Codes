/*
	Author: Hardik Udeshi
	Description: JPEG Compression and Reconstruction of Image.

*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <float.h>

#define pi 3.142857
#define C 8
const int m = 8, n = 8;

//Discrete Cosine Transform Function
double** discreteCosineTransform(int **matrix)
{
    int i, j, k, l;
  
    // dct will store the discrete cosine transform
    // double dct;
    double **dct = (double **)malloc(m * sizeof(double *));
    for (i=0; i<8; i++)
         dct[i] = (double *)malloc(n * sizeof(double));
 
    double ci, cj, dct1, sum;
 
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
 
            // ci and cj depends on frequency as well as
            // number of row and columns of specified matrix
            if (i == 0)
                ci = 1 / sqrt(m);
            else
                ci = sqrt(2) / sqrt(m);
            if (j == 0)
                cj = 1 / sqrt(n);
            else
                cj = sqrt(2) / sqrt(n);
 
            // sum will temporarily store the sum of 
            // cosine signals
            sum = 0;
            for (k = 0; k < m; k++) {
                for (l = 0; l < n; l++) {
                    dct1 = matrix[k][l] * 
                           cos((2 * k + 1) * i * pi / (2 * m)) * 
                           cos((2 * l + 1) * j * pi / (2 * n));
                    sum = sum + dct1;
                }
            }
            dct[i][j] = ci * cj * sum;
        }
    }
  
    return dct;
}

//Inverse Discrete Cosine Transform Function
double** InversediscreteCosineTransform(double** in)
{
  int i, j, u, v;
  double s;

  double **idct = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         idct[i] = (double *)malloc(8 * sizeof(double));

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    {
      s = 0;

      for (u = 0; u < 8; u++)
        for (v = 0; v < 8; v++)
          s += in[u][v] * cos((2 * i + 1) * u * M_PI / 16) *
                          cos((2 * j + 1) * v * M_PI / 16) *
               ((u == 0) ? 1 / sqrt(2) : 1.) *
               ((v == 0) ? 1 / sqrt(2) : 1.);

      idct[i][j] = s / 4;
    }
    return idct;
}

//Printing Matrix if the matrix datatype is int
void print_matrix(int **matrix ,int x, int y)
{
  for(int i=0;i<x;i++)
  {
    for(int j=0;j<y;j++)
    {
      printf("%d\t" ,matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
}

//Printing Matrix if the matrix datatype is double
void print_matrix_f(double **matrix ,int x, int y)
{
  for(int i=0;i<x;i++)
  {
    for(int j=0;j<y;j++)
    {
      printf("%f\t" ,matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
}

//Store Matrix in ZigZag form
int* getZigZagMatrix( int **arr, int n, int m)
{
    int row = 0, col = 0;
    
    // Boolean variable that will true if we
    // need to increment 'row' value otherwise
    // false- if increment 'col' value
    int row_inc = 0;
    int array_size=m*n;
    int* w;
    w = (int *)malloc(array_size * sizeof(int));
    int array_counter=0;
 
    // Print matrix of lower half zig-zag pattern
    int mn = (m<n)?m:n;
    for (int len = 1; len <= mn; ++len) {
        for (int i = 0; i < len; ++i) {
            w[array_counter]=arr[row][col];
            array_counter++;
 
            if (i + 1 == len)
                break;
            // If row_increment value is true
            // increment row and decrement col
            // else decrement row and increment
            // col
            if (row_inc)
                ++row, --col;
            else
                --row, ++col;
        }
 
        if (len == mn)
            break;
 
        // Update row or col vlaue according
        // to the last increment
        if (row_inc)
            ++row, row_inc = 0;
        else
            ++col, row_inc = 1;
    }
 
    // Update the indexes of row and col variable
    if (row == 0) {
        if (col == m - 1)
            ++row;
        else
            ++col;
        row_inc = 1;
    }
    else {
        if (row == n - 1)
            ++col;
        else
            ++row;
        row_inc = 0;
    }
 
    // Print the next half zig-zag pattern
    int MAX = ((m>n)?m:n) - 1;
    for (int len, diag = MAX; diag > 0; --diag) {
 
        if (diag > mn)
            len = mn;
        else
            len = diag;
 
        for (int i = 0; i < len; ++i) {
            w[array_counter]=arr[row][col];
            array_counter++;
 
            if (i + 1 == len)
                break;
 
            // Update row or col vlaue according
            // to the last increment
            if (row_inc)
                ++row, --col;
            else
                ++col, --row;
        }
 
        // Update the indexes of row and col variable
        if (row == 0 || col == m - 1) {
            if (col == m - 1)
                ++row;
            else
                ++col;
 
            row_inc = 1;
        }
 
        else if (col == 0 || row == n - 1) {
            if (row == n - 1)
                ++col;
            else
                ++row;
 
            row_inc = 0;
        }
    }

    return w;
}

//Getting ZigZag Matrix index
int* getZigZagindex(int n, int m)
{
    int row = 0, col = 0;

    // Boolean variable that will true if we
    // need to increment 'row' value otherwise
    // false- if increment 'col' value
    int row_inc = 0;
    int array_size=m*n;
    int* index;
    index = (int *)malloc(array_size * sizeof(int));
    int array_counter=0;
 
    // Print matrix of lower half zig-zag pattern
    int mn = (m<n)?m:n;
    for (int len = 1; len <= mn; ++len) {
        for (int i = 0; i < len; ++i) {
            index[array_counter]=row*m+col;
            array_counter++;
 
            if (i + 1 == len)
                break;
            // If row_increment value is true
            // increment row and decrement col
            // else decrement row and increment
            // col
            if (row_inc)
                ++row, --col;
            else
                --row, ++col;
        }
 
        if (len == mn)
            break;
 
        // Update row or col vlaue according
        // to the last increment
        if (row_inc)
            ++row, row_inc = 0;
        else
            ++col, row_inc = 1;
    }
 
    // Update the indexes of row and col variable
    if (row == 0) {
        if (col == m - 1)
            ++row;
        else
            ++col;
        row_inc = 1;
    }
    else {
        if (row == n - 1)
            ++col;
        else
            ++row;
        row_inc = 0;
    }
 
    // Print the next half zig-zag pattern
    int MAX = ((m>n)?m:n) - 1;
    for (int len, diag = MAX; diag > 0; --diag) {
 
        if (diag > mn)
            len = mn;
        else
            len = diag;
 
        for (int i = 0; i < len; ++i) {
            index[array_counter]=row*m+col;
            array_counter++;
 
            if (i + 1 == len)
                break;
 
            // Update row or col vlaue according
            // to the last increment
            if (row_inc)
                ++row, --col;
            else
                ++col, --row;
        }
 
        // Update the indexes of row and col variable
        if (row == 0 || col == m - 1) {
            if (col == m - 1)
                ++row;
            else
                ++col;
 
            row_inc = 1;
        }
 
        else if (col == 0 || row == n - 1) {
            if (row == n - 1)
                ++col;
            else
                ++row;
 
            row_inc = 0;
        }
    }

    return index;
}




void main()
{
    int fp1,fp2,i,j,k;
    FILE* fp;
    double a;
    char input_image[100],output_image[100];
    unsigned char image[1000],image1[1000];

    int npix,nscan,pix,scan,i1,i2;

    //Input Image File
    printf("Give input image name \n");
    scanf("%s",input_image);
    printf("Give size of image \n");
    scanf("%d%d",&npix,&nscan);
    
    fp1= open(input_image,O_RDONLY);

    if (fp1<0)
    {
        printf("Error in opening %s image \n",input_image);
        exit(1);
    }
   
   //Input Image
    int **img = (int **)malloc(nscan * sizeof(int *));
    for (i=0; i<nscan; i++)
         img[i] = (int *)malloc(npix * sizeof(int));
    
    //dct 8x8
    double **dct = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         dct[i] = (double *)malloc(8 * sizeof(double));


     //quantization 8x8
    int **quantization = (int **)malloc(8 * sizeof(int *));
    for (i=0; i<8; i++)
         quantization[i] = (int *)malloc(8 * sizeof(int));
    
    //Quantization Matrix
    int Q_matrix[8][8] = { { 16, 11, 10, 16, 24, 40, 51, 61 },
					{ 12, 12, 14, 19, 26, 58, 60, 55 },
					{ 14, 13, 16, 24, 40, 57, 69, 56 },
					{ 14, 17, 22, 29, 51, 87, 80, 62},
					{ 18, 22, 37, 56, 68, 109, 103, 77 },
					{ 24, 35, 55, 64, 81, 104, 113, 92},
					{ 49, 64, 78, 87, 103, 121, 120, 101 },
					{ 72, 92, 95, 98, 112, 100, 103, 99 } };

	//Storing input Image
    for (scan=0;scan<nscan;scan++)
    {
        read(fp1,&image[0],npix*sizeof(unsigned char));
        for (pix=0;pix<npix;pix++)
        {
            a=(double)image[pix];

            //Subtracting 128 from all the pixel values
            img[scan][pix] = a-128;
        }
    }

    fp = fopen ("compressed_image_adaptive.txt", "w+");

    //Storing 8x8 input image img in im 8x8 matrix
    int **im = (int **)malloc(8 * sizeof(int *));
    for (i=0; i<8; i++)
         im[i] = (int *)malloc(8 * sizeof(int));

    double **q_final = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         q_final[i] = (double *)malloc(8 * sizeof(double)); 

    double **init_Q_matrix = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         init_Q_matrix[i] = (double *)malloc(8 * sizeof(double));

    // double *DCTvalue;
    // DCTvalue = (double *)malloc(64 * sizeof(double));

    // double *DCTvalues;
    // DCTvalues = (double *)malloc(64 * sizeof(double));

    // double *init_Q_matrix;
    // init_Q_matrix = (double *)malloc(64 * sizeof(double));

    //Storing 64x11 Q_matrices
    double **testV = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         testV[i] = (double *)malloc(8 * sizeof(double));

    double **NQ_max = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         NQ_max[i] = (double *)malloc(8 * sizeof(double)); 

    double **dct_coeff = (double **)malloc(nscan * sizeof(double *));
    for (i=0; i<nscan; i++)
         dct_coeff[i] = (double *)malloc(npix * sizeof(double));

     double **dct_coeff_random = (double **)malloc(nscan * sizeof(double *));
    for (i=0; i<nscan; i++)
         dct_coeff_random[i] = (double *)malloc(npix * sizeof(double));

    double **NQ = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         NQ[i] = (double *)malloc(8 * sizeof(double));

    double min_dct = (double)200000,max_dct=(double)-200000; 

    for(scan=0;scan<nscan;scan+=8)
    {
        for(pix=0;pix<npix;pix+=8)
        {
            for(i=scan;i<scan+8;i++)
            {
              for(j=pix;j<pix+8;j++)
              {
                im[i-scan][j-pix]=img[i][j];
              }
            }

            //Calling discreteCosineTransform function 
            dct=discreteCosineTransform(im);

            for(i=scan;i<scan+8;i++)
            {
                for(j=pix;j<pix+8;j++)
                {
                    dct_coeff[i][j] = dct[i-scan][j-pix];

                    if(dct[i-scan][j-pix]<min_dct)
                    {
                        min_dct = dct[i-scan][j-pix];
                    }

                    if(dct[i-scan][j-pix]>max_dct)
                    {
                        max_dct = dct[i-scan][j-pix];
                    }
                }
            }

                      
        }
    }

    for(scan=0;scan<nscan;scan++)
    {
        for(pix=0;pix<npix;pix++)
        {
            dct_coeff_random[scan][pix] = (rand()%((int)max_dct-(int)min_dct))+(int)min_dct;
        }
    }

    int l;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            q_final[i][j] = (double) Q_matrix[i][j];
        }
    }

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            init_Q_matrix[i][j]=floor(((200-(2*70))*q_final[i][j]+50)/100);;
        }
    }

    //Storing 11 Q_matrices
    double max = -200000.0,min=200000.0;
    double *AMSE1;
    double *AMSE2;
    int ind1=0,ind2=0;

    AMSE1 = (double *)malloc(11 * sizeof(double));
    AMSE2 = (double *)malloc(11 * sizeof(double));

    for(i=0;i<11;i++)
    {
        AMSE1[i]=0;
        AMSE2[i]=0;
    }

    for(l=0;l<11;l++)
    {
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                testV[i][j]=init_Q_matrix[i][j]-5+l;
            }   
        }

        for(scan=0;scan<nscan;scan+=8)
        {
            for(pix=0;pix<npix;pix+=8)
            {
                for(i=scan;i<scan+8;i++)
                {
                    for(j=pix;j<pix+8;j++)
                    {
                        AMSE1[l]+=(dct_coeff_random[i][j]/testV[i-scan][j-pix] - dct_coeff_random[i][j]/q_final[i-scan][j-pix])*(dct_coeff_random[i][j]/testV[i-scan][j-pix] - dct_coeff_random[i][j]/q_final[i-scan][j-pix]);
                    }
                }
                
            }
        }    

        if(AMSE1[l]>max)
        {
            max = AMSE1[l];
            ind1 = l;
        }


    }

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            NQ_max[i][j]=init_Q_matrix[i][j]-5+ind1;
        }   
    }

    for(l=0;l<11;l++)
    {
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                testV[i][j]=init_Q_matrix[i][j]-5+l;
            }   
        }

        for(scan=0;scan<nscan;scan+=8)
        {
            for(pix=0;pix<npix;pix+=8)
            {
                for(i=scan;i<scan+8;i++)
                {
                    for(j=pix;j<pix+8;j++)
                    {
                        AMSE2[l]+=(dct_coeff_random[i][j]/NQ_max[i-scan][j-pix] - dct_coeff_random[i][j]/testV[i-scan][j-pix])*(dct_coeff_random[i][j]/NQ_max[i-scan][j-pix] - dct_coeff_random[i][j]/testV[i-scan][j-pix]);
                    }
                }
                //AMSE2[l]+=(dct_coeff_random[scan][pix]/NQ_max[scan/8][pix%8] - dct_coeff_random[scan][pix]/testV[scan/8][pix%8])*(dct_coeff_random[scan][pix]/NQ_max[scan/8][pix%8] - dct_coeff_random[scan][pix]/testV[scan/8][pix%8]);
            }
        }    

        if(AMSE2[l]<min)
        {
            min = AMSE2[l];
            ind2 = l;
        }


    }

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            NQ[i][j]=init_Q_matrix[i][j]-5+ind2;
        }   
    }
    
    //printf("here...\n");
    ////////////////////////////////////////////////

    //Storing DCT Matrix in Zigzag manner
            // DCTvalue = getZigZagMatrix(dct,8,8);

            // double min_dct= (double) 200000, max_dct = (double) -200000;

            // for(i=0;i<64;i++)
            // {
            //     if(DCTvalue[i]<min_dct)
            //     {
            //         min_dct = DCTvalue[i];
            //     }

            //     if(DCTvalue[i]>max_dct)
            //     {
            //         max_dct = DCTvalue[i];
            //     }
            // }

            // for(i=0;i<64;i++)
            // {
            //     DCTvalues[i] = (rand()%((int)max_dct-(int)min_dct))+(int)min_dct;
            // }

            


            

            // //For storing NQ'
            // for(j=0;j<11;j++)
            // {
            //     AMSE1[j]=0;
            //     for(k=0;k<64;k++)
            //     {
            //         AMSE1[j] += pow((DCTvalues[k]/testV[k][j] - DCTvalues[k]/init_Q_matrix[k]),2);
            //     }
            // }

            // for(j=0;j<11;j++)
            // {

            //     if(AMSE1[j]>max)
            //     {
            //         max = AMSE1[j];
            //         ind1 = j;
            //     }
            // }



            // //For storing NQ
            // for(j=0;j<11;j++)
            // {
            //     AMSE2[j]=0;
            //     for(k=0;k<64;k++)
            //     {
            //         AMSE2[j] += pow((DCTvalues[k]/testV[k][ind1] - DCTvalues[k]/testV[k][ind1]),2);
            //     }
            // }

            // for(j=0;j<11;j++)
            // {

            //     if(AMSE1[j]<min)
            //     {
            //         max = AMSE2[j];
            //         ind2 = j;
            //     }
            // }

            

            // for(i=0;i<64;i++)
            // {
            //     NQ[i]=testV[i][ind2]; 
            // }

            // int* w;
            // w = (int *)malloc(64 * sizeof(int));

            // for(i=0;i<64;i++)
            // {
            //     w[i] = DCTvalue[i]/NQ[i];
            // }



    for(scan=0;scan<nscan;scan+=8)
    {
        for(pix=0;pix<npix;pix+=8)
        {
            //Dividing each pixel value by values of Q_matrix at that index
                for(i=scan;i<scan+8;i++)
                {
                  for(j=pix;j<pix+8;j++)
                  {
                    quantization[i-scan][j-pix]=dct_coeff[i][j]/NQ[i-scan][j-pix];
                  }
                }

                int* w;
                int write_elements=m*n;

                //Stacking the image in ZigZag Form
                w = (int *)malloc((m*n) * sizeof(int));
                w = getZigZagMatrix(quantization,8,8);

                //Checking number of non-zero values
                for(i=m*n-1;i>=0;i--)
                {
                  if(w[i]==0) write_elements--;
                  else break;
                }
                
                fprintf(fp, "%d ",write_elements );
                for(i=0;i<write_elements;i++)
                {
                  fprintf(fp, "%d ",w[i] );
                }

        }
    }

            
    ////////////////////////////////////////////////
    fclose(fp);
    close(fp1);

    //-------------Reconstruction------------------

    int* index;
    int write_elements=m*n;

    //Finding the index of ZigZag Form
    index = (int *)malloc((m*n) * sizeof(int));
    index = getZigZagindex(8,8);

    unsigned char img_rc[npix][nscan];

    fp=fopen("compressed_image_adaptive.txt","r");
    if(fp<0)
    {
      printf("unable to open file\n");
      exit(1);
    }

    //To get the whole 8x8 image after compression
    int buffer[64];
    memset(buffer,0,64*sizeof(int));
    int nzTotal;
    
    //Matrix form of buffer
    double **block = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         block[i] = (double *)malloc(8 * sizeof(double));

     //For storing the matrix after idct
    double **idct = (double **)malloc(8 * sizeof(double *));
    for (i=0; i<8; i++)
         idct[i] = (double *)malloc(8 * sizeof(double));
    

    //Inverse Discrete Cosine Transform
    for(scan=0;scan<nscan;scan+=8)
    {
        for(pix=0;pix<npix;pix+=8)
        {
          memset(buffer,0,64*sizeof(int));
          fscanf(fp,"%d",&nzTotal);
          for(i=0;i<nzTotal;i++)
          {
            fscanf(fp,"%d",&buffer[i]); 
          }

          //Multiplying the pixel values with Q_matrix
          for (i = 0; i < 64; ++i)
          {
            block[index[i]/8][index[i]%8]=buffer[i];
            block[index[i]/8][index[i]%8]*=q_final[index[i]/8][index[i]%8];
          }

          //Inverse Discrete Cosine Transform
          idct=InversediscreteCosineTransform(block);

          //Adding 128 with the image and storing it in img_rc which is a reconstructed 512x512 image
          for(i=scan;i<scan+8;i++)
          {
            for(j=pix;j<pix+8;j++)
            {
              img_rc[i][j]=(unsigned char)((int)(idct[i-scan][j-pix]+128));
            }
          }
        }
    }



    //Output File
    sprintf(output_image,"%s_reconstructed_adaptive",input_image);
    fp2= creat(output_image,0667);
    if (fp2<0)
    {
        printf("Error in opening %s image \n",output_image);
        exit(1);
    }

    //Writing it in the file
    write(fp2,&img_rc,(npix)*(nscan)*sizeof(unsigned char));
    close(fp2);
}

/*
Huffman Coding in image compression


*/