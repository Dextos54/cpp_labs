#include <iostream>
#define N 10



void merge(int array[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1];
    int R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];

    
    int i = 0, j = 0;
    int k = l;

    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}


void merge_sort(int array[], int l, int r){
    if (l >= r){
        return;
    }
    int m = l + (r - l)/ 2;
    merge_sort(array, l, m);
    merge_sort(array, m + 1, r);
    merge(array, l, m, r);

}

void selection_sort(int array[], int size){
    for (int i = 0; i < N; i++){
        int min_ind = i;
        for (int j = i + 1; j < N; j++){
            if (array[j] < array[min_ind]){
                min_ind = j;
            }
        }
        std::swap(array[i], array[min_ind]);
    }
}

void insert_sort(int array[], int size){
    for (int i = 1; i < N; i++){
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;

    }
}

void bubble_sort(int array[], int size){
    for (int i = 0; i < N; i++){
        for (int i = 0; i < N - 1; i++){
            if (array[i] > array[i + 1]){
                std::swap(array[i], array[i + 1]);
            }
        }
    }
}