#include "pt4.h"
#include <vector>

#include "mpi.h"

void Solve()
{
    Task("MPI2Send4");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank > 0)
    {
        int n;
        int *a = new int[n];
        pt >> n;

        for (int i = 0; i < n; ++i)
            pt >> a[i];
            
        int buf = 100 + MPI_BSEND_OVERHEAD;
        int *buffer = (int*)malloc(buf);
        MPI_Buffer_attach(buffer, buf);
        MPI_Bsend(a, n, MPI_INT, 0, rank, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer, &buf);

        delete[] a;
    }
    else
    {
        MPI_Status s;
        int n;
        for (int i = 1; i < size; ++i)
        {
            MPI_Probe(i, i, MPI_COMM_WORLD, &s);
            MPI_Get_count(&s, MPI_INT, &n);
            int *a = new int[n];
            MPI_Recv(a, n, MPI_INT, i, i, MPI_COMM_WORLD, &s);
            for (int j = 0; j < n; ++j)
                pt << a[j];
            delete[] a;
        }
    }
}