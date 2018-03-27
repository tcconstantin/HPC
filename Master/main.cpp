#include	"stdafx.h"
#include	"logic.h"

int main(int argc, char* argv[])
{
	int my_rank;
	int nr_procs;

	string word = argc > 1 ? argv[1] : "When";

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nr_procs);

	MPI_Datatype data_type = register_file_structure_struct();

	MPI_Group group_world;
	MPI_Group group_new;
	MPI_Comm new_comm;

	MPI_Comm_group(MPI_COMM_WORLD, &group_world);
	MPI_Group_incl(group_world, 1, &my_rank, &group_new);
	MPI_Comm_create(MPI_COMM_WORLD, group_new, &new_comm);

	int my_rank_group;
	int nr_procs_group;

	MPI_Comm_rank(new_comm, &my_rank_group);
	MPI_Comm_size(new_comm, &nr_procs_group);

	MPI_Comm worker_comm;
	struct _file_structure buf, arg;

	int sum = 0;
	int mean = 0;
	vector<_file_information> files = get_files_from_directory("input/");
	for (size_t i = 0; i < files.size(); ++i) {
		sum += files[i].size;
	}
	mean = sum / files.size();
	

	size_t j = 0;
	vector<int> count_file_process;
	for (size_t i = 0; i < files.size(); ++i) {
		sum = 0;
		j = i;

		while (sum <= mean) {
			sum += files[j].size;
			if (j < (files.size() - 1)) j++;
			else break;
		};

		count_file_process.push_back(j - i + 1);
		i = j;
	}

#ifdef DEBUG
	printf("mean = %d\n", mean);
	printf("nr_files = %d\n", files.size());
	for (size_t i = 0; i < count_file_process.size(); ++i) {
		printf("c = %d \n", count_file_process[i]);
	}
	printf("nr_workers = %d\n", count_file_process.size());
#endif

	MPI_Comm_spawn("Worker.exe",
		MPI_ARGV_NULL, count_file_process.size(), MPI_INFO_NULL, 0,
		new_comm, &worker_comm,
		MPI_ERRCODES_IGNORE);

	string buffer;
	int index = 0;

	if (0 == my_rank) {
		for (size_t i = 0; i < count_file_process.size(); ++i) {
			for (size_t j = 0; j < count_file_process[i]; ++j) {
				buffer += files[index].name;
				buffer += ";";
				index++;
			}

			strcpy_s(arg.path, buffer.size() + 1, buffer.c_str());
			strcpy_s(arg.word, word.size() + 1,  word.c_str());

			MPI_Send(&arg, 1, data_type, i, 0, worker_comm);

			buffer.clear();
			
			MPI_Recv(&buf, 1, data_type, i, 0, worker_comm, MPI_STATUS_IGNORE);
			printf("Master: %s\n", buf.path);
		}
	}

	free_file_structure_struct(data_type);
	MPI_Comm_free(&worker_comm);
	MPI_Finalize();

    return 0;
}
