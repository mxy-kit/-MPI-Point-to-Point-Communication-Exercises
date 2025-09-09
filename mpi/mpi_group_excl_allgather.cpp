#include "pt4.h"
#include <vector>
#include "mpi.h"
using namespace std;

void Solve()
{
    Task("MPI5Comm2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int exclude = size / 2;
    int group = size - exclude;

    vector<double> input_data(2);
    vector<double> gathered_data(2 * exclude);

    if (rank % 2 == 1)
    {
        pt >> input_data[0] >> input_data[1];
    }

    vector<int> ranks_to_exclude(group);
    for (int i = 0; i < group; ++i)
    {
        ranks_to_exclude[i] = 2 * i;
    }

    MPI_Group original_group, new_group;
    MPI_Comm_group(MPI_COMM_WORLD, &original_group);
    MPI_Group_excl(original_group, group, ranks_to_exclude.data(), &new_group);

    MPI_Comm new_comm;
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    if (rank % 2 == 1)
    {
        MPI_Allgather(&input_data[0], 2, MPI_DOUBLE, &gathered_data[0], 2, MPI_DOUBLE, new_comm);

        for (double value : gathered_data)
        {
            pt << value;
        }
    }
}
