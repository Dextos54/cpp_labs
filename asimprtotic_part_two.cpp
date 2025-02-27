#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#define N 2000


void find_complinary(int data[], int m){
    bool found = false;
    for (int i = 0; i < N; i++){
        if (found){break;}
        int comp = m - data[i];
        for (int j = 0; j < N; j++){
            if (data[j] == comp){
                found = true;
                //std::cout << i << " " << j << std::endl;
                break;
            }
        }
    }
    if (!found){
        //std::cout << -1 << std::endl;
    }
}

void find_complinary_in_sorted(int data[], int m){
    int l_ind = 0;
    int r_ind = N - 1;

    bool found = false;
    
    while (l_ind != r_ind){
        int sum = data[l_ind] + data[r_ind];
        if (sum > m){
            r_ind = r_ind - 1;
        }else if(sum < m){
            l_ind = l_ind + 1;
        }else{
            //std::cout << l_ind << " " << r_ind << std::endl;
            found = true;
            break;
        }
    }
    if (!found){
        //std::cout << -1 << std::endl;
    }
    

}

int main(){

    unsigned seed = 1538;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, 2*N); // Make a random distribution 

    int data_sorted[N]; // Make a sorted array 
    for (int i = 0; i < N; i++){
        data_sorted[i] = i;
    }

    int m;

    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 1000; cnt != 0; cnt--){ // we use cnt=1000 for linear and cnt = 100000 for binary
        m = dstr(rng);
        find_complinary(data_sorted, m); //find_complinary for linear and find_complinary_in_sorted for binary
    }

    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    int passed_time = time_span.count();
    std::cout << passed_time << std::endl;
    return 0;



}