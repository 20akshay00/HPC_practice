
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)

{

	int my_rank; // My process rank
	int nproc;	// The number of processes
	int source;	  // Process sending integral
	int dest = 0; // All messages go to 0
	int tag = 0;
    int tot_sum = 0;
    int part_sum = 0;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	if (my_rank == 0)
	{
		printf("\nCalculated by processor %d = %d\n", my_rank, my_rank);

		for (source = 1; source < nproc; source++)
		{
			MPI_Recv(&part_sum, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
			printf("Received result by processor %d from %d = %d\n", my_rank, source, part_sum);
			
            tot_sum += part_sum;
		}
	}

	else
	{
		MPI_Send(&my_rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		printf("Sent result by processor %d to %d = %d\n", my_rank, dest, my_rank);
	}

	/* Print the result */

	if (my_rank == 0)
	{
        printf("Sum of AP is %d", tot_sum);
	}

	MPI_Finalize();
	return 0;

}

