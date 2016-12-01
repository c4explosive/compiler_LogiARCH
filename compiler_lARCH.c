#include "file_reader.h"
#include "text_utils.h"
#include "translator.h"

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
    char forms[N][5]={
	    "OOO",
	    "OOO",
	    "OOO",
	    "OOO", //t1
	    "OOX",
	    "OOX", //t2
	    "XOO",
	    "XOO",
	    "XOO", //t3
	    "OOX", //t4
	    "OE",
	    "OE", //t5
	    "XE",
	    "XE", //t6
	    "XOX", //t7
	    "OXX" //t8
    };
    char uforms[N][6]={
	    "OOO",
	    "OOO",
	    "OOO",
	    "OOO", //t1
	    "OO",
	    "OO", //t2
	    "OO",
	    "OO",
	    "OO", //t3
	    "OO", //t4
	    "OE",
	    "OE", //t5
	    "E",
	    "E", //t6
	    "O", //t7
	    "O" //t8
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
        sprintf(insn[i].format,"%s",forms[i]);
        sprintf(insn[i].uformat,"%s",uforms[i]);
    }


}

int main(int argc, char * argv[])
{
   //create__write_archivo("dats.txt");
   asignacion_ins();
   int i;
   read_archivo(argv[1]);
   put_fileheader();
   check_if_has_syntaxe();
   translate();
   //fix_O_to_0();
   create__write_archivo(argv[2]);
   return 0;
}
