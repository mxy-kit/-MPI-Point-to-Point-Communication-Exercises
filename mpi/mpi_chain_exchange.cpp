#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI2Send17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status s;

    int cnt = 0;

    for (int i = 0; i < size - 1; ++i)
    {
        int a;
        pt >> a;

        if (rank == i)
            cnt++;

        MPI_Send(&a, 1, MPI_INT, cnt, 0, MPI_COMM_WORLD);

        int b;
        MPI_Recv(&b, 1, MPI_INT, cnt, 0, MPI_COMM_WORLD, &s);
        pt << b;

        cnt++;
    }
}
