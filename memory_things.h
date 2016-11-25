char** arraystring_init(char ** pstring,int i, int j)
{
   int k;
   pstring=malloc(i*sizeof(char*));
   for (k=0; k<i; k++)
	pstring[k]=malloc(j*sizeof(char));
   return pstring;
}
