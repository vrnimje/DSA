#include <iostream>
#include <string>
using namespace std;
#define MAXSIZE 20
class Stack{
    public:
        int top = -1;
        int len = 0;
        int arr[MAXSIZE] = {};                
        bool isEmpty(){
            if (top==-1){
                return true;
            }
            else{
                return false;
            }
        }

        bool isFull(){
            if (top == MAXSIZE-1){
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
                len--;
                return arr[top--];
            }
        }

        void push(int ele){
            if(isFull()){
                cout<<"Stack Overflow"<<endl;
            }
            else{
                len++;
                arr[++top] = ele;
            }
        }

        void disp_stack(){
            cout<<"Stack: ";
            for(int i=0;i<len;i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
};

bool IsOperator(char c){
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/')){
        return true;
    }
    return false;
}


bool isOperand(char c){
    if ((c >= '0')&&(c <= '9')){
        return true;
    }
    else{
        return false;
    }
}

int find_res(int op1, char x, int op2){
    if (x == '+'){
        return op1+op2;
    }
    else if (x == '-'){
        return op1-op2;
    }
    else if (x == '/'){
        return op1/op2;
    }
    else if (x == '*'){
        return op1*op2;
    }
    return -1;

}

int postfix_eval(string exp){
    int k = 48; //Defining zero ascii value for char to int conversion
    Stack opr_stack;
    char ch = ' ';
    for(int i = 0;i<exp.length();i++){
        ch = exp[i];
        if (ch == ' '){
            continue;
        }
        else if (isOperand(ch)){
            opr_stack.push((int)ch-k);
        }
        else if (IsOperator(ch)){
            char op2 = opr_stack.pop();
            char op1 = opr_stack.pop();
            int res = find_res(op1,ch,op2);
            opr_stack.push(res);
        }
    }
    return opr_stack.pop();

}

int main(){
    string exp;
    cout<<"Enter the postfix expression: ";
    getline(cin,exp);
    cout<<"Result of evaluation is: "<<postfix_eval(exp)<<endl;
    return 0;
}

