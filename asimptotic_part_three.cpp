#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <algorithm>
#define N 5000


void swap_elements(int (&arr)[N], int a, int b){
    arr[a] = arr[a] + arr[b];
    arr[b] = arr[a] - arr[b];
    arr[a] = arr[a] - arr[b];
}

unsigned search(int data[], unsigned l_idx, unsigned r_idx, int key){
    auto fail_idx = r_idx;
    while(l_idx < r_idx){
        if (key == data[l_idx]){
            return l_idx;
        }else{
            l_idx = l_idx + 1;
        }
    }
    return fail_idx;
}

void strategy_a(int (&data)[N], int key){
    int found_index = search(data, 0, N, key);
    if ((found_index != 0) && (found_index!=N)){
        swap_elements(data, 0, found_index);
    }
}


void strategy_b(int (&data)[N], int key){
    int found_index = search(data, 0, N, key);
    if ((found_index != 0) && (found_index!= N)){
        swap_elements(data, found_index - 1, found_index);
    }
}

void strategy_c(int (&data)[N], int (&ind)[N], int key){
    int found_index = search(data, 0, N, key);
    if (found_index != N){
        ind[found_index] = ind[found_index] + 1;
    }
    if((found_index != 0) && (found_index!= N)){
        if (ind[found_index] > ind[found_index - 1]){
            swap_elements(data, found_index, found_index - 1);
            swap_elements(ind, found_index, found_index - 1);
        }
    }
}



int main(){
    int data_sorted[N]; // Make a sorted array 
    for (int i = 0; i < N; i++){
        data_sorted[i] = i;
    }

    int counter[N];
    for (int i = 0; i < N; i++){
        counter[i] = 0;
    }

    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N); // Make a random distribution
    int m;

    int a = 100000;
    auto begin = std::chrono::steady_clock::now();

    //for (unsigned cnt = a; cnt != 0; cnt--){ we use for random 
    //    m = dstr(rng);
    //    strategy_c(data_sorted, counter, m);
    //}


    for (unsigned cnt = a/2; cnt != 0; cnt--){ // we use for not random
        m = dstr(rng);
        search(data_sorted, 0, N, m);
    }

    for (unsigned cnt = a/2; cnt != 0; cnt--){
        search(data_sorted, 0, N, 50);
    }
    
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    int passed_time = time_span.count();
    std::cout << passed_time << std::endl;

    return 0;
}