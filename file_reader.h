#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory_things.h"

FILE * archivo;
char datass[10000]="";
int whereAreColons[255][255];
int NumOfdots;
char linebyline[255][200];
char data[28];
char data_inHEX[10000];
int NL=0;
int isok=0;
int Nlines=0;

void view_line_data(const char * string,int y);
void check_if_has_syntaxe(); //check for error in syntaxis in block wothout colons.
void translate(); //translator::translate()
void put_fileheader(); //Put the ARCH_HEADER (v2.0 raw)
int verificar_dosp(); //Verify is the datass have colons
void where_lines_are_colons();

void col_line_ind(); //To took individual lines.
void col_line_emb(); //To took embebeds lines.

void choose_ind_emb(); //Choose between individual or embebed comments.
void ReadLBL(); //Go to text_utils::view_line_data()

void print_buffer_line(); //Print lines in buffer (lineByline array)
void clean_buffer_line(); //Clean buffer for new use

void print_buffer_line()
{
    int i;
    for(i=0;i<NL;i++)
	    printf("Line %d: %s\n",i,linebyline[i]);
}

void where_lines_are_colons()
{
    int i;
    char * pch;
    for(i=0;i<NL;i++)
    {
        pch=strchr(linebyline[i],0x3a);
        if(pch != NULL)
        {
            whereAreColons[0][i]=i;
            whereAreColons[1][i]=pch-linebyline[i];
            NumOfdots++;
        }

    }

    //print the list of columns
    for (i=0;i<NumOfdots;i++)
    {
        printf("LINE:: %d have colon in %d\n",whereAreColons[0][i],whereAreColons[1][i]);
    }

}

void read_lineBline()
{
    int i,j;
    j=0;
    char caracter;
    printf("RBL: %d\n",strlen(datass));
    for(i=0;i<strlen(datass);i++)
    {
        caracter=datass[i];
        if(caracter != '\n')
        {
	    //printf("chart::: %c\n",toupper(caracter));
    	    linebyline[NL][j]=toupper(caracter);
	    //printf("CHAR:: 0x%X\n",linebyline[NL][j]);
	    j++;
        }
        else
        {
            NL++;
            j=0;
        }
    }
    NL+=1;
    print_buffer_line();
    if (!verificar_dosp())
    	ReadLBL();
    else
    {
        printf("Puede que haya una etiqueta\n");
        choose_ind_emb();
    }


}

void choose_ind_emb()
{

}

void ReadLBL()
{
    int i;
    printf("NL:: %d\n",NL);
    	for(i=0;i<NL;i++)
    	{
            view_line_data(linebyline[i],i);
    	}
    	Nlines=NL-1;
}


void read_archivo(const char data[])
{
    int ch;
    int i=0;
    archivo=fopen(data,"r");

    while(1)
    {
    	ch=fgetc(archivo);
	if(ch!=EOF)
	{
	    datass[i]=ch;
	    //printf("%c",ch);
	}
	else
	    break;
	i++;
    }
    fclose(archivo);
    //printf("Datos\n %s\n",datass);
    read_lineBline();
}


int verificar_dosp()
{
    int i;
    char caracter;
    for(i=0;i<strlen(datass);i++)
    {
	caracter=datass[i];
	if(caracter == 0x3a)
		return 1;
    }
    return 0;
}

void create__write_archivo(const char arch[])
{
    //archivo=fopen(arch,"r");
    /*if(archivo!=NULL)
    {
    	archivo=fopen(arch,"a");
   	printf("%s\n",data_inHEX);
	//sprintf(datass,data_inHEX);
	fprintf(archivo,"%s",data_inHEX);
    }
    else
    {*/
    printf("where save:: %s\n",arch);
    archivo=fopen(arch,"w+");
	fprintf(archivo,"%s","");
	fprintf(archivo,"%s",data_inHEX);
	//printf("NULL\n");
    //}
    fclose(archivo);

}

