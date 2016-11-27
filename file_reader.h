#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory_things.h"

FILE * archivo;
char datass[10000]="";
char linebyline[255][200];
char data[28];
char data_inHEX[10000];
int NL=0;
int isok=0;
int Nlines=0;
void view_line_data(const char * string,int y);
void check_if_has_syntaxe();
void translate();
void put_fileheader();
int verificar_dosp();

void col_line_ind();
void col_line_emb();

void ReadLBL();

void read_lineBline()
{
    int i,j;
    j=0;
    char caracter;
    printf("RBL: %d\n",strlen(datass));
    for(i=0;i<strlen(datass);i++)
    {
	caracter=datass[i];
	if(caracter != 0xa)
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

    if (!verificar_dosp())
    	ReadLBL();
    else
	printf("Puede que haya una etiqueta\n");


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
    printf("Datos\n %s\n",datass);
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
    	archivo=fopen(arch,"wr");
	fprintf(archivo,"%s","");
	fprintf(archivo,"%s",data_inHEX);
	//printf("NULL\n");
    //}
    fclose(archivo);

}

