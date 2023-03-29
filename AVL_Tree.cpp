#include <iostream>
using namespace std;

#define COUNT 5;

struct Node{ 
    int info;
    struct Node *left;
    struct Node *right;
    int height;
};

struct Node* head = nullptr;

int height(struct Node* root){
    if (root == NULL){
        return 0;
    }
    return root->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

struct Node *RRotate(struct Node *root){
    struct Node* a = root->left;
    struct Node* temp = a->right;
    a->right = root;
    root->left = temp;
    root->height = max(height(root->left), height(root->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}

struct Node *LRotate(struct Node *root){
    struct Node* a = root->right;
    struct Node* temp = a->left;
    a->left = root;
    root->right = temp;
    root->height = max(height(root->left), height(root->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}

int getBalanceFactor(struct Node* root){
    if (root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);
    
}

struct Node* insert(int x, struct Node *root){
    if (root == NULL){
        struct Node* temp = new struct Node;
        temp->info = x;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->height = 1;
        return temp;
    }
    else if (x < root->info){
        root->left = insert(x, root->left);
    }
    else if (x > root->info){
        root->right = insert(x, root->right);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance_factor = getBalanceFactor(root);
    
    if (balance_factor > 1){
        if (x < root->left->info){
            return RRotate(root);
        }
        else if (x > root->left->info){
            root->left = LRotate(root->left);
            return RRotate(root);
        } 
    }
    else if (balance_factor < -1){
        if (x > root->right->info){
            return LRotate(root);
        }
        else if (x < root->right->info){
            root->right = RRotate(root->right);
            return LRotate(root);
        }
    }
    return root;
}

struct Node* inord_succ(struct Node *root){
    struct Node *curr = root;
    while(curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}   

struct Node* deleteNode(struct Node* root, int x){
    if (root==nullptr){
        return root;
    }

    else if (x < root->info){
        root->left = deleteNode(root->left, x);
    }

    else if (x > root->info){
        root->right = deleteNode(root->right, x);
    }

    else{
        if ((root->right == NULL)||(root->left == NULL)){
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
            }
            free(temp);
        }
        else{
            struct Node* temp = inord_succ(root->right);
            root->info = temp->info;
            root->right = deleteNode(root->right, temp->info);
        }
    }

    if (root == NULL){
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance_factor = getBalanceFactor(root);

    if (balance_factor > 1){
        if (getBalanceFactor(root->left) >= 0){
            return RRotate(root);
        }
        else{
            root->left = LRotate(root->left);
            return RRotate(root);
        }
    }
    else if (balance_factor < -1){
        if (getBalanceFactor(root->right) <= 0){
            return LRotate(root);
        }
        else{
            root->right = RRotate(root->right);
            return LRotate(root);
        }
    }
    return root;
}

void printTree(struct Node* root, int space) {
    if (root != nullptr) {
        space += COUNT;
        printTree(root->right, space);
        cout<<endl;
        for(int i=0; i<space; i++){
            cout<<" ";
        }
        cout<<root->info<<endl;
        printTree(root->left, space);
    }
}

int main(){
    head = insert(33, head);
    head = insert(13, head);
    head = insert(53, head);
    head = insert(9, head);
    head = insert(21, head);
    head = insert(61, head);
    head = insert(8, head);
    head = insert(11, head);
    printTree(head, 0);
    cout<<endl;
    head = deleteNode(head, 9);
    cout << "After deleting 9" << endl;
    printTree(head, 0);
    cout<<endl;
    head = deleteNode(head, 53);
    cout << "After deleting 53" << endl;
    printTree(head, 0);
    cout<<endl;
    return 0;
}