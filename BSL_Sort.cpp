#include <iostream>
using namespace std;

struct node{
    int data;
    struct node *left, *right;
};

void traversal(struct node *root){
    if (root != NULL){
        cout<<root->data<<" ";
        traversal(root->left);
        traversal(root->right);
    }
}

struct node* insert(int x, struct node *root){
    if (root == NULL){
        struct node *temp = new struct node;
        temp->data = x;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    else if (x < root->data){
        root->left = insert(x,root->left);
    }
    else if (x > root->data){
        root->right = insert(x,root->right);
    }
    return root;
}


int main(){
    struct node *root = nullptr;
    int arr[8] = {8, 3, 10, 1, 6, 14, 4, 7};
    for(int i=0; i<8; i++){
        root = insert(arr[i], root);
    }
    cout<<"Pre-order traversal of tree is:"<<endl;
    traversal(root);
    cout<<endl;
    return 0;
}