#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI2Send9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status s;
    if (rank > 0)
    {
        int n;
        pt >> n;
        if (n > 0)
        {
            double *a = new double[n];
            for (int i = 0; i < n; ++i)
            {
                pt >> a[i];
            }
            MPI_Send(a, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        int n;
        MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &s);
        MPI_Get_count(&s, MPI_DOUBLE, &n);
        double *a = new double[n];
        MPI_Recv(a, n, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &s);
        for (int j = 0; j < n; ++j)
            pt << a[j];
        pt << s.MPI_SOURCE;
    }
}
