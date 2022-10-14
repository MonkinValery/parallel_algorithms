/* 
    Будем искать простые числа исходя из предположения, 
    что любое число представимо в виде 6К+-1.
    Проверим все такие числа до N, путём деления 
    на все известные простые числа, меньших чем на половину
    от проверяемого числа
*/
#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]){
    int numberSimple, N = 0;

    // Read the number of elements
    if(argv[1] != nullptr){
        N = std::stoi(argv[1]);
    }
    else{
        std::cout << "Wrong input.";
        return -1;
    }

    if(N == 1)
    {
        std::cout << "Only 1 simple number" << std::endl;
    }
    else if(N == 2)
    {
        std::cout << "Only 2 simple numbers" << std::endl;
    }
    else if(N == 3)
    {
        std::cout << "Only 3 simple numbers" << std::endl;
    }
    else
    {
        numberSimple = 3;
        for (int condidate = 5; condidate <= N; condidate += 6)
        {
            bool isSimple = true;
            #pragma omp parallel shared(isSimple)
            {
                #pragma omp for schedule(dynamic, 1)
                    for(int i = 2; i < condidate / 2; i++)
                    {
                        if(condidate % i == 0)
                        {
                            isSimple = false;
                        }
                    }
                
            }
            #pragma omp barrier
            if(isSimple)
            {
                numberSimple++;
            }
        }
        for (int condidate = 7; condidate <= N; condidate += 6)
        {
            bool isSimple = true;
            #pragma omp parallel shared(isSimple)
            {
                #pragma omp for schedule(dynamic, 1)
                    for(int i = 2; i < condidate / 2; i++)
                    {
                        if(condidate % i == 0)
                        {
                            isSimple = false;
                        }
                    }
            }
            #pragma omp barrier
            if(isSimple)
            {
                numberSimple++;
            }
        }
    }
    
    // Print the result
    std::cout << "The number of simple numbers: " << numberSimple << std::endl;

    return 0;
}