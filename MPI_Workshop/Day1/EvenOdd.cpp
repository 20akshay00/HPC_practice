#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])

{

using namespace std;

int ierr = MPI_Init(&argc, &argv);

int procid;
ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);

const char* result = (procid%2 == 0) ? "even" : "odd";

cout<<"From process "<< procid<<": "<< result <<endl;

ierr = MPI_Finalize();

}