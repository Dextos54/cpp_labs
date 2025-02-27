#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>


void func(int n) {
    std::cout<< "Hellow world" << "\n";
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

unsigned binary_search(int data[], unsigned l_idx, unsigned r_idx, int key){ // Binary search
    auto fail_idx = r_idx;
    while(l_idx < r_idx){
        unsigned pivot_idx = (l_idx + r_idx)/ 2;
        if (key < data[pivot_idx]){
            r_idx = pivot_idx;
        }else if (data[pivot_idx < key]) {
            l_idx = pivot_idx + 1;
        } else {
            return pivot_idx;
        }
    }
    return fail_idx;
}



int timer(int n) {  // Function for measuring time it takes
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 100000; cnt != 0; --cnt){
        func(n);        
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    return time_span.count();
}

int find_random (int arr[]){
    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0,9);

    return arr[dstr(rng)];
}
int another_find_random(int n){
    return std::rand() % n;
}

int main(){
    int n;
    std::cin >> n;

    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0,n); // Make a random distribution 


    int data_sorted[n]; // Make a sorted array 
    for (int i = 0; i < n; i++){
        data_sorted[i] = i;
    }
    int indx, key;
    auto begin = std::chrono::steady_clock::now();

    
    for (unsigned cnt = 10000; cnt != 0; --cnt){ //cnt=10000000 for binary_search, cnt = 10000 for search
        key = data_sorted[dstr(rng)]; // Choose a random key
        indx = search(data_sorted, 0, n, key); // Use an algorithm to find it (binary or other one)
    }

    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    int passed_time = time_span.count();
    std::cout << passed_time << std::endl;
    return 0;
}