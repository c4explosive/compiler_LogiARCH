

typedef struct linesw
{
    char words[10][5];
    int line_number;
    int count;
} linesfilter;


linesfilter linfilT[0xFF];
linesfilter *MlinfilT[0xFF]; //For mirror linfilT data (NEED INITIALIZIED)

int count_words(const char * stringTs)
{
    /*printf("LAST LETTER: 0x%X\n",stringTs[strlen(stringTs)-1]);*/
    if(!strcmp(stringTs,""))
	return 0;
    int cambios,i=0;
    int palabras;
    char anterior=0x20;
    char caracter;

    for(i=0;i<strlen(stringTs);i++)
    {
	caracter=stringTs[i];
	if(caracter == 0x09)
	    caracter=0x20;
	if(caracter == 0x20 && anterior != 0x20)
	   cambios++;
	anterior=caracter;
    }
    caracter=stringTs[strlen(stringTs)-1];
    if(caracter==0x20 || caracter==0x09)
	cambios--;

    palabras=cambios+1;
    return palabras;

}

void filter_ins(const char * stringTs,char ** getstringTs)
{
    if(!strcmp(stringTs,""))
	return ;
    int cambios,i=0;
    int palabras;
    char anterior=0x20;
    char caracter;
    char ** insOPt= arraystringTs_init(insOPt,1,80);

    /*for(i=0;i<80;i++)
    {
        insOPt[0][i]='H';
    }
    for(i=0;i<strlen(*getstringTs);i++)
    {
        *getstringTs[i]='H';
    }*/
    i=0;
    int spccount=0;
    int haveletter=0;
    int j=0;
    //printf("STRRTLEN::::: %d\n",strlen(stringTs));
    for(i=0;i<strlen(stringTs);i++)
    {
        caracter=stringTs[i];
        //printf("CHAR::: %c\n",caracter);
        if(caracter == 0x09)
            caracter=0x20;

        if((caracter==0x20 && anterior==0x20 && haveletter==0))
        {
            continue;
        }
        if((caracter==0x20 && i==strlen(stringTs)-1))
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

	  if (insOPt[0][j-1] == 0x20)
            insOPt[0][j-1]='\0';
    //printf("UCHAR:: 0x%x\n",insOPt[0][j-1]);
    //printf("INSOPT::: %s\n",insOPt[0]);
	//debug_a_stringTs(insOPt[0]);
    *getstringTs=insOPt[0];
    //printf("GETstringTs:: %s\n",*getstringTs);

}

void debug_a_stringTs(const char * stringTs)
{
    int i;
    printf("word::: %s\n",stringTs);
    for (i=0;i<strlen(stringTs);i++)
        printf("0x%x ",stringTs[i]);
    printf("\n");
}


void view_line_data(const char * stringTs,int y, int mode)
{
    int i;
    int word=0;
    int letter=0;
    char caracter;
    char ** data=arraystringTs_init(data,1,34);
    filter_ins(stringTs,data);
    if(mode == 0)
        linfilT[y].count=0;
    else
    {
        for(i=0;i<200;i++) //rm data in this line for copy new data
            linebyline[y][i]='\0';
    }
    //printf("stringTs & Data:: %s & %s\n",stringTs,*data);
    //debug_a_stringTs(stringTs);
    //debug_a_stringTs(*data);

    //printf("MyStrlen::: %d\n",strlen(*data));
    for(i=0;i<strlen(*data);i++)
    {
	    caracter=data[0][i];
	    //printf("CHAR::: 0x%x\n",caracter);

	    if(mode == 1)
        {
            linebyline[y][letter]=caracter;
            letter++;
        }
        else
	    {
            if(caracter != 0x20)
            {
                if(mode==0)
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
    }
    if (mode==0)
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

