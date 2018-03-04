#pragma once

#include    <iostream>
#include    <string>
#include    <mpi.h>

using namespace std;

/**
*  Common part
*/

/***************************************************/
#define MAX_LENGTH	    512

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
int count_word(string text, string word);

/***************************************************/
