void check_if_has_syntaxe()
{
	int isnmonic=0;
	int i,j;
	for(i=0;i<2;i++)
	{
	    for(j=0;j<N;j++)
	    	if(strcmp(linfilT[i].words[0],insn[j].inst)==0)
		{
		    isnmonic=1;
		}
	    if(isnmonic)
		printf("%s is nmonic.\n",linfilT[i].words[0]);
	    else
	    {
		printf("Not valid syntax found. Keyword \"%s\" is Not valid as nmonic, aborting...",
				linfilT[i].words[0]);
		exit(1);
	    }
	    isnmonic=0;
	}

}
void translate(const char string)
{

}
