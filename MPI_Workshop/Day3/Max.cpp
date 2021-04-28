#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int my_rank;  // My process rank
    int p; // The number of processes
    int source; // Process sending integral
    int dest = 0; // All messages go to 0
    int tag = 0;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    srand((unsigned)time(NULL)+my_rank*p);
    double max;
    double value = (double)rand()/(double)RAND_MAX;
    
    printf("Hi, from processor %d with value %f\n",my_rank,value);
    
    MPI_Reduce(&value, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Bcast(&max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("I, processor %d know that maximum value is %f\n",my_rank,max);
    
    MPI_Barrier(MPI_COMM_WORLD);
    if(max == value) printf("\n\n Maximum value %f is from process %d \n\n", max, my_rank);

    MPI_Finalize();
    return 0;
}