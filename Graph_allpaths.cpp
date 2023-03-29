#include <iostream>
#include <iomanip>
using namespace std;

struct node{
    int vertex;
    int weight;
    struct node* next;
};


struct node* createNode(int x, int w){
    struct node* root = new struct node;
    root->vertex = x;
    root->weight = w;
    root->next = nullptr; 
    return root;
}

struct Graph{
    int n;
    struct node* arr[];
};

struct Graph* createGraph(int x){
    struct Graph* gr = new struct Graph;
    gr->n = x;
    for(int i=0; i<gr->n; i++){
        gr->arr[i] = new struct node;
        gr->arr[i] = nullptr; 
    }
    return gr;
}

void addEdge(struct Graph* gr, int s, int d, int w){
    struct node* temp = createNode(d, w);
    temp->next = gr->arr[s];
    gr->arr[s] = temp;
    temp = createNode(s, w);
    temp->next = gr->arr[d];
    gr->arr[d] = temp;
}

void printGraph(struct Graph* gr){
    for(int i = 0; i < gr->n; i++){
        struct node* temp = gr->arr[i];
        cout<<"Vertex:"<<i<<":-";
        while(temp!=NULL){
            cout<<"|"<<temp->vertex<<","<<temp->weight<<"|->";
            temp = temp->next;
        }
        cout<<endl;
    }
}

void recurPaths(int s, int d, int* cost, bool done[], int path[], int* idx, struct Graph* gr){
    done[s] = true;
    path[*idx] = s;
    (*idx)++;
    if(s == d){
        for(int i=0; i<(*idx);i++){
            cout<<path[i]<<" ";
        }
        cout<<" Cost:- "<<(*cost)<<endl;
    }
    else{
        struct node* temp = gr->arr[s];
        while(temp){
            if(!done[temp->vertex]){
                *cost += temp->weight;
                recurPaths(temp->vertex, d, cost, done, path, idx, gr);
            }
            temp = temp->next;
        }
    }
    (*idx)--;
    (*cost) = 0;
    done[s] = false;
}

void printPaths(int s, int d, struct Graph* gr){
    bool* done = new bool[gr->n];
    int* path = new int[gr->n];
    int path_ind = 0, cost = 0;
    for(int i=0; i<gr->n; i++){
        done[i] = false;
    }
    cout<<"Possible paths are:"<<endl;
    recurPaths(s, d, &cost, done, path, &path_ind, gr);
}

int main(){
    struct Graph* g1 = createGraph(7);
    addEdge(g1, 0, 5, 5);
    addEdge(g1, 0, 1, 25);
    addEdge(g1, 5, 4, 20);
    addEdge(g1, 4, 6, 18);
    addEdge(g1, 6, 1, 10);
    addEdge(g1, 4, 3, 16);
    addEdge(g1, 6, 3, 14);
    addEdge(g1, 3, 2, 8);
    addEdge(g1, 2, 1, 12);
    printGraph(g1);
    printPaths(1, 4, g1);
    return 0;
}

