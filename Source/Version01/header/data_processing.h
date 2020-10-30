#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

/**
 * @param process_index: number of the child process the file belongs to
 * @param line_num: represents the line number of the text from the deconstructed .c file
 * @param text: a string to hold a line of deconstructed text found in the .c file
 */
typedef struct Line
{
    int process_index,line_num;
    char* text;
} Line;
/**
 * @param num_files: total number of files found for a given sorter
 * @param catalog_indices: list of line indices that belong to the files for each sorter
 */
typedef struct Data
{
    int* num_files;
    int** catalog_indices;
} Data;
/**
 * @details retreive all of the files for each sorter from the partial task lists
 * @param num_procs: total number of child processes
 * @param file_count: total number of files in the catalog
 * @param catalog: complete list of paths for every file in the directory
 * @return a partilally reconstruncted string containing the text from each file that was processed from the sorter
 */
void data_processing_build_tasklist (int num_procs, int file_count, char** catalog);
/**
 * @details retreive all of the files for each sorter from the partial task lists
 * @param num_procs: total number of child processes
 * @param file_data: data structure to hold keep track of the number of files in each sorter and the file indices that belong to them
 * @param file_count: total number of files in the catalog
 */
void data_processing_fetch_sorter_data (int num_procs, Data* file_data, int file_count);
/**
 * read a file, store the data from the file into memory
 * @details reads the contents of a file into memory and stores it into a Line struct
 * @param path: path to a file
 * @param ln: array of Line struct that store the contents of each file that is being processed
 */
void data_processing_read_file (char* path, Line* ln);
// /**
//  * @details
//  * @param
//  */
// Line* data_processing_sort_files (Line* lines, int num_lines, int sorter_id);
/**
 * @details compares two objects based off of their line numbers
 * @param x: first object
 * @param y: second object
 * @return an integer between -1 and 1. If -1 or 1, the two objects are not equal. If 0, the two objects are equal
 */
int data_processing_compare (const void* x, const void* y);
#endif

// /**
//  * @param num_lines: total number of files found for a given sorter
//  * @param lines: list of Line structs that are used in sorting
//  */
// typedef struct Sorter
// {
//     int num_lines;
//     Line* lines;
// } Sorter;
// /**
//  * @details TODO
//  * @param lines:
//  * @param ln:
//  */
// void data_processing_add_line (Line** lines, Line ln);
// /**
//  * @details compares two objects based off of their line numbers
//  * @param val1: first object
//  * @param val2: second object
//  * @return
//  */
// char* data_processing_build_path (char* root, char* filename);
