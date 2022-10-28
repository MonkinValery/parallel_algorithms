#include <omp.h>
#include <iostream>
#include <fstream>

void quickSort(int* array, int size) {
  long i = 0, j = size-1;
  int pivot = array[size / 2];
  do {
    while (array[i] < pivot) {
        i++;
    }
    while (array[j] > pivot) {
        j--;
    }
    if (i <= j) {
      std::swap(array[i], array[j]);
      i++; j--;
    }
  } while (i <= j);
  #pragma omp task shared(array)
  {
    if (j > 0) {
      quickSort(array, j+1);
    }
  }
  #pragma omp task shared(array)
  {
    if (size > i) {
      quickSort(array + i, size - i);
    }
  }
  #pragma omp taskwait
}

bool isSorted(int* array, int N)
{
    for(int i = 1; i < N; i++)
    {
        if(array[i-1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool isReverseSorted(int* array, int N)
{
    for(int i = 1; i < N; i++)
    {
        if(array[i-1] <= array[i])
        {
            return false;
        }
    }
    return true;
}

bool isAllSame(int* array, int N)
{
    for(int i = 1; i < N; i++)
    {
        if(array[i-1] != array[i])
        {
            return false;
        }
    }
    return true;
}
void readArrayFromFile(int* array, std::string fileName)
{
    std::ifstream inputFile(fileName);
    std::string line;
    if (inputFile.is_open())
    {
        for (int i = 0; getline (inputFile,line); i++)
        {
        array[i] = std::stoi(line);
        }
        inputFile.close();
    }
}

void readFromConsole(int* array, int size)
{
    std::cout << "Print numbers for array of " << size << "elements." << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }
}

void printArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }
}

int main(int argc, char *argv[])
{
    int N = 0;

    // Read the size of array
    if(argv[1] != nullptr){
        N = std::stoi(argv[1]);
        if(N > 10000)
        {
            std::cout << "Too big size." << std::endl;
        }
        if(N < 1)
        {
            std::cout << "Size less than zero." << std::endl;
        }
    }
    else{
        std::cout << "Wrong input." << std::endl;
        return -1;
    }
    
    // Create array
    int* array = new int [N];

    // Read array
    readArrayFromFile(array, "example.txt");
    // readFromConsole(array, N); // To read from console

    // Check array
    if(N == 1)
    {
        std::cout << "Array of 1 element." << std::endl;
        return 0;
    }
    else if(isSorted(array, N) && isAllSame(array, N))
    {
        std::cout << "Array is already sorted." << std::endl;
        return 0;
    }
    else if(isReverseSorted(array, N))
    {
        int tempValue = 0;
        for(int i = 0; i < N/2; i++)
        {
            tempValue = array[i];
            array[i] = array[N - 1 - i];
            array[N -1 - i] = tempValue;
        }
    }

    // Sort array
    #pragma omp parallel shared(array)
    {
        #pragma omp single nowait
        {
            quickSort(array, N);
        }
    }

    printArray(array, N);

    delete [] array;
}