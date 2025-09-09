#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI4Type18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int N;
        pt >> N;

        int blocksize = (size - 1) * N * N;
        int* A = new int[blocksize];

        for(int i = 0; i < blocksize; i++)
            pt >> A[i];

        int blocklengths[N];
        int displacements[N];
        for (int i = 0; i < N; ++i)
        {
            blocklengths[i] = i + 1;
            displacements[i] = N * i * 3;
        }

        MPI_Datatype lower_triangular_block;
        MPI_Type_indexed(N, blocklengths, displacements, MPI_INT, &lower_triangular_block);
        MPI_Type_commit(&lower_triangular_block);

        for (int i = 1; i < size; ++i)
        {
            int block_start = (i - 1) % 3 * N + (i - 1) / 3 * N * 3 * N;
            MPI_Send(&A[block_start], 1, lower_triangular_block, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Status st;
        
        MPI_Probe(0, 0, MPI_COMM_WORLD, &st);

        int count;
        MPI_Get_count(&st, MPI_INT, &count);

        int* B = new int[count];
        MPI_Recv(B, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

        for(int i = 0; i < count; i++)
            pt << B[i];
    }

}
