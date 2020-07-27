#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *input;
	FILE *temp;
	FILE *output;
	long fs=0;
	char inbyte='\0';
	long count=0;
	char name[512];
	char outstring[512];
	int add=0;
	long insize=0;
	long sizecount=0;
	int d=0;

	if ( ( input=fopen(argv[1],"rb") ) == NULL )
	{
		printf("Input file not found\n");
		exit(-1);
	}

	fseek(input,0L,SEEK_END);
	insize=ftell(input);
	fseek(input,0L,SEEK_SET);

	output=fopen("../tempout2","wb");

	while ( sizecount < insize )
	{
		inbyte='\0';
		fread(&inbyte,1,1,input);
		sizecount++;
		count=0;
		
		if ( inbyte == 'A' )
		{
			add=1;
		}else{
			add=0;
		}

		while ( inbyte != 32 )
		{
			inbyte='\0';
			fread(&inbyte,1,1,input);
			sizecount++;
		}

		while ( ( inbyte != '\n' ) && ( ! feof(input) ) )
		{
			inbyte='\0';
			fread(&inbyte,1,1,input);
			sizecount++;
			name[count]=inbyte;
			count++;
		}name[count-1]='\0';

		if ( ( temp=fopen(name,"rb") ) == NULL ){
			printf("Target file not found\n");
			exit(-2);
		}
		fseek(temp,0l,SEEK_END);
		fs=ftell(temp);
		fclose(temp);
		
		for(d=0;d<512;d++)
			outstring[d]='\0';

		if ( add )
		{
			printf("Writing Line \"Add %d %s\"\n",fs,name);
			sprintf(outstring,"Add %d %s\n\0",fs,name);
		}else{
			printf("Writing Line \"Update %d %s\"\n",fs,name);
			sprintf(outstring, "Update %d %s\n\0",fs,name);
		}

		fwrite(&outstring,strlen(outstring),1,output);
		
	}	
		
	fclose(input);
	fclose(output);
}