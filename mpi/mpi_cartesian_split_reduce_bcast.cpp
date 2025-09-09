#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm22");
    int comm_rank, comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);
    double a;
    pt >> a;

    int dims[3] = { 2, 2, comm_size / 4 };
    int periods[3] = { 0, 0, 0 };
    int reorder = 0;
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, reorder, &cart_comm);

    int coords[3];
    MPI_Cart_coords(cart_comm, comm_rank, 3, coords);

    MPI_Comm split_comm;
    MPI_Comm_split(cart_comm, coords[2], comm_rank, &split_comm);

    double sum;
    MPI_Reduce(&a, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, split_comm);

    // Broadcasting the sum to all processes in the split_comm
    MPI_Bcast(&sum, 1, MPI_DOUBLE, 0, split_comm);

    pt << sum;

    MPI_Comm_free(&split_comm);
    MPI_Comm_free(&cart_comm);
}
