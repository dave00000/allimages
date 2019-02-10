/* 
 
 AllImages generates every pattern combination for any sized grid and saves as png files
 Author: David Adams 
 URL: https://github.com/dave00000/allimages/
 
 Compatibility: Working on Ubuntu 18.04
 Usage: all [width] [height]

*/

#include <stdio.h>
#include <stdlib.h>

void printImage(int y, int x, int data[], int imageNumber)
{
           FILE *imageFile;

           int iArrayLen = x * y;
           unsigned char pix[iArrayLen * 3] = {0};

           for (int i = 0; i < iArrayLen; i++)
           {
                   if (data[i] == 0)
                   {
                           //this should be black(0, 0, 0)
                           pix[i*3] = 0;
                           pix[i*3 + 1] = 0;
                           pix[i*3 + 2] = 0;
                   }
                   else
                   {
                           //this should be white(255,255,255)
                           pix[i*3] = 255;
                           pix[i*3 + 1] = 255;
                           pix[i*3 + 2] = 255;
                   }
           }

           char fileName [50];
           sprintf (fileName, "image%d.ppm", imageNumber);
           imageFile=fopen(fileName, "wb");
           if(imageFile==NULL){
              perror("ERROR: Cannot open output file");
              exit(EXIT_FAILURE);
           }

           fprintf(imageFile,"P6\n");               // P6 filetype
           fprintf(imageFile,"%d %d\n", x, y);   // dimensions
           fprintf(imageFile,"255\n");              // Max pixel

           fwrite(pix, 1, iArrayLen * 3, imageFile);
           fclose(imageFile);

           char command [200];
           sprintf (command, "convert image%d.ppm -scale 400x result%d.png", imageNumber, imageNumber);
           system(command);
           system("rm *.ppm");
}



void printArray(int n, int x, int y)
{
		int len = x * y;
        int bit = 1<<len - 1;
        int ilineBreak = 0;
        int dataArray[len];
        int iArrayIndex = 0;
        while ( bit )
        {
                int iVal = n & bit ? 1 : 0;
                printf("%d", iVal);
                bit >>= 1;
                ilineBreak++;
                if (x == ilineBreak)
                {
                        ilineBreak = 0;
                printf("\n");
                }
                dataArray[iArrayIndex] = iVal;
                iArrayIndex++;

        }
        printImage(y, x, dataArray, n);
        printf("\n");
}
int main(int argc,char* argv[])
{
	if (argc != 3)
	{
		printf("Invalid arguments. Try [./all x y]\n");
		exit(0);
	}

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int len = x * y;

    	int n = 1<<len, i;

    	int iCount = 0;
    	for(i=0;i<n;i++)
    	{
        	printArray(i, x, y);
        	iCount++;
    	}

    	printf("%d Images created..\n", iCount);
}
