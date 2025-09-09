#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI3Coll26");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sz = size * (size + 3) / 2;
    int *cnt = new int[size];
    int *sbuf = new int[sz];
    int *rbuf = new int[rank + 2];

    int  c = 2;
    for (int i = 0; i < size; i++)
    {
        cnt[i] = c;
        c++;
    }

    for (int i = 0; i < sz; ++i)
        pt >> sbuf[i];
    
    MPI_Reduce_scatter(sbuf, rbuf, cnt, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    for (int i = 0; i < rank + 2; i++)
    	pt << rbuf[i];
}
