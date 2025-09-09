#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI4Type13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double  Rnum;
    int N = size - 1;
    int *integers = new int[N];

    int packSize = N * sizeof(int) + sizeof(double);
    char* sendBuf = new char[packSize];

    if (rank > 0)
    {
        pt >> Rnum;

        for (int i = 0; i < rank; i++)
            pt >> integers[i];

        int position = 0;
        MPI_Pack(&Rnum, 1, MPI_DOUBLE, sendBuf, packSize, &position, MPI_COMM_WORLD);
        MPI_Pack(integers, N, MPI_INT, sendBuf, packSize, &position, MPI_COMM_WORLD);
    }

    int totalSize = packSize * N;
    char* recBuf = new char[totalSize];

    MPI_Gather(sendBuf, packSize, MPI_PACKED, recBuf, packSize, MPI_PACKED, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        int position = packSize;
        for (int i = 1; i < size; i++)
        {
            MPI_Unpack(recBuf, packSize, &position, &Rnum, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(recBuf, packSize, &position, integers, N, MPI_INT, MPI_COMM_WORLD);

            pt << Rnum;
            for (int j = 0; j < i; ++j)
                pt << integers[j];
        }
        //delete[] recBuf;
    }
    //delete[] sendBuf;
    //delete[] integers;
}