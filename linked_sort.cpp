#include <iostream>
using namespace std;
 
struct node{
    int data;
    struct node *next;
};
 
struct node *start = nullptr;

void insert_at_end(int x){
    struct node *p = new struct node;
    p->data = x;
    p->next = NULL;
    if (start!=NULL){
        struct node *temp = new struct node;
        temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
    else{
        start = p;
    }
}
 
int delete_from_front(){
    if (start == NULL){
        cout<<"QUEUE UNDERFLOW"<<endl;
        return -1;
    }
    else{
        int x = start->data;
        start = start->next;
        return x;
    }
}

void sort_ll(){
    if (start == NULL){
        cout<<"Array is empty"<<endl;
    }
    else{
        struct node *current = start, *index;
        int temp;
        while(current != NULL){
            index = current->next;
            while(index != NULL){
                if (current->data < index->data){
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void display_ll(){
    if (start==NULL){
        cout<<"Array is empty"<<endl;
    }

    else{
        struct node *p = new struct node;
        p = start;
        while(p!= NULL){
            cout<<p->data<<" ";
            p = p->next;
        }
        cout<<endl;
    }
}

int main(){
    int arr[10] = {10, 8, 6, 7, 5, 3, 1, 2, 4, 9};
    for(int i=0;i<10;i++){
        insert_at_end(arr[i]);
    }
    cout<<"Unsorted list: "<<endl;
    display_ll();
    sort_ll();
    cout<<"Sorted list: "<<endl;
    display_ll();
    return 0;
}

