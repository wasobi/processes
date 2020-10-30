#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/startup.h"
#include "../header/dispatcher.h"

// int main (int argc, char** argv)
// {
//     startup();
// 	if (argc != 3)
// 	{
//         printf("  Usage: %s <dir> <output-file>\n\n",argv[0]);
//         exit (1);
//     }
// 	int file_count = dispatcher_get_file_count(argv[1]);
// 	char** catalog = dispatcher_fetch_catalog(file_count,argv[1]);
// 	dispatcher_process(argv[2],file_count,catalog,argv[3]);
// 	dispatcher_distribute(argv[2],file_count,catalog);
//     printf("\ndone.\n\n");
//     return 0;
// }
//
// // dispatcher_process(2,file_count,catalog,"ouput_v1");
// // dispatcher_process(2,file_count,catalog,"ouput_v1.c");

int main (int argc, char** argv)
{
    startup();
	// int file_count = dispatcher_get_file_count(argv[1]);
	// char** catalog = dispatcher_fetch_catalog(file_count,argv[1]);

	// hard-coded input
    int file_count = 12;
	char* catalog[] =
	{
	"../Data-Sets/Data-Set-1/g3.txt",
	"../Data-Sets/Data-Set-1/g53.txt",
	"../Data-Sets/Data-Set-1/f3.txt",
	"../Data-Sets/Data-Set-1/a43.txt",
	"../Data-Sets/Data-Set-1/f162.txt",
	"../Data-Sets/Data-Set-1/a3.txt",
	"../Data-Sets/Data-Set-1/a23.txt",
	"../Data-Sets/Data-Set-1/g32.txt",
	"../Data-Sets/Data-Set-1/g13.txt",
	"../Data-Sets/Data-Set-1/g8.txt",
	"../Data-Sets/Data-Set-1/f17.txt",
	"../Data-Sets/Data-Set-1/h35.txt"};
	// printf("\n\t[catalog]\n\n");
	// for (int i=0; i<file_count; i++)
	// {
	// 	printf("\t  + %s\n",catalog[i]);
	// }
	printf("\n\t...............\n\n");
	// dispatcher_process(argv[2],file_count,catalog,argv[3]);
	// dispatcher_distribute(2,file_count,catalog);
	// dispatcher_process(2,file_count,catalog,"ouput_v1");
	dispatcher_process(2,file_count,catalog,"ouput_v1.c");
    printf("\ndone.\n\n");
    return 0;
}

// /*    char* folderPath = "./Data-Sets/Data-Set-1/";
//  	//	build file list
//  	//	file_list is list of full paths to data files, e.g.  "./DataSets/Data-Set-1/f23.txt"
//     int file_count = dispatcher_get_file_count(root);
//     // allocate memory for an array that will hold all files in the directory
//     char** file_list = dispatcher_open_directory(file_count,root);
// */
