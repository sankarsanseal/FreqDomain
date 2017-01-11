//
//  main.c
//  PGMFreq
//
//  Created by Sankarsan Seal on 05/01/17.
//  Copyright © 2017 Sankarsan Seal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    FILE * fp;
    char m1,m2;
    unsigned char temp;
    char comment[255];
    int width_col=0,height_row=0;
    int maxval=0;
    int **mat;
    int i,j;
    fp=fopen("chat.pgm","rb");
    fscanf(fp,"%c%c%*c",&m1, &m2);
    fprintf(stdout,"Magicnumber: %c, %c\n",m1,m2);
    if ( m1=='P' && m2 == '5')
    {
        fscanf(fp,"%c",&temp);
        fprintf(stdout,"Comment is: %c",temp);
        while (temp=='#')
        {
            fscanf(fp,"%[^\n]s",comment);
            fprintf(stdout,"%s\n",comment);
            fscanf(fp,"%c",&temp);
        }
        
        fscanf(fp,"%d%d", &width_col, &height_row);
        fprintf(stdout," Width:%d Height:%d\n",width_col,height_row);
        fscanf(fp,"%d",&maxval);
        fprintf(stdout,"Maximum Pixel Value:%d\n",maxval);
        
        mat=(int **)malloc(sizeof(int *)*height_row);
        for(i=0;i<height_row;i++)
        {
            *(mat +i )=(int *)malloc(sizeof(int)*width_col);
            for(j=0;j<width_col;j++)
                mat[i][j]=0;
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
    }
    else
    {
        fprintf(stderr,"Error: Wrong file format for PGM P5");
    }
     
    fclose(fp);
    return 0;
}
