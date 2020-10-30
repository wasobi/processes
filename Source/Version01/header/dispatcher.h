#ifndef DISPATCHER_H
#define DISPATCHER_H

/**
 * @details converts n files to partial lists, sorts them based off of their line number, then writes the ordered lines to a file
 * @param num_procs: is the number of child processes
 * @param file_count: total number of files in the root directory that contains all data files
 * @param catalog: list of file paths to every file in the root directory
 * @param outfile: name of the file that the output will be written to
 */
void dispatcher_process (int num_procs, int file_count, char** catalog, char* outfile);
/**
 * @details calculates the amount of files that each distributor receives, creates a partial tasklist for it
 * @param num_procs: total number of child processes
 * @param file_count: total number of files found in the directory
 * @param catalog: total number of files from the
 */
void dispatcher_distribute (int num_procs, int file_count, char** catalog);
/**
 * @details creates a list of all file paths for the files in a directory
 * @param file_count: total number of files in the directory
 * @param root: path to the directory containing all of the data files
 * @return array of file paths
 */
char** dispatcher_fetch_catalog (int file_count, char* root);
/**
 * @details check if the file extension is ".txt"
 * @param filename: name of the corresponding file
 * @return TRUE if the file extension is .txt, otherwise FALSE
 */
int dispatcher_is_valid_file (char* filename);
/**
 * @details calculates the number of files in an open directory
 * @param root: path to a directory
 * @return number of files found
 */
int dispatcher_get_file_count (char* root);

#endif
