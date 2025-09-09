#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI5Comm11");
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N;
    double A = 0.0;
    pt >> N;
    MPI_Comm new_comm;
    int color = (N == 1) ? 1 : MPI_UNDEFINED;
    if(N == 1) pt >> A;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);
    if(N == 1)
    {
        double sumA;
        MPI_Allreduce(&A, &sumA, 1, MPI_DOUBLE, MPI_SUM, new_comm);
        pt << sumA;
    }
    if(new_comm != MPI_COMM_NULL)
        MPI_Comm_free(&new_comm);
}
