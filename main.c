//
//  main.c
//  PGMFreq
//
//  Created by Sankarsan Seal on 05/01/17.
//  Copyright © 2017 Sankarsan Seal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    FILE * fp;
    FILE * output;
    char m1,m2;
    unsigned char temp;
    char comment[255];
    int width_col=0,height_row=0;
    int maxval=0;
    int **mat;
    int **out;
    int i,j,k,l;
    double **freqreal,**freqimaginary;
    double tempdouble=0;
    double multi=0;
    double test1=0,test2=0;
    fp=fopen("cat_small.pgm","rb");
    output=fopen("freqchat.pgm","wb");
    fscanf(fp,"%c%c%*c",&m1, &m2);
    fprintf(stdout,"Magicnumber: %c, %c\n",m1,m2);
    if ( m1=='P' && m2 == '5')
    {
        fscanf(fp,"%c%*c",&temp);
        fprintf(stdout,"Comment is: %c",temp);
        while (temp=='#')
        {
            fscanf(fp,"%[^\n]s",comment);
            fprintf(stdout,"%s\n",comment);
            fscanf(fp,"%c%*c",&temp);
        }
        
        fscanf(fp,"%d%d", &width_col, &height_row);
        fprintf(stdout," Width:%d Height:%d\n",width_col,height_row);
        fscanf(fp,"%d",&maxval);
        fprintf(stdout,"Maximum Pixel Value:%d\n",maxval);
       
 
	multi=1/((double)width_col*height_row);
        mat=(int **)malloc(sizeof(int *)*height_row);
	out=(int **)malloc(sizeof(int *)*height_row);
        for(i=0;i<height_row;i++)
        {
            *(mat +i )=(int *)malloc(sizeof(int)*width_col);
	    *(out +i )=(int *)malloc(sizeof(int)*width_col);
            for(j=0;j<width_col;j++)
	    {
                mat[i][j]=0;
		out[i][j]=0;
	    }
        }
        
        for(i=0;i<height_row;i++)
        {
            for(j=0;j<width_col;j++)
            {
                fscanf(fp,"%c",&temp);
                mat[i][j]=(int)temp;
            }
        }
        
        for(i=0;i<height_row;i++)
        {
            for(j=0;j<width_col;j++)
            {
                fprintf(stdout,"%d ", mat[i][j]);
            }
            fprintf(stdout,"\n");
        }

	freqreal=(double **)malloc(sizeof(double *) *height_row);
	freqimaginary=(double **)malloc(sizeof(double *) *height_row);

	for(i=0;i<height_row;i++)
	{
		*(freqreal+i)=(double*)malloc(sizeof(double) * width_col);
		*(freqimaginary+i)=(double*)malloc(sizeof(double) * width_col);
		for(j=0;j<width_col;j++)
		{
			freqreal[i][j]=0;
			freqimaginary[i][j]=0;
		}
	}
	

	for(i=0;i<height_row;i++)
	{
		for(j=0;j<width_col;j++)
		{
			for(k=0;k<height_row;k++)
			{
				for(l=0;l<width_col;l++)
				{
					tempdouble=2*M_PI*(i*k/((double)height_row)
							+ j*l/((double)width_col));
					freqreal[i][j]+=(double)mat[k][l]
						*cos(tempdouble);
					freqimaginary[i][j]+=(double)mat[k][l]
							*sin(tempdouble);
				}
			
			}

			//freqreal[i][j]*=multi;
			//freqimaginary[i][j]*=multi;
	//	fprintf(stdout,"i: %d j: %d real:%lf ima: %lf\n",i,j,freqreal[i][j], freqimaginary[i][j]);	

		}
	}


		fprintf(stdout,"\n********\n");
	fprintf(output,"%c%c\n#Created by Sankarsan Seal",'P','5');
	sprintf(comment,"%d %d",width_col,height_row);	
	fprintf(output,"\n%s",comment);
	sprintf(comment,"%d",maxval);
	fprintf(output,"\n%s ",comment);
	fflush(output);
	tempdouble=0;
	for(i=0;i<height_row;i++)
	{
		for(j=0;j<width_col ;j++)
		{
		temp=0;
		test1=0;
		test2=0;
		
			for(k=0;k<height_row;k++)
			{
				for(l=0;l<width_col;l++)
				{
				
					tempdouble=2*M_PI*(i*k/((double)height_row)
							+ j*l/((double)width_col)); 
					test1+=freqreal[k][l]*cos(tempdouble);
					test1+=freqimaginary[k][l]
							*sin(tempdouble);
					test2+=freqreal[k][l]*sin(tempdouble);
					test2-=freqimaginary[k][l]
						*cos(tempdouble);
				
//fprintf(stdout,"test1:%lf\n",test1);
				}	
			}
		temp=(char)(test1*multi);
		fwrite(&temp,sizeof(temp),1,output);
		fprintf(stdout,"%d ",(int)test1);
		}
		

		//fprintf(output,"\n");
	}	

    }
    else
    {
        fprintf(stderr,"Error: Wrong file format for PGM P5");
    }
     
    fclose(fp);
    fclose(output);
    return 0;
}
