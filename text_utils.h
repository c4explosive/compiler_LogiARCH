#define N 16
typedef struct instruct
{
    char inst[3];
    int hex_code;
    int warguments;
    char format[5];
    char uformat[6];
} instruction;

typedef struct linesw
{
    char words[10][5];
    int line_number;
    int count;
} linesfilter;

instruction insn[N];
linesfilter linfilT[0xFF];

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

void filter_ins(const char * string,char ** getstring)
{
    if(!strcmp(string,""))
	return ;
    int cambios,i=0;
    int palabras;
    char anterior=0x20;
    char caracter;
    char ** insOPt= arraystring_init(insOPt,1,80);

    /*for(i=0;i<80;i++)
    {
        insOPt[0][i]='H';
    }
    for(i=0;i<strlen(*getstring);i++)
    {
        *getstring[i]='H';
    }*/
    i=0;
    int spccount=0;
    int haveletter=0;
    int j=0;
    //printf("STRRTLEN::::: %d\n",strlen(string));
    for(i=0;i<strlen(string);i++)
    {
        caracter=string[i];
        //printf("CHAR::: %c\n",caracter);
        if(caracter == 0x09)
            caracter=0x20;

        if((caracter==0x20 && anterior==0x20 && haveletter==0))
        {
            continue;
        }
        if((caracter==0x20 && i==strlen(string)-1))
            break;

        if ( caracter!=0x20)
        {
            insOPt[0][j]=caracter;
            j++;
            haveletter=1;
            spccount=0;
        }
        else
        {
            if(spccount<1)
            {
            insOPt[0][j]=caracter;
            spccount++;
            j++;
            }

        }
    }
    if(caracter==0x20)
	{
	    insOPt[0][j-1]='\0';
	}
	printf("INSOPT::: %s\n",insOPt[0]);
    *getstring=insOPt[0];
    //printf("GETSTRING:: %s\n",*getstring);

}

void debug_a_string(const char * string)
{
    int i;
    printf("word::: %s:: ",string);
    for (i=0;i<strlen(string);i++)
        printf("0x%x ",string[i]);
    printf("\n");
}

void view_line_data(const char * string,int y)
{
    int i;
    int word=0;
    int letter=0;
    char caracter;
    char ** data=arraystring_init(data,1,34);
    for(i=0;i<strlen(*data);i++)
    {
        data[0][i]='\0';
    }

    //debug_a_string(*data);
    filter_ins(string,data);

    linfilT[y].count=0;
    //printf("DATA:: %s\n",*data);
    //printf("MyStrlen::: %d\n",strlen(*data));
    for(i=0;i<strlen(*data);i++)
    {
	    caracter=data[0][i];
	    //printf("CHAR::: 0x%x\n",caracter);

	    if(caracter != 0x20)
	    {
	    	linfilT[y].words[word][letter]=caracter;
            letter++;
	    }
	    else
	    {
            letter=0;
            //printf("CWORD:::: %d\n",word);
            word++;
	    }
    }
    linfilT[y].count=word+1;
    //printf("Word:::: %d have %d arguments\n",y,linfilT[y].count);

    /*for(i=0;i<linfilT[y].count;i++)
	    printf("word%d :: %s\n",i,linfilT[y].words[i]);*/
}

void print_nmonics()
{
   int i;
   for (i=0;i<N;i++)
   	printf("%s\t%1X\t%1d\t%s\n",insn[i].inst,
			insn[i].hex_code,insn[i].warguments, insn[i].format);

}

