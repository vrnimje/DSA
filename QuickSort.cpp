#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int lidx, int ridx){
    int pivot = arr[ridx];
    int temp = lidx-1;
    for (int i=lidx; i<ridx; i++){
        if (arr[i] <= pivot){
            temp++;
            swap(&arr[temp], &arr[i]);
        }
    }
    swap(&arr[temp + 1], &arr[ridx]);
    return (temp + 1);
}

void quick_sort(int arr[], int lidx, int ridx){
    if (lidx < ridx){
        int pi = partition(arr, lidx, ridx);
        quick_sort(arr, lidx, pi - 1);
        quick_sort(arr, pi+1, ridx);
    }
    
}

void printArr(int arr[], int n){
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int arr[] = {12, 11, 13, 5, 6};
    int l = sizeof(arr)/sizeof(int);
    printArr(arr, l);
    quick_sort(arr, 0, l-1);
    cout<<"Sorted Array is:- "<<endl;
    printArr(arr, l);
}