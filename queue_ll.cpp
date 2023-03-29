#include <iostream>
using namespace std;
 
struct qnode{
    int data;
    struct qnode *next;
};

class Queue{
    public:
    struct qnode *start = nullptr;

    void enqueue(int x){
        struct qnode *p = new struct qnode;
        p->data = x;
        p->next = NULL;
        if (start!=NULL){
            struct qnode *temp = new struct qnode;
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
    
    int dequeue(){
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

    void display_q(){
        if (start==NULL){
            cout<<"Queue is empty"<<endl;
        }

        else{
            struct qnode *p = new struct qnode;
            p = start;
            cout<<"Queue: ";
            while(p!= NULL){
                cout<<p->data<<" ";
                p = p->next;
            }
            cout<<endl;
        }
    }

    int front(){
        if (start != NULL){
            return start->data;
        }
        else{
            cout<<"Queue is empty"<<endl;
            return -1;
        }
    }

    int back(){
        if (start == NULL){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        else{
            struct qnode *temp = new struct qnode;
            temp = start;
            while(temp->next != NULL){
                temp = temp->next;
            }
            return temp->data;
        }
        
    }
};

int main(){
    Queue q;
    q.enqueue(23);
    q.enqueue(20);

    q.display_q();

    q.enqueue(4);

    q.display_q();

    cout<<"Element at front of the queue is: "<<q.front()<<endl;

    cout<<"Element at back of the queue is: "<<q.back()<<endl;

    cout<<"Dequeued element is: "<<q.dequeue()<<endl;

    q.display_q();

    q.dequeue();
    q.dequeue();
    
    q.display_q();
    return 0;
}