#include "pt4.h"

#include "mpi.h"

void Solve()
{
    /*
    В главном процессе дан набор вещественных чисел; количество чисел равно количеству подчиненных процессов.
    С помощью функции MPI_Bsend переслать по одному числу в каждый из подчиненных процессов,
    перебирая процессы в обратном порядке (первое число в последний процесс, второе — в предпоследний процесс, и т. д.),
    и вывести в подчиненных процессах полученные числа.
    */
    Task("MPI2Send6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank > 0)
    {
        double x;
        MPI_Recv(&x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        pt << x;
    }
    else
    {
        double x;
        for (int i = size - 1; i > 0; --i)
        {
            // Создаем буфер:
            int buf_size = sizeof(double) + MPI_BSEND_OVERHEAD;
            double* buf = (double*)malloc(buf_size);
            MPI_Buffer_attach(buf, buf_size);
            // Посылаем сообщение:
            pt >> x;
            MPI_Bsend(&x, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            // Отсоединяем буфер:
            MPI_Buffer_detach(buf, &buf_size);
        }
    }
}
