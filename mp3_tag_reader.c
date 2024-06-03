#include "header_file.h"
int main(int argc,char* argv[])
{
	if(argc == 1)
	{
		printf("Please pass valid either -t,-T,-a,-A,-y,-c,-g,-h,-v and mp3 file name\n");
		return 0;
	}
	char Version[3]={0};
	if ((strcmp("--help",argv[1] )) == 0 )
	{
		printf("usage: mp3tag -[tTaAycg] ""value"" file1\n\tmp3tag -v\n-t\tModifies a Title tag\n-T\tModifies a Track tag\n-a\tModifies an Artist tag\n-A\tModifies an album tag\n-y\tModifies a Year tag\n-c\tModifies a Comment tag\n-g\tModifies a Genre tag\n-h\tDisplays this help info\n-v\tPrints version info\n");
		return 0;
	}
	if( strcmp("-v",argv[1]) == 0 )
	{
		if(argv[2] == 0 )
		{
			printf("Please pass filename\n");
			return 0;
		}
		FILE* fptr = fopen(argv[2],"r");
		if (fptr == NULL)
		{
			printf("Unable to open file\n");
			return 0;
		}
		if( read_tags(fptr) == e_failure)
		{
			printf("Read tags function failure\n");

		}
		else
		{
			printf("Reading tags successfully done\n");
		}
		fclose(fptr);

	}
	if(strcmp("-e",argv[1] ) == 0 )
	{
		if(argv[3] == 0)
		{
			printf("Please pass new tag to edit\n");
			return 0;
		}
		if( argv[4] == 0)
		{
			printf("Please pass song name\n");
			return 0;
		}
		if(argv[2] == 0)
		{
			printf("Please pass option to edit\n");
			return 0;
		}
		char arr[5],str[150];
		unsigned char length[4];
		int size=0;
		FILE* sample = fopen(argv[4],"r");
		FILE* fp = fopen("temp.mp3","w");
		if(fp == NULL)
		{
			return 0;
		}
		strcpy(str,argv[3]);

		if( strcmp("-t",argv[2]) == 0)
		{
			strcpy(arr,"TIT2");
			printf("You choosed to edit Title tag\n");
		}
		/*else if(strcmp("-T",argv[2]) == 0)
		  {
		  strcpy(arr,"");
		  printf("You choosed to edit Title tag\n");

		  }*/
		else if(strcmp("-a",argv[2]) == 0)
		{
			strcpy(arr,"TPE1");

			printf("You choosed to edit Track tag\n");
		}
		else if(strcmp("-A",argv[2]) == 0)
		{
			strcpy(arr,"TALB");
			printf("You choosed to edit Album tag\n");
		}
		else if(strcmp("-y",argv[2]) == 0)
		{
			strcpy(arr,"TYER");
			printf("You choosed to edit Year tag\n");
		}
		else if(strcmp("-c",argv[2]) == 0)
		{
			strcpy(arr,"COMM");
			printf("You choosed to edit Comment tag\n");
		}
		else if(strcmp("-g",argv[2]) == 0)
		{
			strcpy(arr,"TCON");
			printf("You choosed to edit Genre tag\n");
		}
		else
		{
			printf("Please pass valid argument to edit\n");
			return 0;
		}
		if(copy_remain(fp,sample,str,arr) == e_success)
		{
			printf("Successfully changed the tag\n");
		}

	}
	return 0;
}

