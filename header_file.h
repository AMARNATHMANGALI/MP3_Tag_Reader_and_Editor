#ifndef HEADER_FILE
#define HEADER_FILE
#include<stdio.h>
#include<string.h>
typedef enum
{
        e_failure,
        e_success,
}Status;

Status read_tags(FILE* fptr);
Status copy_remain(FILE* src,FILE* des, char* usr_str,char* usr_tag);

#endif
