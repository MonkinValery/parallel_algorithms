#include <omp.h>
#include <iostream>

int main (int argc, char *argv[])
{   
    #pragma omp parallel
    {
        int threads_num = omp_get_num_threads();
        for(int i = threads_num-1; i>=0; i--)
        {
                #pragma omp barrier
                {
                    if(i==omp_get_thread_num())
                    {
                            #pragma omp critical
                            std::cout << "Hello world, i'm thread "<< i << std::endl;
                    }
                }
        }
    }  
    return 0;
}