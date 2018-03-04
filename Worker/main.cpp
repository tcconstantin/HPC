#include	"stdafx.h"
#include	"logic.h"

int main(int argc, char* argv[])
{
    int my_rank;
	int nr_procs;
    int p_remote;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nr_procs);

    MPI_Datatype data_type = register_file_structure_struct();

    MPI_Comm master_comm;
	struct _file_structure b, msg;
	strcpy_s(b.path, strlen("test_path1") + 1, "test_path1");
	strcpy_s(b.word, strlen("test_word1") + 1, "test_word1");

	MPI_Comm_get_parent(&master_comm);
	MPI_Comm_remote_size(master_comm, &p_remote);

	if (0 == my_rank) {
		MPI_Recv(&msg, 1, data_type, 0, 0, master_comm, MPI_STATUS_IGNORE);
		printf("[%s;%s]\n", msg.path, msg.word);
		MPI_Send(&b, 1, data_type, 0, 0, master_comm);
	}
	else {
		printf("worker: %d\n", my_rank);
	}

	free_file_structure_struct(data_type);
	MPI_Comm_free(&master_comm);
	MPI_Finalize();

    return 0;
}

