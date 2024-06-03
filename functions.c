#include "header_file.h"
#define SWAP(num) \
{ \
	unsigned char* str = (unsigned char*) &(num); \
	for(int i=0;i<2;i++) \
	{ \
		unsigned char temp = str[i]; \
		str[i] = str[3-i]; \
		str[3-i] = temp; \
	} \
}

char Title[50]={0},Artist[50]={0},Album[50]={0},Composer[50]={0},Content[50]={0},Year[4]={0},arr[100],str[5]={0},ch;
int size=0,i,sample_size=0,Version;
Status read_tags(FILE* fptr)
{
	fread(arr,3,1,fptr);
	arr[3] = '\0';
	if(strcmp(arr,"ID3") != 0 )
	{
		printf("Given file name is not a MP3 file\n");
		return e_failure;
	}
	fread(arr,2,1,fptr);
	arr[2] = '\0';
	if( arr[0] == 3 && arr[1] == 00)
	{
		Version = 2;
	}
	fseek(fptr,10,SEEK_SET);
	for( i=1;i<=6;i++)
	{
		fread(str,4,1,fptr);
		size = 0;
		fread(&size,4,1,fptr);
		SWAP(size);
		fseek(fptr,3,SEEK_CUR);
		if( strncmp(str,"TIT2",4) == 0 )
		{
			fread(Title,size-1,1,fptr);
			Title[size-1] = '\0';
		}
		else if( strncmp(str,"TYER",4) == 0 )
		{
			fread(Year,size-1,1,fptr);
			Year[size-1] = '\0';
		}
		else if( strncmp(str,"TALB",4) == 0 )
		{
			fread(Album,size-1,1,fptr);
			Album[size-1] = '\0';
		}
		else if( strncmp(str,"TPE1",4) == 0 )
		{
			fread(Artist,size-1,1,fptr);
			Artist[size-1] = '\0';
		}
		else if( strncmp(str,"TCON",4) == 0 )
		{
			fread(Content,size-1,1,fptr);
			Content[size-1] = '\0';
		}
		else if( strncmp(str,"COMM",4) == 0 )
		{
			fread(Composer,size-1,1,fptr);
			Composer[size-1] = '\0';
		}
	}
	printf("........................................\n");
	printf("MP3 Tag Reader and Editor for ID3 v%d\n",Version);
	printf("........................................\n");
	printf("Title\t :\t %s\nArtist\t :\t %s\nAlbum\t :\t %s\nYear\t :\t %s\nGenre\t :\t %s\nComposer :\t %s\n",Title,Artist,Album,Year,Content,Composer);
	return e_success;
}
Status copy_remain(FILE* src,FILE* des, char* usr_str,char* usr_tag)
{
	fread(arr,10,1,des);
	fwrite(arr,10,1,src);
	for(i=1;i<=6;i++)
	{
		fread(str,4,1,des);
		fwrite(str,4,1,src);
		if( strncmp(str,usr_tag,4) == 0 )
		{

			size = strlen(usr_str);
			int temp_size = size;
			size++;

			SWAP(size);
			fwrite(&size,4,1,src);

			fread(&sample_size,4,1,des);

			fread(arr,3,1,des);
			fwrite(arr,3,1,src);

			fwrite(usr_str,temp_size,1,src);   // size-1

			SWAP(sample_size);


			fseek(des,sample_size-1,SEEK_CUR);

		}
		else
		{ 

			fread(&sample_size,4,1,des);
			fwrite(&sample_size,4,1,src);

			SWAP(sample_size);

			fread(arr,3,1,des);
			fwrite(arr,3,1,src);


			fread(arr,sample_size-1,1,des);
			arr[sample_size-1] = '\0';
			fwrite(arr,sample_size - 1,1,src);

		}

	}
	while ( fread(&ch,1,1,des) > 0 )
	{
		fwrite(&ch,1,1,src);
	}
	fclose(src);
	fclose(des);
	return e_success;


}
