#include "pt4.h"
#include "mpi.h"
using namespace std;

void Solve()
{
    Task("MPI5Comm8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N;
    pt >> N;

    MPI_Comm new_comm;
    int color = (N == 1) ? 1 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);

    if (N == 1)
    {
        double A;
        pt >> A;

        int new_rank, new_size;
        MPI_Comm_rank(new_comm, &new_rank);
        MPI_Comm_size(new_comm, &new_size);

        vector<double> recvbuf(new_size);

        MPI_Gather(&A, 1, MPI_DOUBLE, &recvbuf[0], 1, MPI_DOUBLE, new_size - 1, new_comm);

        if (new_rank == new_size - 1)
        {
            for (double val : recvbuf)
                pt << val;
        }
    }

}
