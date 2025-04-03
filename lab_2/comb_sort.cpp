#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>


bool forward_step(unsigned array[], int size, int step, bool disorder){
    for (int i = 0; i + step < size; i= i + step){
        if (array[i] > array[i + step]){
            disorder = true;
            std::swap(array[i], array[i + step]);
        }
    }
    return disorder;
}

void comb_sort(unsigned array[], int size){
    int step = size;
    bool disorder = false;

    while ((step > 1) || disorder){
        if (step > 1){
            step = step / 2;
        }
        disorder = false;
        disorder = forward_step(array,  size, step, disorder);
    }
}  


int main(){
    //unsigned array[] = {7, 9, 1, 5, 6, 2, 3, 10, 4};
    int n = 9;
    //comb_sort(array, n);
    //for (int i = 0; i < n; i++){
    //    std::cout << array[i] << " ";
    //}
    //std::cout << std::endl;

    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    int m;
    int a = 100001;
    unsigned full_array[a];
    std::uniform_int_distribution<unsigned> dstr(0, a); // Make a random distribution



    for (unsigned i = 0; i < a; i++){
        m = dstr(rng);
        full_array[i] = m;
    }

    for (int n = 100; n < a; n = n * 5/4){
        {
            unsigned small_array[n];
            for (int i = 0; i < n; i++){
                small_array[i] = full_array[i];
            }
            auto begin = std::chrono::steady_clock::now();
            comb_sort(small_array, n);
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            int passed_time = time_span.count();
            std::cout << passed_time << ", " << n << std::endl;

        }
    }
}