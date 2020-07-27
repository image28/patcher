// Image28:
// While this program is attached to a file, the file can be moved/deleted/renamed and still remain accessible through
// the proc filesystem 

#include <stdio.h>   /* Standard input/output voidinitions */
#include <string.h>  /* String function voidinitions */
#include <unistd.h>  /* UNIX standard function voidinitions */

int main(int argc, char *argv[])
{
	FILE *input;
	char wait[1024];
	int done=0;

	if ( (input=fopen(argv[1],"rb")) != NULL )
	{
		while(!done)
		{
			scanf("%s",wait);
			if ( strncmp(wait,"exit",4) == 0 )
			{
				done=1;
			}
		}
	}

	printf("File hold released");
	return(0);
}