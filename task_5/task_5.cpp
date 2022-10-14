//count row of e^x and tg((x^2))*sin(1/(1-x))
#include <omp.h>
#include <iostream>
#include <chrono> //this for counting time

int main(int argc, char *argv[]){
    int N = 0;

    // Read the number of elements
    if(argv[1] != nullptr){
        N = std::stoi(argv[1]);
    }
    else{
        std::cout << "Wrong input.";
        return -1;
    }

    int numThreads = omp_get_num_threads();
    int elementsOnThread = N / (numThreads * 10); // here we devide all elements on 10 * numberOfThreads groups, that will be counted on single thread 
    if(elementsOnThread == 0)
    {
        std::cout << "Use bigger N" << std::endl;
        return -1;
    }

    // Count the row in linear
    double x = 1.0;
    double rowLinear = 1.0;
    double elementLinear = 1.0;
    std::chrono::steady_clock::time_point beginLinear = std::chrono::steady_clock::now(); //Start
    for(int i = 1; i < N; i++)
    {
        elementLinear = elementLinear * x / i;
        rowLinear += elementLinear;
    }
    std::chrono::steady_clock::time_point endLinear = std::chrono::steady_clock::now(); //End
    

    // Count the row in parallel
    /* Ускорение в нашем случае происходит засчёт распараллеливания 
       записи в итоговый рещультат. Так как экспонента считается по рекурсии
       то распараллеливание её невозможно
    */
    double rowParallel = 1.0;
    std::chrono::steady_clock::time_point beginParallel = std::chrono::steady_clock::now(); //Start
    #pragma omp parallel default(shared)
    { 
        #pragma omp single
        {
            double elementParallel = 1.0;
            double rowThread = 0;
            for(int i = 1; i < N; i++)
            {
                elementParallel = elementParallel * x / i;
                rowThread += elementParallel;
                #pragma omp task
                {
                    rowParallel += rowThread;
                }
            }
        }
    } 
    std::chrono::steady_clock::time_point endParallel = std::chrono::steady_clock::now(); //End    

    // Print the result
    std::cout << "The linear result:   " << rowLinear <<std::endl;
    std::cout << "The parallel result: " << rowLinear <<std::endl;

    // Print used time
    std::cout << "Linear implementation:   " << std::chrono::duration_cast<std::chrono::microseconds>(endLinear - beginLinear).count() << "[µs]" << std::endl;
    std::cout << "Linear implementation:   " << std::chrono::duration_cast<std::chrono::nanoseconds> (endLinear - beginLinear).count() << "[ns]" << std::endl;
    std::cout << "Parallel implementation: " << std::chrono::duration_cast<std::chrono::microseconds>(endParallel - beginParallel).count() << "[µs]" << std::endl;
    std::cout << "Parallel implementation: " << std::chrono::duration_cast<std::chrono::nanoseconds> (endParallel - beginParallel).count() << "[ns]" << std::endl;
}