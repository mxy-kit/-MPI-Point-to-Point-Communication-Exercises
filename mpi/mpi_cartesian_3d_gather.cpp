#include "pt4.h"
#include "mpi.h"
#include <vector>
using namespace std;

void Solve()
{
    Task("MPI5Comm19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int A;
    pt >> A;

    MPI_Comm grid_comm;
    int dims[] = {2, 2, size / 4};
    int periods[] = {0, 0, 0};
    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &grid_comm);

    int coords[3];
    MPI_Cart_coords(grid_comm, rank, 3, coords);

    MPI_Comm row_comm;
    int remain_dims[] = {0, 0, 1};
    MPI_Cart_sub(grid_comm, remain_dims, &row_comm);

    int row_rank;
    MPI_Comm_rank(row_comm, &row_rank);

    int row_size = size / 4;
    vector<int> gathered_nums(row_size);

    MPI_Gather(&A, 1, MPI_INT, &gathered_nums[0], 1, MPI_INT, 0, row_comm);

    if (row_rank == 0)
    {
        for (int i = 0; i < row_size; ++i)
            pt << gathered_nums[i];
    }
}
