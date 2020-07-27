#include <stdio.h>

struct header
{
	int action;
	long size;
	char filename[512];
};

int main( int argc, char *argv[] )
{
	FILE *input;
	FILE *output;
	int size=13049;
	long fs=0;
	long count=0;
	char inbyte='\0';
	struct header index[256];
	long pos=0;
	char csize[512];
	int d=0;
	int end=0;
	char cmd[512];
	int fpos=0;

	if ( ( input = fopen(argv[0],"rb") ) == NULL ) exit(-1);
	//output=fopen("out.txt","wb");

	fseek(input,0L,SEEK_END);
	fs=ftell(input);
	fseek(input,size,SEEK_SET);

	while ( ! end )
	{
		inbyte='\0';
		fread(&inbyte,1,1,input);

		if ( inbyte == 'A' )
		{
			// ADD
			index[pos].action=0;

			for(d=0;d<3;d++)
				fread(&inbyte,1,1,input);

			inbyte='\0';
			fread(&inbyte,1,1,input);
			
			for(d=0;d<512;d++)
				csize[d]='\0';

			while ( inbyte != 32 )
			{
				csize[count]=inbyte;
				inbyte='\0';
				fread(&inbyte,1,1,input);
				count++;
			}count=0;

			// convert string to number
			index[pos].size=strtol(csize,NULL,10);
			printf("%s %d\n",csize, index[pos].size);

			inbyte='\0';
			fread(&inbyte,1,1,input);

			while ( inbyte != '\n' )
			{
				index[pos].filename[count]=inbyte;
				inbyte='\0';
				fread(&inbyte,1,1,input);
				count++;
			}count=0;

			printf("%d %s %d\n",index[pos].action, index[pos].filename, index[pos].size);

		}
		else if ( inbyte == 'U' )
		{
			// UPDATE
			for(d=0;d<6;d++)
				fread(&inbyte,1,1,input);

			index[pos].action=1;

			inbyte='\0';
			fread(&inbyte,1,1,input);
			
			for(d=0;d<512;d++)
				csize[d]='\0';

			while ( inbyte != 32 )
			{
				csize[count]=inbyte;
				inbyte='\0';
				fread(&inbyte,1,1,input);
				count++;
			}count=0;

			// convert string to number
			index[pos].size=strtol(csize,NULL,10);

			inbyte='\0';
			fread(&inbyte,1,1,input);

			while ( inbyte != '\n' )
			{
				index[pos].filename[count]=inbyte;
				inbyte='\0';
				fread(&inbyte,1,1,input);
				count++;
			}count=0;

			printf("%d %s %d\n",index[pos].action, index[pos].filename, index[pos].size);

		}
		else if ( inbyte == 'D' )
		{
			// DELETE
			for(d=0;d<6;d++)
				fread(&inbyte,1,1,input);

			index[pos].action=2;

			inbyte='\0';
			fread(&inbyte,1,1,input);

			while ( inbyte != '\n' )
			{
				index[pos].filename[count]=inbyte;
				inbyte='\0';
				fread(&inbyte,1,1,input);
				count++;
			}count=0;

			printf("%d %s\n",index[pos].action, index[pos].filename);

		}else{
			while ( inbyte != '\n' )
				fread(&inbyte,1,1,input);
			end=1;
		}
		
		
		pos++;
	}

	for(d=0;d<pos-1;d++)
	{
		if ( index[d].action == 2 )
		{
			strcpy(cmd,"rm ");
			strcat(cmd,index[d].filename);
			printf("Removing %s\n",index[d].filename);
			system(cmd);
		}
		else if ( index[d].action == 0 )
		{
			fpos=0;
			printf("Adding %s with size of %d bytes\n",index[d].filename, index[d].size);
			output=fopen(index[d].filename,"wb");
			while ( fpos < index[d].size )
			{
				inbyte='\0';
				fread(&inbyte,1,1,input);
				fwrite(&inbyte,1,1,output);
				fpos++;
			}	
			fclose(output);
		}
		else if ( index[d].action == 1 )
		{
			strcpy(cmd,"rm ");
			strcat(cmd,index[d].filename);
			printf("Updating %s with size of %d bytes\n",index[d].filename, index[d].size);
			system(cmd);

			fpos=0;
			output=fopen(index[d].filename,"wb");
			while ( fpos < index[d].size )
			{
				inbyte='\0';
				fread(&inbyte,1,1,input);
				fwrite(&inbyte,1,1,output);
				fpos++;
			}	
			fclose(output);

			
		}

	}

	fclose(input);
}