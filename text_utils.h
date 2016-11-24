#define N 16
typedef struct instruct
{
    char inst[3];
    int hex_code;
    int warguments;
    char format[5];
} instruction;


instruction insn[N];

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
   	printf("%s\t%1X\t%1d\t%s\n",insn[i].inst,
			insn[i].hex_code,insn[i].warguments, insn[i].format);

}

