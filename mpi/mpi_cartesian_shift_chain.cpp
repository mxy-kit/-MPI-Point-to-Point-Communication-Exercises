#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI5Comm25");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm cart_comm;
    int dims = size, periods = 0, reorder = 1;
    MPI_Cart_create(MPI_COMM_WORLD, 1, &dims, &periods, reorder, &cart_comm);

    int source, dest;
    MPI_Cart_shift(cart_comm, 0, -1, &source, &dest);

    double A;
    if (rank != 0)
    {
        pt >> A;
        MPI_Send(&A, 1, MPI_DOUBLE, dest, 0, cart_comm);
    }

    if (rank != size - 1)
    {
        MPI_Recv(&A, 1, MPI_DOUBLE, source, 0, cart_comm, MPI_STATUS_IGNORE);
        pt << A;
    }

}
