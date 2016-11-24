#include "file_reader.h"
typedef struct instruct
{
    char inst[3];
    int hex_code;
    int warguments;
} instruction;


#define N 16
instruction insn[N];


void asignacion_ins()
{

    char nmonicos[N][4]={
	    "ADD",
	    "SUB",
	    "AND",
	    "OR",
	    "SR",
	    "SL",
	    "SLT",
	    "CMP",
	    "SB",
	    "LB",
	    "LI",
	    "LUI",
	    "JMP",
	    "BRA",
	    "JR",
	    "SPC"
    };
    int hex_codes[N]={
	    0x0,
	    0x01,
	    0x02,
	    0x03,
	    0x04,
	    0x05,
	    0x06,
	    0x07,
	    0x08,
	    0x09,
	    0x0A,
	    0x0B,
	    0x0C,
	    0x0D,
	    0x0E,
	    0x0F
    };
    int wargsm[N]={
	    3,
	    3,
	    3,
	    3,
	    2,
	    2,
	    2,
	    2,
	    2,
	    2,
	    2,
	    2,
	    1,
	    1,
	    1,
	    1
    };
    int i;

    for(i=0;i<N;i++)
    {
    	sprintf(insn[i].inst,"%s",nmonicos[i]);
    	insn[i].hex_code=hex_codes[i];
    	insn[i].warguments=wargsm[i];
    }

    
}

int count_words(const char * string) 
{
    /*printf("LAST LETTER: 0x%X\n",string[strlen(string)-1]);*/
    if(!strcmp(string,""))
	return 0;
    int cambios,i=0;
    int palabras;
    char anterior=0x20;
    char caracter;

    for(i=0;i<strlen(string);i++)
    {
	caracter=string[i];
	if(caracter == 0x09)
	    caracter=0x20;
	if(caracter == 0x20 && anterior != 0x20)
	   cambios++;
	anterior=caracter;
    }
    caracter=string[strlen(string)-1];
    if(caracter==0x20 || caracter==0x09)
	cambios--;

    palabras=cambios+1;
    return palabras;

}

void print_nmonics()
{
   int i;
   for (i=0;i<N;i++)
   	printf("%s\t%1X\t%1d\n",insn[i].inst,
			insn[i].hex_code,insn[i].warguments);

}
int main()
{
   //create__write_archivo("dats.txt");
   asignacion_ins();
   //printf("Num of words: %d\n",count_words("ADD 				R1 R2"));
   print_nmonics();
   return 0;
}
