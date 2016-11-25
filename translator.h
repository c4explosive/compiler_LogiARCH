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

int get_register_nums(const char * string)
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
	printf("Aqui no hay errores.");	

}
void translate(const char string)
{

}
