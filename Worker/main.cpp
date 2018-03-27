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
	struct _file_structure b;

	MPI_Comm_get_parent(&master_comm);
	MPI_Comm_remote_size(master_comm, &p_remote);

	for (int i = 0; i < nr_procs; ++i) {
		if (my_rank == i) {
			struct _file_structure msg_recv;
			MPI_Recv(&msg_recv, 1, data_type, 0, 0, master_comm, MPI_STATUS_IGNORE);
			string to_send;
			string files = msg_recv.path;
			string delimiter = ";";
			size_t position = 0;
			string file;
			while ((position = files.find(delimiter)) != std::string::npos) {
				file = files.substr(0, position);
				int c_word = count_word(file, msg_recv.word);
				to_send += file + ":" + to_string(c_word) + ";";
				files.erase(0, position + delimiter.length());
			}

			strcpy_s(b.path, to_send.size() + 1, to_send.c_str());
			strcpy_s(b.word, strlen(msg_recv.word) + 1, msg_recv.word);
			MPI_Send(&b, 1, data_type, 0, 0, master_comm);
			to_send.clear();

#ifdef DEBUG
			printf("[%s%s]\n", msg_recv.path, msg_recv.word);
#endif
		}
	}

	free_file_structure_struct(data_type);
	MPI_Comm_free(&master_comm);
	MPI_Finalize();

    return 0;
}

