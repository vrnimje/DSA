#include <iostream>
using namespace std;

int BinarySearch(int arr[], int l, int h, int e){
    if (l>h){
        return -1;
    }
    else{
        int mid = l + (h-l)/2;
        if (arr[mid] == e){
            return mid;
        }
        else if (e > arr[mid]){
            BinarySearch(arr, mid + 1, h, e);
        }
        else if (e < arr[mid]){
            BinarySearch(arr, l, mid - 1, e);
        }
    }

}

int main(){
    int arr[10];
    cout<<"Enter elements of the array in sorted order: ";
    int len = 10;
    for(int i=0; i<len; i++){
        cin>>arr[i];
    }
    cout<<"Enter element to be searched: ";
    int x;
    cin>>x;
    int res = BinarySearch(arr, 0, len-1, x);
    if (res == -1){
        cout<<x<<" not found in the array"<<endl;
    }
    else{
        cout<<x<<" found at index "<<res<<" of the array"<<endl;
    }
    return 0;
}