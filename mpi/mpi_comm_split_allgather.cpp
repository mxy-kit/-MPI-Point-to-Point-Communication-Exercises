#include "pt4.h"
#include "mpi.h"
#include <vector>
#include <algorithm>

void Solve()
{
    Task("MPI5Comm9");
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N;
    double A = 0.0;
    pt >> N;
    MPI_Comm new_comm;
    int color = (N == 1) ? 1 : MPI_UNDEFINED;
    if(N == 1) pt >> A;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);
    if(N == 1)
    {
        int new_size;
        MPI_Comm_size(new_comm, &new_size);
        std::vector<double> all_A(new_size);
        MPI_Allgather(&A, 1, MPI_DOUBLE, &all_A[0], 1, MPI_DOUBLE, new_comm);
        for(auto& num : all_A) 
            pt << num;
    }
    if(new_comm != MPI_COMM_NULL)
        MPI_Comm_free(&new_comm);
}
