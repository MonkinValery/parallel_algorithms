#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

class SudokuGenerator
{
    private:
        int** table;
        int** tableSolution;
        int N;

        void transposing()
        {
            int tempValue = 0;
            for(int i = 0; i < N; i++)
                for(int j = i; j < N; j++)
                {
                    tempValue = table[i][j];
                    table[i][j] = table[j][i];
                    table[j][i] = tempValue;

                    tempValue = tableSolution[i][j];
                    tableSolution[i][j] = tableSolution[j][i];
                    tableSolution[j][i] = tempValue;
                } 
        }

        void swapRows()
        {
            /*Swap Rows in random area*/

            // random values from 0 to sqrt(N) + 0
            int areaSize = (int)sqrt(N);
            int area = 0 + rand() % areaSize;
            int firstLine = 0 + rand() % areaSize;
            int secondLine = 0 + rand() % areaSize;

            while(firstLine == secondLine)
            {
                secondLine = 0 + 0 + rand() % areaSize;
            }

            firstLine += area * areaSize;
            secondLine += area * areaSize;

            int tempValue = 0;
            for(int j = 0; j < N; j++)
            {
                tempValue = table[firstLine][j];
                table[firstLine][j] = table[secondLine][j];
                table[secondLine][j] = tempValue;

                tempValue = tableSolution[firstLine][j];
                tableSolution[firstLine][j] = tableSolution[secondLine][j];
                tableSolution[secondLine][j] = tempValue;
            }
        }

        void swapColums()
        {
            /*Swap colums in random area*/

            transposing();
            swapRows();
            transposing();
        }

        void swapAreaRows()
        {
            /*Swap random rows of areas*/

            int areaSize = (int)sqrt(N);
            int firstArea = 0 + rand() % areaSize;
            int secondArea = 0 + rand() % areaSize;

            while(firstArea == secondArea)
            {
                secondArea = 0 + rand() % areaSize;
            }

            int tempValue = 0;
            for(int i = 0; i < areaSize; i++)
                for(int j = 0; j < N; j++)
                {
                    tempValue = table[i + firstArea * areaSize][j];
                    table[i + firstArea * areaSize][j] = table[i + secondArea * areaSize][j];
                    table[i + secondArea * areaSize][j] = tempValue;

                    tempValue = tableSolution[i + firstArea * areaSize][j];
                    tableSolution[i + firstArea * areaSize][j] = tableSolution[i + secondArea * areaSize][j];
                    tableSolution[i + secondArea * areaSize][j] = tempValue;
                }
        }

        void swapAreaColums()
        {
            transposing();
            swapAreaRows();
            transposing();
        }
    public:
        SudokuGenerator(int _N)
        {
            N = _N;
            // Create dynamic 2D array
            table = new int * [N];
            tableSolution = new int * [N];
            for (int i = 0; i < N; i++) 
            {
                table[i] = new int [N];
                tableSolution[i] = new int [N];
            }

            //Full in defalt tables
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    table[i][j] = i * + j *;
                    tableSolution[i][j] = 0;
                }
            }
        }

        ~SudokuGenerator()
        {
            for (int i = 0; i < N; i++)
            {
                delete [] table[i];
                delete [] tableSolution[i];
            }
            delete [] table;
            delete [] tableSolution;
        }

        void writeToFile(std::string& fileName)
        {
            std::string fileSolutionName = "solution_";
            fileSolutionName.append(fileName);

            // Open the file
            std::ofstream resultFile;
            std::ofstream resultSolutionFile;
            resultFile.open(fileName);
            resultSolutionFile.open(fileSolutionName);

            // Write table to file in such way
            // 1 2 3 4\n
            // 3 4 1 2\n
            // 2 3 4 1\n
            // 4 1 2 3\n
            // i stands for rows
            // j stands for colums
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                {
                    if(j != N - 1)
                    {
                        resultFile << table[i][j] << " ";
                        resultSolutionFile << tableSolution[i][j] << " ";
                    }
                    else
                    {
                        resultFile << table[i][j] << std::endl; 
                        resultSolutionFile << tableSolution << std::endl;                     
                    }
                }

            // Close file
            resultFile.close();
            resultSolutionFile.close();
        }

        void mix()
        {

        }
};