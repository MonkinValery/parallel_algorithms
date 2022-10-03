#include <omp.h>
#include <iostream>

int main (int argc, char *argv[])
{   
    int index, sum = 0;
    int N = 0;

    // Check the right input
    //
    if(argc == 2)
    {
        N = atoi(argv[1]);
    }
    else
    {
        std::cout << "Wrong input" << std::endl;
        return -1;
    }

    // We sum numver form 1 to N with using omp for(automatic paralleling loop)
    // schedule with dynamic and chunck-size 1 means that each thread do only 1 sum operation and it provides optimal load balancing
    // 
    //
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