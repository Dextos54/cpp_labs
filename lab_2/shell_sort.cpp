#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

int fib(int n) {
    if (n + 1 <= 1)
        return n + 1;
    return fib(n - 1) + fib(n - 2);
}
 
int max_fib(int n){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 0;
    }
    for (int i = 0; i < n; i++){
        if ((fib(i) <= n) && fib(i + 1) >= n){
            return fib(i);
        }
    }
}



void insert_sort(int array[], int size){
    for (int i = 1; i < size; i++){
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;

    }
}


void shell_sort_one(int array[], int size){
    for (int interval = size/2; interval > 0; interval = interval / 2){
        for (int i = interval; i < size; i++){
            int key = array[i];
            int j = i - interval;
            
            while(j >= 0 && array[j] > key){
                array[j + interval] = array[j];
                j = j - interval;
            }
            array[j + interval] = key;
        }
    }  
}

void shell_sort_three(int array[], int size){
    for (int interval = max_fib(size); interval > 0; interval = max_fib(interval)){
        for (int i = interval; i < size; i++){
            int key = array[i];
            int j = i - interval;
            
            while(j >= 0 && array[j] > key){
                array[j + interval] = array[j];
                j = j - interval;
            }
            array[j + interval] = key;
        }
    }  
}


void shell_sort_two(int array[], int size){
    int k = std::log2(size);
    for (int interval = std::pow(2, k) - 1; interval > 0; interval = (interval + 1)/ 2 - 1){
        for (int i = interval; i < size; i++){
            int key = array[i];
            int j = i - interval;
            
            while(j >= 0 && array[j] > key){
                array[j + interval] = array[j];
                j = j - interval;
            }
            array[j + interval] = key;
        }
    }  
}



int main(){
    //int array[] = {1, 3, 3, 11, 21, 1, 45, 7, 6, 4};
    //shell_sort_two(array, 10);
    //for (int i = 0; i < 10; i++){
    //    std::cout << array[i] << " ";
    //}
    //std::cout << std::endl;


    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    int m;
    int a = 1000001;
    unsigned full_array[a];
    std::uniform_int_distribution<unsigned> dstr(0, a); // Make a random distribution

    for (unsigned i = 0; i < a; i++){
        m = dstr(rng);
        full_array[i] = m;
    }

    for (int n = 100; n < a; n = n * 5/4){
        {
            int small_array[n];
            for (int i = 0; i < n; i++){
                small_array[i] = full_array[i];
            }

            auto begin = std::chrono::steady_clock::now();
            shell_sort_one(small_array, n);
            auto end = std::chrono::steady_clock::now();

            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            int passed_time = time_span.count();
            std::cout << n << ", " << passed_time << ", ";





            {auto begin = std::chrono::steady_clock::now();
            shell_sort_two(small_array, n);
            auto end = std::chrono::steady_clock::now();


            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            int passed_time = time_span.count();
            std::cout << passed_time << ", ";}



            {auto begin = std::chrono::steady_clock::now();
            shell_sort_three(small_array, n);
            auto end = std::chrono::steady_clock::now();


            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            int passed_time = time_span.count();
            std::cout << passed_time << std::endl;}




        }
    }
    
}