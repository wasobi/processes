#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include "../header/dispatcher.h"
#include "../header/distributor.h"
#include "../header/data_processing.h"

#define TRUE 1
#define FALSE 0

void dispatcher_process (int num_procs, int file_count, char** catalog, char* outfile)
{
    printf("\t+ distributing files to child processes...\n\n");
    dispatcher_distribute (num_procs,file_count,catalog);
    unsigned long outfile_len = strlen(outfile); // fixed
    char* ext = strrchr(outfile,'.');
    if (strcmp(ext,".c") == 0)
    {
         char* temp = (char*) calloc(outfile_len+2,sizeof(char));
         strcat(temp,outfile);
         strcat(temp,".c");
    }
    printf("\t...............\n\n");
    printf("\t+ retreiving messages from the distributors...\n\n");
    data_processing_build_tasklist(num_procs,file_count,catalog);
    // // write sorted data to .c file
    // FILE* output = fopen(outfile,"w");
    // for (int i = 0; i < num_procs; i ++)
    // {
    //     char* path = distributor_build_path(i);
    //     FILE* fp = fopen(path,"w");
    //     char* line = (char*) calloc(2000,sizeof(char));
    //     fscanf(fp,"%[^\n]",&line)
    //     fprintf(output,"%s",line);
    // }
    // fclose(fp);
}
void dispatcher_distribute (int num_procs, int file_count, char** catalog)
{
    int n = file_count/num_procs;
    int r = file_count%num_procs;
    int start = 0;
    int end = n-1;
    printf("\tnumber of child processes: %d\n\trange (n) = %d\n\tremainder (r) = %d\n\n",num_procs,n,r);
    // create a distributor for each set of files
    for (int i = 0; i < num_procs; i++)
    {
        // the first r processes receive an additional file
        if (i < r)
        {
            end++;
        }
        //	Version 2
        //	p = fork();
        //	if (p==0)
        distributor_build_task_list(i,num_procs,catalog,start,end);
        // increment your start and end index by the range
        start = end + 1;
        end = start + n - 1;
    }
}
char** dispatcher_fetch_catalog (int file_count, char* root)
{
    printf("+ opening directory...\n\n");
    DIR* dir = opendir(root);
    if (dir == NULL)
    {
        puts("  Unable to read directory");
		printf("  ERROR: Folder %s not found\n", root);
		exit(1);
	}
    struct dirent* record;
    if ((record = readdir(dir)) == NULL)
    {
        puts("  Folder is empty");
		exit(1);
	}
	unsigned long root_len = strlen(root); // fixed
    if (root[root_len-1] == '/')
    {
         root[root_len-1] = '\0';
         root_len--;
    }
    unsigned int i = 0;
    char** catalog = (char**) calloc(file_count,sizeof(char*));
    // search for the files in the current directory
    while ((record = readdir(dir)) != NULL)
    {
        if ((record->d_name[0] != '.') && (record->d_type == DT_REG))
        {
            if (dispatcher_is_valid_file(record->d_name) == TRUE)
            {
                catalog[i] = (char*) calloc(strlen(record->d_name) + root_len + 2,sizeof(char));
                printf(catalog[i], "%s/%s", root, record->d_name);
            }
        }
    }
    printf("+ closing directory.\n\n");
    closedir(dir);
    return catalog;
}
int dispatcher_is_valid_file (char* filename)
{
    char* extension = strchr(filename,'.');
    if (strcmp(extension,".txt") == 0 && filename[strlen(filename)-3]=='t')
    {
            return TRUE;
    }
    return FALSE;
}
int dispatcher_get_file_count (char* root)
{
    int count = 0;
    struct dirent* file;
    DIR* dir = opendir(root);
    while ((file = readdir(dir)) != NULL)
    {
        if ((file->d_name[0] != '.') && (file->d_type == DT_REG))
        {   if (dispatcher_is_valid_file(file->d_name) == TRUE)
			    count++;
        }
    }
	closedir(dir);
    printf("  [%d files found]\n\n", count);
    return count;
}
