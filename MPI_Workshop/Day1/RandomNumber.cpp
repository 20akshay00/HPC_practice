#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include<time.h>

int main(int argc, char *argv[])

{

using namespace std;

int ierr = MPI_Init(&argc, &argv);

int procid, numprocs;

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);

srand(procid + 1);
cout<<"Random number from process "<< procid<<": "<< rand()/double(RAND_MAX)<<endl;

ierr = MPI_Finalize();

}