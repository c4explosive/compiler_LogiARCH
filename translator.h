int get_code(const char* string)
{
    int i;
    for (i=0;i<N;i++)
    {
	if(strcmp(string,insn[i].inst) == 0)
		return i;
    }
    return -1;
}

char is_O_E(const char * string)
{
    if( strcmp(string,"R1") == 0)
	return 'O';
    else if ( strcmp(string,"R2") == 0)
	return 'O';
    else if ( strcmp(string,"R3") == 0)
	return 'O';
    else if ( strcmp(string,"R4") == 0)
	return 'O';
    else if ( strcmp(string,"R5") == 0)
	return 'O';
    else if ( strcmp(string,"R6") == 0)
	return 'O';
    else if ( strcmp(string,"R7") == 0)
	return 'O';
    else if ( strcmp(string,"R8") == 0)
	return 'O';
    else if ( strcmp(string,"R9") == 0)
	return 'O';
    else if ( strcmp(string,"R10") == 0)
	return 'O';
    else if ( strcmp(string,"R11") == 0)
	return 'O';
    else if ( strcmp(string,"R12") == 0)
	return 'O';
    else if ( strcmp(string,"R13") == 0)
	return 'O';
    else if ( strcmp(string,"R14") == 0)
	return 'O';
    else if ( strcmp(string,"R15") == 0)
	return 'O';
    else if ( strcmp(string,"R0") == 0)
	return 'O';
    else if ( atoi(string) >= 0 && atoi(string) <= 0xFF)
	return 'E';
    else
	return '?';
}

char get_register_nums(const char * string)
{
    if( strcmp(string,"R1") == 0)
	return '1';
    else if ( strcmp(string,"R2") == 0)
	return '2';
    else if ( strcmp(string,"R3") == 0)
	return '3';
    else if ( strcmp(string,"R4") == 0)
	return '4';
    else if ( strcmp(string,"R5") == 0)
	return '5';
    else if ( strcmp(string,"R6") == 0)
	return '6';
    else if ( strcmp(string,"R7") == 0)
	return '7';
    else if ( strcmp(string,"R8") == 0)
	return '8';
    else if ( strcmp(string,"R9") == 0)
	return '9';
    else if ( strcmp(string,"R10") == 0)
	return 'A';
    else if ( strcmp(string,"R11") == 0)
	return 'B';
    else if ( strcmp(string,"R12") == 0)
	return 'C';
    else if ( strcmp(string,"R13") == 0)
	return 'D';
    else if ( strcmp(string,"R14") == 0)
	return 'E';
    else if ( strcmp(string,"R15") == 0)
	return 'F';
    else if ( strcmp(string,"R0") == 0)
	return 'O';
 
}



void check_if_has_syntaxe()
{
	int isnmonic=0;
	int i,j,k;
	char typeA;
	char formM[6];
	char formOW[6];
	k=0;
	for(i=0;i<=Nlines;i++)
	{
	    for(j=0;j<N;j++)
	    	if(strcmp(linfilT[i].words[0],insn[j].inst)==0)
		{
		    isnmonic=1;
		}
	    if (!(isnmonic))
	    {
		printf("Error de sysntaxis encontrada. La palabra clave \"%s\" no es válida como nmónico, abortando...\n",
				linfilT[i].words[0]);
		printf("Línea: %d\n",i);
		exit(1);
	    }
	    isnmonic=0;
	}
	for(i=0;i<=Nlines;i++)
	{
	      if (!(linfilT[i].count-1 == insn[get_code(linfilT[i].words[0])].warguments))
	      {
		   printf("Número de argumentos no validos en %s; abortando...\n",linfilT[i].words[0]);
		   printf("Línea: %d\n",i);
		   exit(1);
	      }
	}
	for(i=0;i<=Nlines;i++)
	{
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
		printf("Línea: %d\n",i);
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
    char ** traduction=arraystring_init(traduction,1,5);
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
