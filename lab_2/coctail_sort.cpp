#include <iostream>
#include <algorithm>



bool forward_step(unsigned array[], unsigned left, unsigned right, bool disorder){
    for (int i = left; i < right; i++){
        if (array[i] > array[i + 1]){
            std::swap(array[i], array[i + 1]);
            disorder = true;
        }
    }
    return disorder;
}



bool backward_step(unsigned array[], unsigned left, unsigned right, bool disorder){
    for (int i = right; i > left; i--){
        if (array[i - 1] > array[i]){
            std::swap(array[i - 1], array[i]);
            disorder = true;
        }
    }
    return disorder;
}

void shaker_sort(unsigned array[], int size){
    int left = 0;
    int right = size - 1;

    bool disorder = true;

    while ((left < right) && disorder){
        disorder = false;
        disorder = forward_step(array, left, right, disorder);
        right--;
        disorder = backward_step(array, left, right, disorder);
        left++;
    }

}


int main(){
    unsigned array[] = {7, 9, 1, 5, 6, 2, 3, 10, 4};
    int n = 9;
    shaker_sort(array, n);
    for (int i = 0; i < n; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    unsigned array1[] = {7, 9, 1, 5, 6, 2, 3, 10, 4};
    forward_step(array1, 0, n, false);

    for (int i = 0; i < n; i++){
        std::cout << array1[i] << " ";
    }
    std::cout << std::endl;


    unsigned array2[] = {7, 9, 1, 5, 6, 2, 3, 10, 4};
    backward_step(array2, 0, n, false);

    for (int i = 0; i < n; i++){
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;

}