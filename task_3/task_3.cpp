#include <omp.h>
#include <iostream>

int main (int argc, char *argv[])
{   
    int array_size = 100000;
    double init_array[array_size]{0};
    for(int i = 0; i < array_size; i++)
    {
        init_array[i] = i;
    }

    int index = 0;

    #pragma omp parallel default(shared) private(index)
    {
        double left_num, temp_left_num, left_border_num, right_border_num = 0;
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int begin_index, end_index = 0;

        if(thread_num == 0)
        {
            begin_index = 0;
            end_index = (array_size / num_threads) * (thread_num + 1);
            left_border_num = init_array[begin_index];
            right_border_num = init_array[end_index + 1];
        }
        else if(thread_num == num_threads - 1)
        {
            begin_index = (array_size / num_threads) * thread_num + 1;
            end_index = array_size - 1;
            left_border_num = init_array[begin_index-1];
            right_border_num = init_array[end_index];
        }
        else
        {
            begin_index = (array_size / num_threads) * thread_num + 1;
            end_index = (array_size / num_threads) * (thread_num + 1);
            left_border_num = init_array[begin_index-1];
            right_border_num = init_array[end_index+1];
        }

        #pragma omp barrier

        left_num = init_array[begin_index];
        init_array[begin_index] = left_border_num * init_array[begin_index] * init_array[begin_index + 1] / 3;

        for(index = begin_index + 1; index <= end_index - 1; index++)
        {
            temp_left_num = init_array[index];
            init_array[index] = left_num * init_array[index] * init_array[index + 1] / 3;
            left_num = temp_left_num;
        }

        init_array[end_index] = left_num * init_array[end_index] * right_border_num / 3;
   
    }
    
    return 0;
}