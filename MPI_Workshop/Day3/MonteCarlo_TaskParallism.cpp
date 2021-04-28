#include <stdio.h>
#include <stdlib.h>/* We'll be using MPI routines, definitions, etc. */
#include "mpi.h"

int main(int argc, char** argv) {
    int         my_rank;   /* My process rank           */
    int         p;         /* The number of processes   */

    float       a;         /* Left endpoint             */
    float       b;         /* Right endpoint            */
    int         n;         /* Number of sweeps          */
    
    float       local_a;   /* Left endpoint my process  */
    float       local_b;   /* Right endpoint my process */
    int         local_n;   /* Number of trapezoids for  */
                           /* my calculation            */
    float       integral;  /* Integral over my interval */
    float       total;     /* Total integral            */
    
    int         source;    /* Process sending integral  */
    int         dest = 0;  /* All messages go to 0      */
    int         tag = 0;
    float       x;
    
    MPI_Status  status;
   
    void Get_data2(float* a_ptr, float* b_ptr, int* n_ptr, int my_rank);    /* Let the system do what it needs to start up MPI */
    
    MPI_Init(&argc, &argv);    /* Get my process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);    /* Find out how many processes are being used */
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    Get_data2(&a, &b, &n, my_rank);
    MPI_Barrier(MPI_COMM_WORLD); 
    
    local_a = a + my_rank*(b-a)/p;
    local_b = local_a + (b-a)/p;

    local_n = n;  /* So is the number of trapezoids */    
    integral = 0.0; 
    srand((unsigned)time(NULL)+my_rank*p);

    for (int i = 1; i < local_n; i++) { 
        x = local_a + (float)rand()*(local_b-local_a)/(float)RAND_MAX;
      //printf("rank x %d,%f\n",my_rank,x);
        integral = integral + x*x; 
    } 

    integral = (local_b-local_a)*integral/local_n;     /* Print the result */

    if (my_rank == 0) {
        printf("Calculated by processor %d = %f\n", my_rank, integral);
    }
    else{
    printf("Received by processor 0 from processor %d = %f\n", my_rank, integral);
    }    /* Add up the integrals calculated by each process */
   
    MPI_Reduce(&integral, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);    
        
    MPI_Barrier(MPI_COMM_WORLD);
    if(my_rank==0){
    printf("\n\nWith n = %d sweeps, our estimate\n", p*n);
    printf("of the integral from %f to %f = %f\n", a, b, total);
    }

    /* Shut down MPI */
    MPI_Finalize();
}
/* Function Get_data2 */
void Get_data2(
         float*  a_ptr    /* out */, 
         float*  b_ptr    /* out */, 
         int*    n_ptr    /* out */,
         int     my_rank  /* in  */) {    
             
    if (my_rank == 0) {
        printf("Enter a, b, and n\n");
        scanf("%f %f %d", a_ptr, b_ptr, n_ptr);
    }

    MPI_Bcast(a_ptr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(b_ptr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(n_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
} /* Get_data2 */