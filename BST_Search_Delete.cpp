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

void search(struct node *root, int data){
    if (root == NULL){
        cout<<"NULL"<<endl;
        cout<<"Element doesn't exist in tree"<<endl;
        return;
    }
    if (root->data == data){
        cout<<data<<endl;
        return;
    }
    else if (data < root->data){
        cout<<(root->data)<<"->";
        search(root->left,data);
    }
    else if (data > root->data){
        cout<<(root->data)<<"->";
        search(root->right,data);
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

struct node* inord_succ(struct node *root){
    struct node *curr = root;
    while(curr && curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}   

struct node* deletion(int x, struct node *root){
    if (root == NULL){
        return root;
    }

    if (x < root->data){
        root->left = deletion(x,root->left);
    }
    else if (x > root->data){
        root->right = deletion(x,root->right);
    }
    else{
        struct node *temp = new struct node;
        if (root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }
        temp = inord_succ(root->right);
        root->data = temp->data;
        root->right = deletion(temp->data,root->right);
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
    int data;
    cout<<"Enter key to be searched: ";
    cin>>data;
    search(root,data);
    cout<<"Enter node to be deleted: ";
    cin>>data;
    root = deletion(data, root);
    cout<<"Pre-order traversal of tree after deletion is: "<<endl;
    traversal(root);
    cout<<endl;
    return 0;
}