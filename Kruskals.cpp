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

struct Edge{
    int v1, v2, weight;
    struct Edge *next;
};

struct Edge* insert_at_end(struct Edge* start, int x1, int x2, int w){
    struct Edge *p = new struct Edge;
    p->v1 = x1;
    p->v2 = x2;
    p->weight = w;
    p->next = NULL;
    if (start!=NULL){
        struct Edge *temp = new struct Edge;
        temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
    else{
        start = p;
    }
    return start;
}

void sort_ll(struct Edge* start){
    if (start == NULL){
        cout<<"Array is empty"<<endl;
    }
    else{
        struct Edge *current = start, *index;
        int temp;
        while(current != NULL){
            index = current->next;
            while(index != NULL){
                if (current->weight > index->weight){
                    temp = current->weight;
                    current->weight = index->weight;
                    index->weight = temp;
                    temp = current->v1;
                    current->v1 = index->v1;
                    index->v1 = temp;

                    temp = current->v2;
                    current->v2 = index->v2;
                    index->v2 = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void display_ll(struct Edge* start){
    if (start==NULL){
        cout<<"Array is empty"<<endl;
    }

    else{
        struct Edge *p = new struct Edge;
        p = start;
        while(p!= NULL){
            cout<<"|"<<p->v1<<","<<p->v2<<","<<p->weight<<"|->";
            p = p->next;
        }
        cout<<endl;
    }
}

struct Graph{
    int n=0;
    struct Edge *start;
    struct node* arr[];
};

struct Graph* createGraph(int x){
    struct Graph* gr = new struct Graph;
    gr->n = x;
    for(int i=0; i<gr->n; i++){
        gr->arr[i] = new struct node;
        gr->arr[i] = nullptr; 
    }
    gr->start = new struct Edge;
    gr->start = NULL;
    return gr;
}

void addEdge(struct Graph* gr, int s, int d, int w){
    struct node* temp = createNode(d, w);
    temp->next = gr->arr[s];
    gr->arr[s] = temp;
    temp = createNode(s, w);
    temp->next = gr->arr[d];
    gr->arr[d] = temp;
    gr->start = insert_at_end(gr->start, s, d, w);
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

class Forest{
    int* parent;
    int* rank;

    public:
        Forest(int n){
            parent = new int[n];
            rank = new int[n];
        
            for (int i = 0; i < n; i++) {
                parent[i] = -1;
                rank[i] = 1;
            }
        }

        int find(int i){
            if (parent[i] == -1){
                return i;
            }
            return parent[i] = find(parent[i]);
        }

        void unite(int x, int y){
            int s1 = find(x);
            int s2 = find(y);
            if (s1 != s2){
                if (rank[s1] < rank[s2]){
                    parent[s1] = s2;
                    rank[s2] += rank[s1];
                }
                else{
                    parent[s2] = s1;
                    rank[s1] += rank[s2];
                }
            }
        }
};

void KruskalsMST(struct Graph* gr){
    struct Graph* res = createGraph(gr->n);
    sort_ll(gr->start);
    Forest f(gr->n);
    struct Edge* p = new struct Edge;
    p = gr->start;
    int cost = 0;
    while(p){
        int x = p->v1;
        int y = p->v2;
        int w = p->weight;

        if (f.find(x) != f.find(y)){
            f.unite(x, y);
            addEdge(res, x, y, w);
            cost += w;
        }
        p = p->next;
    }
    printGraph(res);
    cout<<"Total cost of all edges is: "<<cost<<endl;
}

int main(){
    struct Graph* g1 = createGraph(4);
    /*addEdge(g1, 0, 2, 3);
    addEdge(g1, 2, 1, 10);
    addEdge(g1, 2, 4, 6);
    addEdge(g1, 2, 3, 2);
    addEdge(g1, 1, 3, 4);
    addEdge(g1, 3, 4, 1);*/
    addEdge(g1, 0, 1, 12);
    addEdge(g1, 0, 2, 5);
    addEdge(g1, 0, 3, 29);
    addEdge(g1, 1, 2, 19);
    addEdge(g1, 2, 3, 80);
    addEdge(g1, 1, 3, 7);
    printGraph(g1);
    cout<<"Minimum Spanning tree obtained by Kruskal's algorithm is:-"<<endl;
    KruskalsMST(g1);
    return 0;
}