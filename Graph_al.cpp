#include <iostream>
using namespace std;

struct node{
    int vertex;
    struct node* next;
};


struct node* createNode(int x){
    struct node* root = new struct node;
    root->vertex = x;
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

void addEdge(struct Graph* gr, int s, int d){
    struct node* temp = createNode(d);
    temp->next = gr->arr[s];
    gr->arr[s] = temp;
    temp = createNode(s);
    temp->next = gr->arr[d];
    gr->arr[d] = temp;
}

void printGraph(struct Graph* gr){
    for(int i = 0; i < gr->n; i++){
        struct node* temp = gr->arr[i];
        cout<<"Vertex:"<<i<<":-";
        while(temp!=NULL){
            cout<<"|"<<temp->vertex<<"|->";
            temp = temp->next;
        }
        cout<<endl;
    }
}

struct Graph* complement(struct Graph* gr){
    int num = 0;
    if(gr->n%2 == 0){
        num = gr->n/2;
    }
    else{
        num = (gr->n/2)+1;
    }
    struct Graph* res = createGraph(gr->n);
    for(int i=0; i<num+1; i++){
        struct node* temp = gr->arr[i];
        int tarr[gr->n-1];
        int b=0;
        for(int k = 0; k < (gr->n); k++){
            if (k == i){
                continue;
            }
            tarr[b] = k;
            b++;
        }
        int a = 0;
        while(temp){
            for(int l = 0; l<(gr->n-1); l++){
                if (tarr[l] == temp->vertex){
                    tarr[l] = -1;
                }
            }
            temp = temp->next;
        }
        for(int k = 0; k<(gr->n-1); k++){
            if(tarr[k]>=0){
                addEdge(res, i, tarr[k]);
            }
        }
    }
    return res;
}

int main(){
    struct Graph* graph = createGraph(4);
    addEdge(graph, 1, 0);
    addEdge(graph, 2, 0);
    addEdge(graph, 3, 0);
    addEdge(graph, 2, 1);
    printGraph(graph);
    struct Graph* res = complement(graph);
    cout<<"Complement of above graph is:"<<endl;
    printGraph(res);
    return 0;
}








