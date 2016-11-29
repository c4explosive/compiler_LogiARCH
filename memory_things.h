char** arraystring_init(char ** pstring,int i, int j)
{
   int k,l;
   pstring=malloc(i*sizeof(char*));
   for (k=0; k<i; k++)
        pstring[k]=malloc(j*sizeof(char));
   for(k=0;k<i;k++)
   {
       for(l=0;l<j;l++)
        pstring[k][l]='\0';
   }
   return pstring;

}
