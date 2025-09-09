#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI3Coll9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *cnt = new int[size];
    int *dis = new int[size];
    int sz = size * (size + 3) / 2;
    int *sbuf = new int[sz];
    int *rbuf = new int[sz];

    int  c = 2, d = 0;
    for (int i = 0; i < size; ++i)
    {
        dis[i] = d;
        cnt[i] = c;
        d += c;
        c++;
    }

    if (rank == 0)
    	for (int i = 0; i < sz; i++)
    		pt >> sbuf[i];

    MPI_Scatterv(sbuf, cnt, dis, MPI_INT, rbuf, sz, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < sz; i++)
        if (rbuf[i] > 0)
    	    pt << rbuf[i];
}