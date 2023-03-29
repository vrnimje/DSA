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
    if (start!=NULL){
        struct node *temp = new struct node;
        temp = start;
        while(temp->next != start){
            temp = temp->next;
        }
        temp->next = p;
        p->next = start;
    }
    else{
        start = p;
        p->next = start;
    }
}
 
int deleteNode(int x){
    if (start == NULL){
        cout<<"CLL UNDERFLOW"<<endl;
        return -1;
    }
    else{
        if (start->data == x){
            struct node *temp = start->next;
            while(temp->next != start){
                temp = temp->next;
            }
            start = start->next;
            temp->next = start;
            
        }
        else{
            struct node *temp = new struct node, *prev = new struct node;
            temp = start->next;
            prev = start;
            while ((temp->data != x)&&(temp->next!=start)){
                prev = temp;
                temp = temp->next;
            }

            if (temp->next!=start){
                prev->next = temp->next;
            } 
            else{
                if (temp->data == x){
                    prev->next = start;
                }
                else{
                    cout<<"Node not found"<<endl;
                    return -1;
                }
            }
        }
        return x;
    }
}

void display_ll(){
    if (start==NULL){
        cout<<"Linked list is empty"<<endl;
    }

    else{
        struct node *p = new struct node;
        p = start;
        cout<<p->data<<"->";
        p = p->next;
        while(p->next!= start){
            cout<<p->data<<"->";
            p = p->next;
        }
        cout<<"(head node)";
        cout<<endl;
    }
}

int main(){
    int x;
    cout<<"Given circular linked list: "<<endl;
    int arr[5] = {2,5,7,8,10};
    for(int i=0;i<=5;i++){
        insert_at_end(arr[i]);
    }
    display_ll();
    cout<<"Enter the node to be deleted: ";
    cin>>x;
    int r = deleteNode(x);
    cout<<"Circular Linked list after linked list: "<<endl;
    display_ll();
    cout<<"Data: "<<r<<endl;
    return 0;
}