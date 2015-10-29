// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
//C:\Program Files\Microsoft Compute Cluster Pack\Bin\mpiexec.exe -np 2 Parall.exe

#include "C:\\Program Files\\Microsoft Compute Cluster Pack\\Include\\mpi.h"
//#include <mpi.h>
#include <stdio.h>
const int N = 1000;
int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("I %d of %d\n", rank, size);
	int msg = 1;
	MPI_Status stat;
	if (rank == 0){
		for (int i = 1; i < size; i++)
			MPI_Send(&i, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
	}
	else {
		msg = 5;
		//printf("Before %d\n", msg);
		MPI_Recv(&msg, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &stat);
		printf("I am %d get ^%d^ \n", rank, msg);
	}
	double start,finish;
	if (rank == 0)
	{
		start = MPI_Wtime();
		for (int i = 0; i < N; i++) MPI_Send(&msg, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		finish = MPI_Wtime();
		printf("Time: %e\n", (finish - start)/N);
	}
	//if (rank == 1) MPI_Recv(&msg, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &stat);
	
	//getchar();
	MPI_Finalize();
	return 0;
}

