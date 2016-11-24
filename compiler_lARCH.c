#include "file_reader.h"
#include "text_utils.h"


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

int main()
{
   //create__write_archivo("dats.txt");
   asignacion_ins();
   //printf("Num of words: %d\n",count_words("ADD 				R1 R2"));
   print_nmonics();
   return 0;
}
