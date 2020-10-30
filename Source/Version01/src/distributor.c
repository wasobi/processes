#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/distributor.h"


void distributor_build_task_list (int distr_id, int num_procs, char** catalog, int start, int end)
{
    int* num_files_found = (int*) calloc(num_procs, sizeof(int));
    int** file_index_lists = (int**) calloc(num_procs, sizeof(int*));
    printf("\t[distributor %d]\n\t\tstart: %d\tend: %d\n",distr_id,start,end);
    for (int i = start; i <= end; i++)
    {
    	FILE* fp = fopen(catalog[i],"r");
    	if(fp==NULL)
        {
    		printf("file not found: %s\n",catalog[i]);
    		exit(11);
    	}
        int process_index;
        fscanf(fp,"%d",&process_index);
        distributor_add_element_to_list(file_index_lists+process_index,num_files_found[process_index],i);
        num_files_found[process_index]++;
        // printf("\t%d \t--> %s \t--> for sorter %d\n", i,catalog[i],process_index);
        fclose(fp);
    }
    distributor_write_tasklist_to_file(distr_id,num_procs,num_files_found,file_index_lists);
}
char* distributor_build_path (int distr_id)
{
    // char* root = "/tmp/CSC412_prog04/distr_";
    char* root = "/tmp/CSC412_prog04_distr_";
    int digits = distributor_count_digits(distr_id);
    char* path = (char*) calloc((strlen(root)+digits+4),sizeof(char));
    sprintf(path,"%s%d.txt",root,distr_id);
    free(path);
    return path;
}
void distributor_write_tasklist_to_file (int distr_id, int num_procs, int* num_files, int** file_indices)
{
    char* outpath = distributor_build_path(distr_id);
    printf("\t\tpath to output file: %s\n",outpath);
    FILE* outfile = fopen(outpath,"w");
    if(outfile==NULL)
    {
    		printf("file not found: %s\n",outpath);
    		exit(11);
    }
    for (int i = 0; i < num_procs; i++)
    {
        fprintf(outfile,"%d",num_files[i]);
        for (int j = 0; j < num_files[i]; j++)
        {
            fprintf(outfile," %d",file_indices[i][j]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);
}
void distributor_add_element_to_list (int** list, int size, int element)
{
	int* temp = (int*) calloc(size+1,sizeof(int));
    // copy the items from the original list to the temporary list
	for(int i = 0; i < size; i++)
    {
        temp[i] = (*list)[i];
    }
    // add the new element to the last index of the list
	temp[size] = element;
	if (*list != NULL)
    {
        free(*list);
    }
    // free memory for list and update it to include the new element
	*list = temp;
}
int distributor_count_digits (int num)
{
    if (num < 10)
    {
        return 1;
    }
    else if (num < 100)
    {
        return 2;
    }
    else if (num < 1000)
    {
        return 3;
    }
    else if (num < 10000)
    {
        return 4;
    }
    else if (num < 100000)
    {
        return 5;
    }
    else
    {
        return 0;
    }
}
