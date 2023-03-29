#include <iostream>
using namespace std;

#define COUNT 5;

struct node{ 
    int info;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node* root){
    if (root == NULL){
        return 0;
    }
    return root->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

struct node *RRotate(struct node *root){
    struct node* a = root->left;
    struct node* temp = a->right;
    a->right = root;
    root->left = temp;
    root->height = max(height(root->left), height(root->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}

struct node *LRotate(struct node *root){
    struct node* a = root->right;
    struct node* temp = a->left;
    a->left = root;
    root->right = temp;
    root->height = max(height(root->left), height(root->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}

int getBalanceFactor(struct node* root){
    if (root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);
    
}

struct node* insert(int x, struct node *root){
    if (root == NULL){
        struct node* temp = new struct node;
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

void printTree(struct node* root, int space) {
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

void inord_arr(struct node* root, int inorder[], int* index_ptr){
    if (root == NULL){
        return;
    }
    inord_arr(root->left, inorder, index_ptr);
    inorder[*index_ptr] = root->info;
    (*index_ptr)++;
    inord_arr(root->right, inorder, index_ptr);
}

struct node* sortedArr_to_AVL(int arr[], int start, int end){
    if (start>end){
        return nullptr;
    }
    int mid = (start+end)/2;
    struct node* root = new struct node;
    root->info = arr[mid];
    root->left = sortedArr_to_AVL(arr, start, mid-1);
    root->right = sortedArr_to_AVL(arr, mid+1, end);
    return root;
}

int *merge(int arr1[], int arr2[], int m, int n){
    int *merged = new int[m+n];
    int i=0, j=0, l=0;

    while(i<m && j<n){
        if (arr1[i]<arr2[j]){
            merged[l] = arr1[i];
            i++;
        }
        else{
            merged[l] = arr2[j];
            j++;
        }
        l++;
    }
    while(i<m){
        merged[l] = arr1[i];
        i++;
        l++;
    }
    while(j<n){
        merged[l] = arr2[j];
        j++;
        l++;
    }
    return merged;
}

struct node* merge_AVL(struct node* root1, struct node* root2, int m, int n){
    int *arr1 = new int[m];
    int i = 0;
    inord_arr(root1, arr1, &i);

    int *arr2 = new int[n];
    int j = 0;
    inord_arr(root2, arr2, &j);

    int *merged_arr = merge(arr1, arr2, m, n);
    return sortedArr_to_AVL(merged_arr, 0, m + n - 1);
}

int main(){
    struct node* head1 = nullptr;
    head1 = insert(100, head1);
    head1 = insert(50, head1);
    head1 = insert(20, head1);
    head1 = insert(101, head1);
    head1 = insert(70, head1);
    cout<<"1st tree: "<<endl;
    printTree(head1, 0);

    struct node* head2 = nullptr;
    head2 = insert(80, head2);
    head2 = insert(120, head2);
    head2 = insert(40, head2);
    head2 = insert(71, head2);
    cout<<"2nd tree: "<<endl;
    printTree(head2, 0);

    struct node* res = merge_AVL(head1, head2, 5, 3);
    cout<<"Resultant AVL Tree: "<<endl;
    printTree(res, 0);
    return 0;
}