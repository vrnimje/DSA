#include <iostream>
using namespace std;

void insertion_sort(int arr[], int n){
    int temp;
    for(int i=1; i<n; i++){
        temp = arr[i];
        int j = i-1;
        while(j>=0 && temp <= arr[j]){
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = temp;
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
    insertion_sort(arr, l);
    cout<<"Sorted Array is:- "<<endl;
    printArr(arr, l);
}