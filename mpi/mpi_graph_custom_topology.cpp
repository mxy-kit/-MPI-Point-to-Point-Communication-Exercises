#include "pt4.h"
#include "mpi.h"
#include <vector>
using namespace std;

void Solve()
{
    Task("MPI5Comm30");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = (size - 1) / 3;

    vector<int> edges(size), index;

    edges[0] = n;
    for (int i = 1; i < size; i++)
        edges[i] = edges[i - 1] + ((i % 3 == 0) ? 3 : 2);

    for (int i = 3; i < size; i += 3)
        index.push_back(i);

    for (int i = 1; i < size; i++)
    {
        switch (i % 3)
        {
            case 0:
                index.push_back(0);
                index.push_back(i - 2);
                index.push_back(i - 1);
                break;
            case 1:
                index.push_back(i + 1);
                index.push_back(i + 2);
                break;
            case 2:
                index.push_back(i - 1);
                index.push_back(i + 1);
                break;
        }
    }
    MPI_Status st;

    int A;
    pt >> A;

    MPI_Comm graph_comm;

    MPI_Graph_create(MPI_COMM_WORLD, size, &edges[0], &index[0], 0, &graph_comm);

    int neighbors_count;
    MPI_Graph_neighbors_count(graph_comm, rank, &neighbors_count);
    vector<int> neighbors(neighbors_count);
    MPI_Graph_neighbors(graph_comm, rank, neighbors_count, &neighbors[0]);

    int data;
    vector<int> received_data;
    for (int i = 0; i < neighbors_count; i++)
    {
        MPI_Sendrecv(&A, 1, MPI_INT, neighbors[i], 0, &data, 1, MPI_INT, neighbors[i], 0, graph_comm, &st);
        received_data.push_back(data);
    }
    
    for(auto el : received_data)
        pt << el;
}
