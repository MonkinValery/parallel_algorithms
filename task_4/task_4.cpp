#include <omp.h>
#include <iostream>
#include <chrono> //this for counting time
#include "SquareMatrix.hpp"

int main (int argc, char *argv[])
{
    int N = 100000;
    SquareMatrix matrixA(N); // Inital matrix with random values
    SquareMatrix matrixB(N); // Inital matrix with random values
    SquareMatrix matrixLinearResult(N); // Matrix, to write the result of linear implementation
    SquareMatrix matrixParallelResult(N); // Matrix, to write the result of parallel implementation

    /*
    In this program we compare time, used by linear and parallel implementaions
    We gonna multiply random matrixes matrixA and matrixB: Result = matrixA * matrixB
    */
    
    // Linear implementation
    std::chrono::steady_clock::time_point beginLinear = std::chrono::steady_clock::now(); //Start
    double temp_result = 0; //Temporary variable  
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
                temp_result += matrixA.getElement(i, k) * matrixB.getElement(k, j);
            matrixLinearResult.setElement(i, j, temp_result);
            temp_result = 0;
        }   
    }
    std::chrono::steady_clock::time_point endLinear = std::chrono::steady_clock::now(); //End
    
    // Parallel implementation
    // In this implementation we count element(i,j) for result matrix on each thread
    std::chrono::steady_clock::time_point beginParallel = std::chrono::steady_clock::now(); //Start
    #pragma omp parallel default(shared)
    { 
        #pragma omp single
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    #pragma omp task
                    {
                        double temp_result = 0;
                        for (int k = 0; k < N; k++)
                            temp_result += matrixA.getElement(i, k) * matrixB.getElement(k, j);
                        matrixParallelResult.setElement(i, j, temp_result);
                    } 
                }   
            }
        }
    }     
    std::chrono::steady_clock::time_point endParallel = std::chrono::steady_clock::now(); //End

    /* Print ResultMatrix */
    // matrixLinearResult.printToConsole();
    // std::cout << std::endl;
    // matrixParallelResult.printToConsole();

    // Print used time
    std::cout << "Linear implementation:   " << std::chrono::duration_cast<std::chrono::microseconds>(endLinear - beginLinear).count() << "[µs]" << std::endl;
    std::cout << "Linear implementation:   " << std::chrono::duration_cast<std::chrono::nanoseconds> (endLinear - beginLinear).count() << "[ns]" << std::endl;
    std::cout << "Parallel implementation: " << std::chrono::duration_cast<std::chrono::microseconds>(endParallel - beginParallel).count() << "[µs]" << std::endl;
    std::cout << "Parallel implementation: " << std::chrono::duration_cast<std::chrono::nanoseconds> (endParallel - beginParallel).count() << "[ns]" << std::endl;
}