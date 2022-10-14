#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

        void swapRowsSmall()
        {

        }

        void swapColumsSmall()
        {

        }

        void swapRowsArea()
        {

        }

        void swapColumsArea()
        {

        }
    public:
        SudokuGenerator(int N)
        {
            this->N = N;
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
                    table[i][j] = 0;
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

        void writeToFile(string fileName)
        {
            string fileSolutionName = "solution_";
            fileSolutionName.append(fileName);

            // Open the file
            ofstream resultFile;
            ofstream resultSolutionFile;
            resultFile.open(fileName);
            resultSolutionFile.open(fileSolutionName);

            // Write table to file in such way
            // 1 2 3 4\n
            // 3 4 1 2\n
            // 4 1 2 3\n
            // 2 3 4 1\n
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
                        resultFile << table[i][j] << endl; 
                        resultSolutionFile << tableSolution << endl;                     
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

/*import random
import solver


class grid:
	def __init__(self,n = 3):
		""" Generation of the base table """
		self.n = n
		self.table = [[ ((i*n + i/n + j) % (n*n) + 1) for j in range(n*n)] for i in range(n*n)]
		print "The base table is ready!"

	def __del__(self):
		pass
	
	def show(self):
		for i in range(self.n*self.n):
			print self.table[i]

	def transposing(self):
		""" Transposing the whole grid """
		self.table = map(list, zip(*self.table))

	def swap_rows_small(self):
		""" Swap the two rows """
		area = random.randrange(0,self.n,1)
		line1 = random.randrange(0,self.n,1)
		#получение случайного района и случайной строки
		N1 = area*self.n + line1
		#номер 1 строки для обмена

		line2 = random.randrange(0,self.n,1)
		#случайная строка, но не та же самая
		while (line1 == line2):
			line2 = random.randrange(0,self.n,1)

		N2 = area*self.n + line2
		#номер 2 строки для обмена

		self.table[N1],self.table[N2] = self.table[N2], self.table[N1]


	def swap_colums_small(self):
		grid.transposing(self)
		grid.swap_rows_small(self)
		grid.transposing(self)


	def swap_rows_area(self):
		""" Swap the two area horizon """
		area1 = random.randrange(0,self.n,1)
		#получение случайного района

		area2 = random.randrange(0,self.n,1)
		#ещё район, но не такой же самый
		while (area1 == area2):
			area2 = random.randrange(0,self.n,1)

		for i in range(0, self.n):
			N1, N2 = area1*self.n + i, area2*self.n + i
			self.table[N1], self.table[N2] = self.table[N2], self.table[N1]


	def swap_colums_area(self):
		grid.transposing(self)
		grid.swap_rows_area(self)
		grid.transposing(self)
	
	def mix(self,amt = 10):
		mix_func = ['self.transposing()', 
					'self.swap_rows_small()', 
					'self.swap_colums_small()', 
					'self.swap_rows_area()', 
					'self.swap_colums_area()']
		for i in xrange(1, amt):
			id_func = random.randrange(0,len(mix_func),1)
			eval(mix_func[id_func])

example = grid()
example.mix()

flook = [[0 for j in range(example.n*example.n)] for i in range(example.n*example.n)]
iterator = 0
difficult = example.n ** 4 #Первоначально все элементы на месте

example.show() 
print "---------------------------"

while iterator < example.n ** 4:
	i,j = random.randrange(0, example.n*example.n ,1), random.randrange(0, example.n*example.n ,1) # Выбираем случайную ячейку
	if flook[i][j] == 0:	#Если её не смотрели
		iterator += 1
		flook[i][j] = 1 	#Посмотрим

		temp = example.table[i][j]	#Сохраним элемент на случай если без него нет решения или их слишком много
		example.table[i][j] = 0
		difficult -= 1 #Усложняем если убрали элемент

		table_solution = []
		for copy_i in range(0, example.n*example.n):
			table_solution.append(example.table[copy_i][:]) #Скопируем в отдельный список

		i_solution = 0
		for solution in solver.solve_sudoku((example.n, example.n), table_solution):
			i_solution += 1 #Считаем количество решений

		if i_solution != 1: #Если решение не одинственное вернуть всё обратно
			example.table[i][j] = temp
			difficult += 1 # Облегчаем

example.show()
print "difficult = ",difficult*/