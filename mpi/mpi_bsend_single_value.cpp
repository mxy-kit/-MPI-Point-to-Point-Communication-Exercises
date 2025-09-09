#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI2Send2");
    /*
    В каждом подчиненном процессе дано вещественное число. Переслать эти числа в главный процесс,
    используя функции MPI_Bsend (посылка сообщения с буферизацией) и MPI_Recv, и вывести их в главном процессе.
    Полученные числа выводить в порядке убывания рангов переславших их процессов.
    Для задания буфера использовать функцию MPI_Buffer_attach
    */
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (rank > 0)
    {
        double x;
        pt >> x;
        int buf_size = sizeof(double) + MPI_BSEND_OVERHEAD;
        double* buf = (double*)malloc(buf_size);
        MPI_Buffer_attach(buf, buf_size);
        MPI_Bsend(&x, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
        MPI_Buffer_detach(buf, &buf_size);
    }
    else
    {
        for (int i = size - 1; i > 0; --i)
        {
            double x;
            MPI_Recv(&x, 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD, &status);
            pt << x;
        }
    }

}
