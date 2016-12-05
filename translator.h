int get_code(const char* stringTs)
{
    int i;
    for (i=0;i<N;i++)
    {
	if(strcmp(stringTs,insn[i].inst) == 0)
		return i;
    }
    return -1;
}

char is_O_E(const char * stringTs)
{
    if( strcmp(stringTs,"R1") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R2") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R3") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R4") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R5") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R6") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R7") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R8") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R9") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R10") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R11") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R12") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R13") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R14") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R15") == 0)
	return 'O';
    else if ( strcmp(stringTs,"R0") == 0)
	return 'O';
    else if ( atoi(stringTs) >= 0 && atoi(stringTs) <= 0xFF)
	return 'E';
    else
	return '?';
}

char get_register_nums(const char * stringTs)
{
    if( strcmp(stringTs,"R1") == 0)
	return '1';
    else if ( strcmp(stringTs,"R2") == 0)
	return '2';
    else if ( strcmp(stringTs,"R3") == 0)
	return '3';
    else if ( strcmp(stringTs,"R4") == 0)
	return '4';
    else if ( strcmp(stringTs,"R5") == 0)
	return '5';
    else if ( strcmp(stringTs,"R6") == 0)
	return '6';
    else if ( strcmp(stringTs,"R7") == 0)
	return '7';
    else if ( strcmp(stringTs,"R8") == 0)
	return '8';
    else if ( strcmp(stringTs,"R9") == 0)
	return '9';
    else if ( strcmp(stringTs,"R10") == 0)
	return 'A';
    else if ( strcmp(stringTs,"R11") == 0)
	return 'B';
    else if ( strcmp(stringTs,"R12") == 0)
	return 'C';
    else if ( strcmp(stringTs,"R13") == 0)
	return 'D';
    else if ( strcmp(stringTs,"R14") == 0)
	return 'E';
    else if ( strcmp(stringTs,"R15") == 0)
	return 'F';
    else if ( strcmp(stringTs,"R0") == 0)
	return '0';

}

int replace_REALline(const char * stringTs)
{
    int i;
    char lineS[50];
    char * pch;
    char ** data;
    for(i=0;i<NL2;i++)
    {
        data=arraystringTs_init(data,1,34);
        filter_ins(linebyline2[i],data);
        /*pch=strstr(*data,"SLT");
        if(pch != NULL)
        {
            printf("stringTs:: %s\n",stringTs);
            debug_a_stringTs(stringTs);
            printf("DATAR:: %s\n",*data);
            debug_a_stringTs(*data);
        }*/
        if(strstr(*data,stringTs) != NULL)
        {
            return i+1;
        }

    }
    return -1;
}

void print_lineINLine()
{
    int i;
    for(i=0;i<lINL;i++)
        printf("%d -> %d\n",lineINLINE[1][i],lineINLINE[0][i]);
}


void check_if_has_syntaxe()
{
    //print_lineINLine();
	int isnmonic=0;
	int i,j,k,l;
	char typeA;
	char formM[6];
	char formOW[6];
	int line=0;
	int argNow;
	int argDef;
	char strns[50]="";
	k=0;

	for(i=0;i<=Nlines;i++)
	{

        for(l=0;l<linfilT[i].count;l++)
        {
            if(l!=0)
                sprintf(strns,"%s %s",strns,linfilT[i].words[l]);
            else
                sprintf(strns,"%s%s",strns,linfilT[i].words[l]);
        }
        line=replace_REALline(strns);

	    for(j=0;j<N;j++)
	    	if(strcmp(linfilT[i].words[0],insn[j].inst)==0)
		{
		    isnmonic=1;
		}
	    if (!(isnmonic))
	    {
		printf("Error de syntaxis encontrada. La palabra clave \"%s\" no es válida como nmónico, abortando...\n",
				linfilT[i].words[0]);
		printf("Línea: %d\n",line);
		exit(1);
	    }
	    isnmonic=0;
	    argNow=linfilT[i].count-1;
	    argDef=insn[get_code(linfilT[i].words[0])].warguments;
          //printf("DEBUG:: %d vs %d\n",argNow,argDef);
	      if (!(argNow == argDef))
	      {
		   printf("Número de argumentos no validos en %s; abortando...\n",linfilT[i].words[0]);
		   printf("Línea: %d\n",line);
		   exit(1);
	      }
	      sprintf(strns,"");

	   for(j=1;j<linfilT[i].count;j++)
	   {
		//printf("WORDS::: %s\n",linfilT[i].words[j]);
		typeA=is_O_E(linfilT[i].words[j]);
		formM[k]=typeA;
		k++;
		//printf("TYPE::: %c\n",typeA);

	   }
	   formM[j-1]='\0';
	   //printf("FORMM::: %s\n",formM);
	   sprintf(formOW,insn[get_code(linfilT[i].words[0])].uformat);
	   //printf("FORMOW::: %s\n",formOW);
	   if(strcmp(formM,formOW) !=0)
	   {
		printf("Hay un registro o inmediato no válido, abortando...\n");
		printf("Línea: %d\n",line);
		exit(1);
	   }
	   k=0;
	   sprintf(formM,"");

	}
	printf("Aquí no hay errores.\n");

}

void put_fileheader()
{
    sprintf(data_inHEX,"v2.0 raw\n");
}

void translate()
{
    printf("Nlines:: %d\n",Nlines);
    char ** traduction=arraystringTs_init(traduction,1,5);
    sprintf(traduction[0],"");
    int i,k,h,z;
    h=1;
    char theformins[5];
    char theletter;
    char caractt;
    for(i=0;i<=Nlines;i++)
    {
	sprintf(traduction[0],"%s%X",traduction[0],insn[get_code(linfilT[i].words[0])].hex_code);
	sprintf(theformins,insn[get_code(linfilT[i].words[0])].format);
	//printf("FORM_INS::: %s\n",theformins);
	for(k=0;k<strlen(theformins);k++)
	{
	    theletter=theformins[k];
	    if(theletter=='O')
	    {
		sprintf(traduction[0],"%s%c",traduction[0],get_register_nums(linfilT[i].words[h]));
		h++;
	    }
	    else if(theletter=='E')
	    {
		sprintf(traduction[0],"%s%2X",traduction[0],atoi(linfilT[i].words[h]));
		h++;
	    }
	    else if(theletter=='X')
	    {
		sprintf(traduction[0],"%s%d",traduction[0],0);
	    }
	}

	for(z=0;z<strlen(traduction[0]);z++)
	{
	    caractt=traduction[0][z];
	    //printf("D%d:: 0x%X\n",z,caractt);
	    if(caractt==0x20)
            traduction[0][z]='0';
	}
	//printf("INSS::: %s\n",linfilT[i].words[0]);
	//printf("OVERDRIVE::: %s\n",traduction[0]);
	sprintf(data_inHEX,"%s %s",data_inHEX,traduction[0]);
	h=1;
	k=1;
	sprintf(theformins,"");
	sprintf(traduction[0],"");
    }

}

void fix_O_to_0()
{
    int i;
    char caracter;
    for(i=0;i<strlen(data_inHEX);i++)
    {
        caracter=data_inHEX[i];
        if(caracter == 0x4f)
            data_inHEX[i]=0x30;
    }
}
