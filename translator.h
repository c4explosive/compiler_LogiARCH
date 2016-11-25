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

void check_if_has_syntaxe()
{
	int isnmonic=0;
	int i,j;
	char typeA;
	char formM[6];
	for(i=0;i<=Nlines;i++)
	{
	    for(j=0;j<N;j++)
	    	if(strcmp(linfilT[i].words[0],insn[j].inst)==0)
		{
		    isnmonic=1;
		}
	    if(isnmonic)
		printf("%s es nmónico.\n",linfilT[i].words[0]);
	    else
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
	      if(linfilT[i].count-1 == insn[get_code(linfilT[i].words[0])].warguments)
		printf("Número de argumentos para %s están correctos.\n",linfilT[i].words[0]);
	      else
	      {
		   printf("Número de argumentos no validos en %s; abortando...\n",linfilT[i].words[0]);
		   printf("Línea: %d\n",i);
		   exit(1);
	      }
	}
	for(i=0;i<=Nlines;i++)
	{
	   for(j=1;j<=linfilT[i].count;j++)
	   {
		typeA=is_O_E(linfilT[i].words[j]);
		printf("TYPE::: %c\n",typeA);
	   	if(typeA == '?')
			{
				printf("%s no es un registro o inmediato válido, abortando...");
				exit(1);
			}
				
	   }
	}
	printf("Aqui no hay errores.");	

}
void translate(const char string)
{

}
