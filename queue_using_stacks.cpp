#include <iostream>
using namespace std;
#define MAXSIZE 20
class Stack{
    public:
        int top = -1;
        int arr[MAXSIZE];                
        bool isEmpty(){
            if (top==-1){
                return true;
            }
            else{
                return false;
            }
        }

        bool isFull(){
            if (top==MAXSIZE-1){
                return true;
            }
            else{
                return false;
            }
        }

        int peek(){
            if(!isEmpty()){
                return arr[top];
            }
            else{
                return -1;
            }
        }

        int pop(){
            if(isEmpty()){
                cout<<"Stack Underflow"<<endl;
                return -1;
            }
            else{
                return arr[top--];
            }
        }

        void push(int ele){
            if(isFull()){
                cout<<"Stack Overflow"<<endl;
            }
            else{
                arr[++top] = ele;
            }
        }
};

class Queue{
    public:
        int len = 0;
        Stack stk1,stk2;
        void enqueue(int ele){
            if (!stk1.isFull()){
                stk1.push(ele);
                len++;
            }
            else{
                cout<<"Queue Overflow"<<endl;
            }
        }

        int dequeue(){
            if (stk1.isEmpty()){
                cout<<"Queue Underflow"<<endl;
                return -1;
            }
            else{
                while(!stk1.isEmpty()){
                    int x = stk1.pop();
                    stk2.push(x);
                }

                int res = stk2.pop();
                while(!stk2.isEmpty()){
                    int x = stk2.pop();
                    stk1.push(x);
                }
                len--;
                return res;
            }
        }

        int rear(){
            if (stk1.isEmpty()){
                cout<<"Queue Underflow"<<endl;
                return -1;
            }
            else{
            return stk1.peek();
            }                                
        }

        int front(){
            if (stk1.isEmpty()){
                cout<<"Queue Underflow"<<endl;
                return -1;
            }
        else{
                while(!stk1.isEmpty()){
                    int x = stk1.pop();
                    stk2.push(x);
                }
                int res = stk2.peek();
                while(!stk2.isEmpty()){
                    int x = stk2.pop();
                    stk1.push(x);
                }
                return res;
            }
        }

        void disp_queue(){
            cout<<"Queue: ";
            for(int i=0;i<len;i++){
                cout<<stk1.arr[i]<<" ";
            }
            cout<<endl;
        }
};

int main(){
    Queue q;
    q.enqueue(2);
    q.enqueue(4);
    q.enqueue(5);
    q.disp_queue();
    cout<<"Element at front of the queue is: "<<q.front()<<endl;
    cout<<"Element at rear of the queue is: "<<q.front()<<endl;
    cout<<"Dequeued element is: "<<q.dequeue()<<endl;
    q.disp_queue();
    q.dequeue();
    q.disp_queue();

}

