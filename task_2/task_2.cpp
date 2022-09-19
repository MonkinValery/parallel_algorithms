#include <omp.h>
#include <iostream>

int main (int argc, char *argv[])
{   
    int index, sum = 0;
    int N = 0;
    if(argc == 2)
    {
        N = atoi(argv[1]);
    }
    else
    {
        std::cout << "Wrong input" << std::endl;
        return -1;
    }
    #pragma omp parallel shared(N, sum) private(index)
    {
        #pragma omp for schedule(dynamic, 1) reduction(+:sum) 
        for(index = 1; index <= N; index++)
        {
            sum += index;
        }    
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}