#include "SquareMatrix.hpp"
#include <iostream>

SquareMatrix::SquareMatrix(int N)
{
    this->N = N;
    // Create dynamic 2D array
    squareMatrix = new double * [N];
    for (int i = 0; i < N; i++) 
    {
        squareMatrix[i] = new double [N];
    }
    //Full in with random numbers
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            squareMatrix[i][j] = rand() / 100000000.0;
        }
    }
}

SquareMatrix::~SquareMatrix()
{
    for (int i = 0; i < N; i++)
    {
        delete [] squareMatrix[i];
    }
    delete [] squareMatrix;
}

double SquareMatrix::getElement(int i, int j)
{
    if(i < 0 && i >= N && j < 0 && j >= N)
    {
        std::cout << "Wrong input for getElement" << std::endl;
        return -1;
    }
    else
    {
        return squareMatrix[i][j];
    }
} 

void SquareMatrix::setElement(int i, int j, double value)
{
    if(i < 0 && i >= N && j < 0 && j >= N)
    {
        std::cout << "Wrong input for setElement" << std::endl;
    }
    else
    {
        squareMatrix[i][j] = value;
    }
}

void SquareMatrix::printToConsole()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << squareMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void SquareMatrix::printElement(int i, int j)
{
    if(i < 0 && i >= N && j < 0 && j >= N)
    {
        std::cout << "Wrong input for printElement" << std::endl;
    }
    else
    {
        std::cout << squareMatrix[i][j] << std::endl;
    }
}