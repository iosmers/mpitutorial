// #include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int get_mpi_rank()
{
    int a;
    MPI_Comm_rank(MPI_COMM_WORLD, &a);
    return a;
}

int get_mpi_world()
{
    int a;
    MPI_Comm_size(MPI_COMM_WORLD, &a);
    return a;
}

void testSendAndRecv()
{
    MPI_Init(NULL, NULL);
    int rank = get_mpi_rank();
    int world_size = get_mpi_world();

    if(world_size < 2)
    {
        printf("错误，必须使用两个以上的进程\n");
        MPI_Abort(MPI_COMM_WORLD, 8);
    }
    int number ;
    if(rank == 0)
    {
        number = 10;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }else if(rank == 1)
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf ("进程1收到进程0的消息：number=%d\n", number);  
    }
    MPI_Finalize();
}
int main()
{
    testSendAndRecv();

}