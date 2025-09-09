#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI2Send21");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status s;
    int l, t;
    double a, k;
    if (rank > 0)
    {
        pt >> l;
        for (int i = 0; i < l; ++i)
        {
            pt >> a;
            pt >> t;
            MPI_Send(&a, 1, MPI_DOUBLE, 0, t, MPI_COMM_WORLD);
        }
    }
    else
    {
        for (int i = 0; i <  2 * size; ++i)
        {
            MPI_Recv(&k, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i + 1, MPI_COMM_WORLD, &s);
            pt << k;
        }
    }

}
