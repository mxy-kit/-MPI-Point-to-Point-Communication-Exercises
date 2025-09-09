#include "pt4.h"

#include "mpi.h"

void Solve()
{
    Task("MPI2Send13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double randomNum;
int arrayLength = size - 1;
int *numArray = new int[arrayLength];

int bufferSize = arrayLength * sizeof(int) + sizeof(double);
char* outBuffer = new char[bufferSize];

if (rank > 0)
{
    pt >> randomNum;

    for (int index = 0; index < rank; index++)
        pt >> numArray[index];

    int offset = 0;
    MPI_Pack(&randomNum, 1, MPI_DOUBLE, outBuffer, bufferSize, &offset, MPI_COMM_WORLD);
    MPI_Pack(numArray, arrayLength, MPI_INT, outBuffer, bufferSize, &offset, MPI_COMM_WORLD);
}

int totalBufferSize = bufferSize * arrayLength;
char* inBuffer = new char[totalBufferSize];

MPI_Gather(outBuffer, bufferSize, MPI_PACKED, inBuffer, bufferSize, MPI_PACKED, 0, MPI_COMM_WORLD);

if (rank == 0)
{
    int offset = bufferSize;
    for (int index = 1; index < size; index++)
    {
        MPI_Unpack(inBuffer, bufferSize, &offset, &randomNum, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Unpack(inBuffer, bufferSize, &offset, numArray, arrayLength, MPI_INT, MPI_COMM_WORLD);

        pt << randomNum;
        for (int subIndex = 0; subIndex < index; ++subIndex)
            pt << numArray[subIndex];
    }
}


}
