#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI3Coll18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *cnt = new int[size];
    int *dis = new int[size];
    int *rdis = new int[size];
    int sz = size * 2;
    double *sbuf = new double[sz];
    double *rbuf = new double[sz];

    int pow = size - 1;
    for (int i = 0; i < size; i++)
    {
        cnt[i] = 2;
        rdis[i] = i * 2;
        dis[i] = pow - i;
    }

    for (int i = 0; i <= size; i++)
        pt >> sbuf[i];

    MPI_Alltoallv(sbuf, cnt, dis, MPI_DOUBLE, rbuf, cnt, rdis, MPI_DOUBLE, MPI_COMM_WORLD);

    for (int i = 0; i < sz; i++)
    	pt << rbuf[i];
}
