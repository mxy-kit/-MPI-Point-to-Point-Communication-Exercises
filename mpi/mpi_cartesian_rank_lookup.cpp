#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI5Comm23");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int M, N , X, Y;
    if (rank == 0)
        pt >> M >> N;
    
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm comm;

    int dims[] = {M, N};
    int periods[] = {1, 0};
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);

    if (rank < M * N)
        pt >> X >> Y;
        
    int coords[] = {X, Y};
    int new_rank;
    
    MPI_Comm_set_errhandler(comm, MPI_ERRORS_RETURN);

    if (comm != MPI_COMM_NULL)
    {
        if (MPI_Cart_rank(comm, coords, &new_rank) == MPI_SUCCESS)
            pt << new_rank;
        else pt << -1;
    }
}
