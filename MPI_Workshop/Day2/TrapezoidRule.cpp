
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)

{

	int my_rank;	 // My process rank

	int nproc;		 // The number of processes

	float xi = 0.0;	 // Left endpoint

	float xf = 1.0;	 // Right endpoint

	int ntrap = 200; // Number of trapezoids

	float h;		 // Trapezoid base length

	float local_xi;	 // Left endpoint my process

	float local_xf;	 // Right endpoint my process

	float x;

	int local_ntrap;	 // Number of trapezoids

	float intg;			 // Integral over my interval

	float tot_intg = -1; // Total integral

	int source;	  // Process sending integral

	int dest = 0; // All messages go to 0

	int tag = 0;

	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	h = (xf - xi) / ntrap;		 /* h is the same for all processes */

	local_ntrap = ntrap / nproc; /* So is the number of trapezoids */

	/* Length of each process' interval of integration = local_n*h. */

	local_xi = xi + my_rank * local_ntrap * h;

	local_xf = local_xi + local_ntrap * h;

	intg = (local_xi * local_xi + local_xf * local_xf) / 2.0;


	x = local_xi;


	for (int i = 1; i <= local_ntrap - 1; i++)

	{

		x = x + h;

		intg = intg + x * x;

	}

	intg = intg * h;


	/* Add up the intgs calculated by each process */

	if (my_rank == 0)

	{

		tot_intg = intg;

		printf("\nCalculated by processor %d = %f\n", my_rank, intg);

		for (source = 1; source < nproc; source++)

		{

			MPI_Recv(&intg, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);

			printf("Received result by processor %d from %d = %f\n",

				   my_rank, source, intg);

			tot_intg = tot_intg + intg;

		}

	}

	else

	{

		MPI_Send(&intg, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);

		printf("Sent result by processor %d to %d = %f\n",

			   my_rank, dest, intg);

	}

	/* Print the result */

	if (my_rank == 0)

	{

		printf("With n = %d trapezoids, our estimate\n", ntrap);

		printf("of the integral from %f to %f = %f\n", xi, xf, tot_intg);

	}


	MPI_Finalize();

	return 0;

}

