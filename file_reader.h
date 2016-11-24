#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * archivo;
char datass[1000]="";
char data[28];


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
    
}


void create__write_archivo(const char arch[])
{
    archivo=fopen(arch,"r");
    if(archivo!=NULL)
    {
    	archivo=fopen(arch,"a");
	sprintf(datass,"datos a grabarse");
	fprintf(archivo,"%s",datass);
    }
    else
    {
    	archivo=fopen(arch,"a+");
	printf("NULL\n");
    }

}

