#include "pt4.h"
#include <vector>
#include "mpi.h"

using namespace std;

void Solve()
{
    Task("MPI4Type10");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int m = 0;
	int temp;

	MPI_Pack_size(2, MPI_INT, MPI_COMM_WORLD, &temp);
	m += temp;
	MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &temp);
	m += temp;
	int buff_size = m * (size - 1);

	vector<char> buff (buff_size);
	vector<char> r_buf(m);
	vector<int> s_count(size, m);

	s_count[0] = 0;
	vector<int> dis(size, 0);

	for (int i = 2; i < size; ++i)
		dis[i] = dis[i - 1] + m;

	int position;

	if (rank == 0) 
    {
		position = 0;
		for (int i = 0; i < size - 1; ++i) 
        {
			int a, c;
			double b;
			pt >> a >> b >> c;
			MPI_Pack(&a, 1, MPI_INT, &buff[0], buff_size, &position, MPI_COMM_WORLD);
			MPI_Pack(&b, 1, MPI_DOUBLE, &buff[0], buff_size, &position, MPI_COMM_WORLD);
			MPI_Pack(&c, 1, MPI_INT, &buff[0], buff_size, &position, MPI_COMM_WORLD);
		}

	}

	MPI_Scatterv(&buff[0], &s_count[0], &dis[0], MPI_PACKED, &r_buf[0], m, MPI_PACKED, 0, MPI_COMM_WORLD);

	if (rank != 0) 
    {
		position = 0;
		int a, c;
		double b;
		MPI_Unpack(&r_buf[0], buff_size, &position, &a, 1, MPI_INT, MPI_COMM_WORLD);
		MPI_Unpack(&r_buf[0], buff_size, &position, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Unpack(&r_buf[0], buff_size, &position, &c, 1, MPI_INT, MPI_COMM_WORLD);
		pt << a << b << c;
	}
}
