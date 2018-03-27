#pragma once

#include    <iostream>
#include    <string>
#include    <mpi.h>
#include    <dirent.h>
#include	<vector>
#include	<algorithm>
#include	<fstream>

using namespace std;

/**
 *  Common part
 */

/***************************************************/
#define MAX_LENGTH			512
#define CHUCK				1024
#define MAX_SIZE_PROC		15

struct _file_structure {
	char path[MAX_LENGTH];
	char word[MAX_LENGTH];
};

MPI_Datatype register_file_structure_struct();
void free_file_structure_struct(MPI_Datatype arg);

/***************************************************/

/**
 *  Z Algorithm
 * 	Source: https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
 */

/***************************************************/

void get_z_array(string text, int *Z);
int count_word(string file, string word);

/***************************************************/

/**
 *  Dirent
 */
/***************************************************/

struct _file_information {
	char name[MAX_LENGTH];
	int size;
};

vector<_file_information> get_files_from_directory(char *directory_path);
int get_size_of_file(char *path);

/***************************************************/