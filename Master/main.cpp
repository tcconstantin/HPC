#include	"stdafx.h"
#include	"logic.h"

int main(int argc, char* argv[])
{
	int my_rank;
	int nr_procs;

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
	struct _file_structure arg, buf;
	strcpy_s(arg.path, strlen("test_path1") + 1, "test_path2");
	strcpy_s(arg.word, strlen("test_word1") + 1, "test_word2");

	MPI_Comm_spawn("Worker.exe",
		MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0,
		new_comm, &worker_comm,
		MPI_ERRCODES_IGNORE);

	if (0 == my_rank) {
		MPI_Send(&arg, 1, data_type, 0, 0, worker_comm);
		MPI_Recv(&buf, 1, data_type, 0, 0, worker_comm, MPI_STATUS_IGNORE);
		printf("[%s;%s]\n", buf.path, buf.word);
	}

	// for test
	/***************************************************/
	vector<string> files = get_files_from_directory("../Master/");
	for(size_t i = 0; i < files.size(); ++i) printf("%s\n", files[i].c_str());
	int fsize = get_size_of_file("../Master/Master.vcxproj");
	printf("%d\n", fsize);
	/***************************************************/

	free_file_structure_struct(data_type);
	MPI_Comm_free(&worker_comm);
	MPI_Finalize();

    return 0;
}
