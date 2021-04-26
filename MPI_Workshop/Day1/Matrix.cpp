#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include<cmath>

int main(int argc, char *argv[])

{

using namespace std;

int ierr = MPI_Init(&argc, &argv);

int procid;
int res = 1;
ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);

switch(procid)
{  
    case 0:
        for(int i = 2; i<=10; i++){res += i;}
        break;
    case 1:
        for(int i = 2; i<=10; i++){res *= i;}
        break;
    case 2:
        for(int i = 2; i<=10; i++){res += pow(i, 2);}
        break;

    default:
        break;
}

cout<<"Result from process "<< procid<<", "<<res<<endl;

ierr = MPI_Finalize();

}