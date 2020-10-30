#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

/**
 * @details records the number of files found that belong to each sorter and records theie file indices from the catolog
 * @param distr_id: represents the nth child process, which is one of n distributors
 * @param num_procs: total number of child processes
 * @param catalog: list of file paths for every file in the root directory
 * @param start: index of the first element in the catalog that is assigned to the nth distributor
 * @param end: the final index of the element in the catatlog that is assigned to the nth distributor
 */
void distributor_build_task_list (int distr_id, int num_procs, char** catalog, int start, int end);
/**
 * @details constructs the path for a file that will store the partial tasklist for the nth distributor
 * @param distr_id: represents the nth child process and is used to create a unique file name for the distributor's output
 * @return a character array that stores the final path of the output file
 */
char* distributor_build_path (int distr_id);
/**
 * @details writes that partial tasklist to a file that is uniquely identified by the distr_id
 * @param distr_id: represents the nth child process and is used to create a unique file name for the distributor's output
 * @param num_procs: total number of child processes
 * @param num_files: array that stores the number of files that were found for each distributor
 * @param file_indices: 2-d array that stores the index of the file path from the catalog for each file that the distributor receives
 */
void distributor_write_tasklist_to_file (int distr_id, int num_procs, int* num_files, int** file_indices);
/**
 * @details allocates memory and adds an item to the tasklist
 * @param list: 2-d array that holds the partial tasks lists for n distributors
 * @param size: number of elements in the original list
 * @param element: item that will be added to the list
 */
void distributor_add_element_to_list (int** list, int size, int element);
/**
 * @details count the digits in a number
 * @param num: positive integer
 * @return the number of digits in the positive integer
 */
int distributor_count_digits (int num);

#endif
