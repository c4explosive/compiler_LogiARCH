#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
		char myfuckingstring[]="hyper logic, hyper class, hyper kernel::system\n";
		char * pch;
		pch=strchr(myfuckingstring,0x3a);
		if( pch != NULL)
		{
				printf("%s\n",myfuckingstring);
				printf("String's address: 0x%p\n",myfuckingstring);
				printf("Pointer's address: 0x%p\n",pch);
				printf("The Colon is in position: %d\n",pch-myfuckingstring);
				printf("Char:: %c\n",myfuckingstring[pch-myfuckingstring]);
		}
}
