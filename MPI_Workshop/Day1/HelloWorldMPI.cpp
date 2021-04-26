#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])

{

using namespace std;

int ierr = MPI_Init(&argc, &argv);

int procid, numprocs;

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);

ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

cout<<"Hello world,"<< procid<<", "<<numprocs<<endl;

ierr = MPI_Finalize();

}

