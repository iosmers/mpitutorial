#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_mpi_rank()
{
    int a;
    MPI_Comm_rank(MPI_COMM_WORLD, &a);
    return a;
}

int get_mpi_size()
{
    int a;
    MPI_Comm_size(MPI_COMM_WORLD, &a);
    return a;
}

void testDynamicSendAndRecv()
{
    MPI_Init(NULL, NULL);
    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    
    int number_amount;
    int i = 0;
    int size = get_mpi_size();
    if(get_mpi_rank() == 0)
    {
        srand(time(NULL)); 
        while(i < 100)
        {
            number_amount = (rand() / (float) RAND_MAX) * MAX_NUMBERS;
            int dst = i % (size - 1) + 1;
            MPI_Send(numbers, number_amount, MPI_INT, dst, 1 , MPI_COMM_WORLD);
            printf("0 发送 %d 个数到%d\n", number_amount, dst );
            i++;
        } 
    }else
    {
        while( i < 25)
        {
            MPI_Status status;
            MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &number_amount);
            printf("%d收到%d个从0发来的数据.消息源=%d, tag=%d\n", get_mpi_rank(), number_amount, status.MPI_SOURCE, status.MPI_TAG);
            i++;
        } 
    }
     
    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}
int main()
{
    testDynamicSendAndRecv();
    return 0;
}

