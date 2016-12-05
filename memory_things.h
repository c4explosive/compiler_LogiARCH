char** arraystringTs_init(char ** pstringTs,int i, int j)
{
   int k,l;
   pstringTs=malloc(i*sizeof(char*));
   for (k=0; k<i; k++)
        pstringTs[k]=malloc(j*sizeof(char));
   for(k=0;k<i;k++)
   {
       for(l=0;l<j;l++)
        pstringTs[k][l]='\0';
   }
   return pstringTs;

}
