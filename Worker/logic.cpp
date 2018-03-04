#include	"stdafx.h"
#include	"logic.h"

/**
*  Common part
*/

/***************************************************/

MPI_Datatype register_file_structure_struct() {
	struct _file_structure arg;
	MPI_Datatype structtype;
	MPI_Datatype types[] = {
		MPI_CHAR,
		MPI_CHAR
	};
	int blocklen[] = {
		MAX_LENGTH,
		MAX_LENGTH
	};
	MPI_Aint disp[] = {
		(char *)arg.path - (char *)&arg,
		(char *)arg.word - (char *)&arg
	};
	MPI_Type_create_struct(2, blocklen, disp, types, &structtype);
	MPI_Type_commit(&structtype);

	return structtype;
}

void free_file_structure_struct(MPI_Datatype arg) {
	MPI_Type_free(&arg);
}

/***************************************************/

/**
*  Z Algorithm
* 	Source: https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
*/

/***************************************************/
void get_z_array(string text, int *Z) {
	int len = text.length();
	int L = 0, R = 0, k = 0;
	int iterator = 0;

	for (iterator = 1; iterator < len; ++iterator) {
		if (iterator > R) {
			L = R = iterator;
			while ((R < len) && (text[R - L] == text[R])) {
				R++;
			}
			Z[iterator] = R - L;
		}
		else {
			k = iterator - L;
			if (Z[k] < (R - iterator + 1)) {
				Z[iterator] = Z[k];
			}
			else {
				L = iterator;
				while ((R < len) && text[R - L] == text[R]) {
					R++;
				}
				Z[iterator] = R - L;
				R--;
			}
		}
	}
}

int count_word(string text, string word) {
	int count = 0;
	string concat = word + "$" + text;
	int len_concat = concat.length();
	int len_pattern = word.length();
	int *Z = (int *)malloc(len_concat * sizeof(int));
	int iterator = 0;

	get_z_array(concat, Z);

	for (iterator = 0; iterator < len_concat; ++iterator) {
		if (Z[iterator] == len_pattern) {
			count++;
		}
	}

	return count;
}

/***************************************************/