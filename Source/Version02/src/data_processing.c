#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include "../header/data_processing.h"
#include "../header/distributor.h"

// creates n child processes
// fetches sorter data from each distributor file
// sorts the lines
// concatenates the lines in order
// return the line back to the parent to be stored in the 2-d array
void data_processing_build_tasklist (int num_procs, int file_count, char** catalog)
{
    Data file_data;
    // Sorter* sorter_list = (Sorter*) calloc(num_procs,sizeof(Sorter));
    printf("\t\tfetching tasks from dispatcher...\n\n");
    data_processing_fetch_sorter_data(num_procs,&file_data,file_count);

    for (int i = 0; i < num_procs; i++)
    {
        int p = fork();
        if (p == 0)
        {
            printf("\t-----> number of files: %d\n",file_data.num_files[i]);
            Line* lines = (Line*) calloc(file_data.num_files[i],sizeof(Line));

            for (int j = 0; j < file_data.num_files[i]; j++)
            {
                Line ln;
                char* path = catalog[file_data.catalog_indices[i][j]];
                // open each file
                data_processing_read_file(path,&ln);
                // save data to list
                lines[j] = ln;
            }
            // printf("\t-----> number of files: %d\n",file_data.num_files[i]);
            // sort by line number
            qsort(lines,file_data.num_files[i],sizeof(Line),data_processing_compare);
            // write results to output file
            char* root = "../sorter_";
            int digits = distributor_count_digits(i);
            char* path = (char*) calloc((strlen(root)+digits+4),sizeof(char));
            sprintf(path,"%s%d.txt",root,sorter_id);
            FILE* fp = fopen(path,"w");
            if(fp == NULL)
            {
            		printf("file not found: %s\n",path);
            		exit(11);
            }
            for (int i = 0; i < num_lines; i++)
            {
                fprintf(fp,"%d %s\n",lines[i].line_num,lines[i].text);
            }
            exit(1);
        }
        else
        {
            waitpid(p);
        }
    }
}
void data_processing_fetch_sorter_data (int num_procs, Data* file_data, int file_count)
{
    file_data->num_files = (int*) calloc(num_procs, sizeof(int));
    file_data->catalog_indices = (int**) calloc(num_procs, sizeof(int*));
    int* current_file_index = (int*) calloc(num_procs,sizeof(int));
    for (int i=0; i<num_procs; i++)
    {
    	file_data->catalog_indices[i] = (int*) calloc(file_count,sizeof(int));
    }
    for (int i = 0; i < num_procs; i++) // files
    {
    	char* path = distributor_build_path(i);
    	FILE* fp = fopen(path,"r");
        if (fp == NULL)
    	{
    		printf("\tERROR: Failed to load file \"%s\"\n\n",path);
    		exit(1);
        }
        printf("\t\t>> retrieving data from --> %s\n",path);
    	for (int j = 0; j < num_procs; j++) // lines in the file
        {
    		// read an int num  -> number of files seen by distributor i for sorter j
    		// read into fileList[j]
            int num;
            fscanf(fp,"%d",&num);
    		for (int k = 0; k < num; k++) // rows
            {
                // fileList[j][numFiles[j]+k] is the file index
    			fscanf(fp,"%d",file_data->catalog_indices[j] + current_file_index[j]);
                current_file_index[j]++;
    		}
    		file_data->num_files[j] += num;
    	}
    	fclose(fp);
    }
    printf("\n\t+ all messages read.\n\n");
}
void data_processing_read_file (char* path, Line* ln)
{
    FILE* fp = fopen(path,"r");
    if (fp == NULL)
	{
		printf("\tERROR: Failed to load file \"%s\"\n\n", path);
		exit(1);
    }
    // using fgets()
    ln->text = (char*) calloc(2000,sizeof(char));
    fscanf(fp,"%d %d",&(ln->process_index),&(ln->line_num));
    fgets(ln->text,2000,fp);

    // char BUFF[2000];
    // fscanf(fp,"%d %d %[^\n]",&(ln->process_index),&(ln->line_num),BUFF);
    // getc(fp);
    // // allocate memory for the file text and read the data into it
    // ln->text = (char*) calloc(strlen(BUFF)+1,sizeof(char));
    // strcpy(ln->text,BUFF);
    printf("\t%d\t%s\n",ln->line_num,ln->text);
    fclose(fp);
}
// void data_processing_sort_files (Line* lines, int num_lines, int sorter_id)
// {
//
//     // return lines;
//     // char* root = "../sorter_";
//     // int digits = distributor_count_digits(sorter_id);
//     // char* path = (char*) calloc((strlen(root)+digits+4),sizeof(char));
//     // sprintf(path,"%s%d.txt",root,sorter_id);
//     // free(path);
//     // FILE* fp = fopen(path,"w");
//     // if(fp == NULL)
//     // {
//     // 		printf("file not found: %s\n",path);
//     // 		exit(11);
//     // }
//     // for (int i = 0; i < num_lines; i++)
//     // {
//     //     fprintf(fp,"%d %s\n",lines[i]->line_num,lines[i]->text);
//     // }
// }
int data_processing_compare (const void* x, const void* y)
{
    Line* ln1 = (Line*) x;
	Line* ln2 = (Line*) y;
	int result = (ln1->line_num - ln2->line_num);
    return result;
}
// void data_processing_add_line (Line** lines, Line ln)
// {
//     int size = strlen(ln.text);
// 	Line* temp = (Line*) calloc(strlen(ln.text),sizeof(Line));
//     // copy the items from the original list to the temporary list
// 	for(int i = 0; i < size; i++)
//     {
//         temp[i] = (*lines)[i];
//     }
//     // add the new line to the last index of the list
// 	temp[size] = ln;
// 	if (*lines != NULL)
//     {
//         free(*lines);
//     }
//     // free memory for list and update it to include the new line
// 	*lines = temp;
// }

// void data_processing_read_message (int num_procs, int*** sorter_data, char* outfile)
// {
//     FILE* fp = fopen(outfile,"r");
//     assert(outfile!=NULL); // path should never be null
//     if (fp == NULL)
// 	{
// 		printf("\tERROR: Failed to load file \"%s\"\n\n", outfile);
// 		exit(1);
//     }
//     int** sdata = (int**) calloc(num_procs,sizeof(int*));
//     int m = 0;
//     int n = 0;
//     fscanf(fp,"%d",&n);
//     while (!feof(fp))
//     {
//         int j = 0;
//         printf("\t[number of files]: %d\n", n);
//         fscanf(fp,"%d",&n);
//         sdata[m] = (int*) calloc(n,sizeof(int));
//         for (int i = 0; i < n; i++)
//         {
//             fscanf(fp,"%d",&(sdata[i][j]));
//             printf("\t\tindex --> %d\n", sdata[i][j]);
//             j++;
//         }
//         *(sorter_data[m]) = sdata[m];
//         m++;
//     }
//
//     fclose(fp);
//
// }


// int** data_processing_fetch_sorter_data (int num_procs, int*** file_data)
// {
//     char* root_messages = "/tmp/CSC412_prog04";
//     DIR* dir = opendir(root_messages);
//     if (dir == NULL)
//     {
//         puts("  Unable to read directory");
//         printf("  ERROR: Folder %s not found\n", root_messages);
//         exit(1);
//     }
//     int** sorter_data = (int**) calloc(num_procs,sizeof(int*));
//     struct dirent* record;
//     while ((record = readdir(dir)) != NULL)
//     {
//         char* extension = strchr(record->d_name,'.');
//         if ((record->d_name[0] != '.') && (record->d_type == DT_REG))
//         {
//             if (strcmp(extension,".txt") == 0 && record->d_name[strlen(record->d_name)-3]=='t')
//             {
//                 char* path = data_processing_build_path(root_messages,record->d_name);
//                 data_processing_read_message(num_procs,&sorter_data,path);
//             }
//         }
//     }
//     return sorter_data;
//     // for (int i = 0; i < num_procs; i++)
//     // {
//     //     Line ln;
//     //     char* path = data_processing_build_path(root_messages,record->d_name);
//     //     printf("\t\t--> path: %s\n",path);
//     //     data_processing_read_file(sorter_id,path,&ln);
//     // }
//     // printf("\t+ %d assigned to sorter %d.\n\n",sorter->num_lines,sorter_id);
//     // closedir(dir);
// }


// for (int j = 0; j < strlen(sdata[i]); j++)
        // {
        //     // sscanf(sdata[i][j],"%d ",sorter_data[i][j]);
        //     *(sorter_data[i][j]) = atoi(sdata[i][j]);
        // }

        // char c;
        // int num;
        // int j = 0;
        // while (c != '\n' && getw(fp) != "EOF")
        // {
        //     num = getw(fp);
        //     *(sorter_data[i][j]) = num;
        // }





// while (fscanf(fp,"%d",&size))
// {
//     int* sdata = calloc(size,sizeof(int));
//     for (int i = 0; i < size; i++)
//     {
//         fscanf(fp,"%d",&(sdata[i]));
//     }
//     *(sorter_data[i]) = sdata;
//     i++;
//     free(sdata);
// }

// for (unsigned int i = 0; i < num_procs; i++)
// {

//     // create col
//     *(sorter_data[i]) = (int*) calloc(img.width+1, sizeof(char)); // QUESTION: should we do brackets?
//     //read in each line character by character
//     for (unsigned int j=0; j<img.width; j++)
//     {
//         fscanf(fp, "%c", &(img.characters[i][j]));
//     }
//     char eol;
//     // consume the last character
//     fscanf(fp,"%c", &eol);
// }





// void data_processing_read_file (int sorter_id, char* path, Line* ln)
// {
//     FILE* fp = fopen(path,"r");
//     assert(path!=NULL); // path should never be null
//     if (fp == NULL)
// 	{
// 		printf("\tERROR: Failed to load file \"%s\"\n\n", path);
// 		exit(1);
//     }
//     int process_index;
//     fscanf(fp,"%d",&process_index);
//     printf("\tprocess id: %d\t sorter id: %d\n\n",process_index,sorter_id);
//     assert(process_index==sorter_id); // process index and sorter_id should be equivalent
//     if (sorter_id == process_index){
//         char line[1024];
//         fscanf(fp,"%u%u %[^\n]",&(ln->process_index),&(ln->line_num),line);
//         getc(fp);
//         // allocate memory for the file text and read the data into it
//         ln->text = (char*) calloc(strlen(line)+1,sizeof(char));
//         strcpy(ln->text,line);
//         printf("\t%u %u\t%s\n\n", ln->process_index, ln->line_num, ln->text);
//     }
//     fclose(fp);
// }
