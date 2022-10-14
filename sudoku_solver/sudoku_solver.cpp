#include <omp.h>
#include <iostream>
#include <fstream>

using namespace std;

#define SIZE 4

void readSudoku(int ** sudokuMap)
{
    // Open input file
    ifstream input = "";
    input.open("input.txt");

    string buffer;
    // Read from input file
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            input >> buffer;
            sudokuMap[i][j] = atoi(buffer);
        }

    // Close inpuit file
    input.close();
}

void writeSudoku(int** sudokuMap)
{
    // Open output file
    ifstream input;
    input.open("input.txt");

    string buffer = "";
    // Write from output file
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
             = atoi(buffer);

        }

    // Close outpuit file
    input.close();
}
// writeToFile()

// checkSolution()

// algorith of solution

int main (int argc, char *argv[])
{
    int sudokuMap[SIZE][SIZE] = {};

    

    
    return 0;
}