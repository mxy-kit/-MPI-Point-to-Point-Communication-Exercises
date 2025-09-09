#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI4Type17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int N;
    pt >> N;

    MPI_Datatype blockType;
    MPI_Type_vector(N, N, N * 3, MPI_INT, &blockType);
    MPI_Type_commit(&blockType);

    if (rank > 0)
    {
        int blocksize = N * N;
        int* B = new int[blocksize];
        for (int i = 0; i < blocksize; i++)
            pt >> B[i];

        MPI_Send(B, blocksize, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Status s;
        int blocksize = N * N;
        int* A = new int[blocksize * (size - 1)];

        for (int i = 1; i < size; ++i) 
        {
            int tmp = (i - 1) / 3;
            int tmp_mod = (i - 1) % 3;

            MPI_Recv(&A[tmp * blocksize * 3 + tmp_mod * N], 1, blockType, i, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
        }

        for (int i = 0; i < blocksize * (size - 1); i++)
        {
            pt << A[i];
        }
    }
}