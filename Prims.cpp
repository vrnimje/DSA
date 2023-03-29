#include <iostream>
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

bool isinArr(int arr[], int e, int len){
    for(int i=0; i<len; i++){
        if (arr[i] == e){
            return true;
        }
    }
    return false;
}

int minWeightPath(int prim[],struct node* head, int* y, int c){
    while(head->next && isinArr(prim, head->vertex, c)){
        head = head->next;
    }
    int minw = head->weight, vertex = head->vertex;
    struct node* temp = new struct node;
    temp = head;
    while(temp){
        if ((temp->weight < minw) && !(isinArr(prim, temp->vertex, c))){
            minw = temp->weight;
            vertex = temp->vertex;
        }
        temp = temp->next;
    }
    *y = vertex;
    return minw;
}

void PrimsMST(struct Graph* gr){
    int num = gr->n;
    int prim[num];
    prim[0] = 0;
    struct Graph* res = createGraph(num);
    int c = 1, cost = 0;
    while(c < num){
        int x=0;
        int* y = new int;
        int s = 0, min_ver = 20, min_weight = 20;
        for(int i=0; i<c; i++){
            x=0;
            *y = 0;
            x = minWeightPath(prim, gr->arr[prim[i]], y, c);
            if (!(isinArr(prim, *y, c)) && (min_weight >= x)){
                min_weight = x;
                min_ver = *y;
                s = prim[i];
            }
        }
        addEdge(res, s, min_ver, min_weight);
        cost += min_weight;
        prim[c] = min_ver;
        c++;
    }
    printGraph(res);
    cout<<"Total cost of all edges is: "<<cost<<endl;
}

int main(){
    struct Graph* g1 = createGraph(5);
    addEdge(g1, 0, 2, 3);
    addEdge(g1, 2, 1, 10);
    addEdge(g1, 2, 4, 6);
    addEdge(g1, 2, 3, 2);
    addEdge(g1, 1, 3, 4);
    addEdge(g1, 3, 4, 1);
    printGraph(g1);
    cout<<"Minimum Spanning tree obtained by Prim's algorithm is:-"<<endl;
    PrimsMST(g1);
    return 0;
}