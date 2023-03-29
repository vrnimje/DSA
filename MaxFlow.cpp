#include <iostream>
#include <climits>
using namespace std;


struct qnode{
    int data;
    struct qnode *next;
};

class Queue{
    public:
    struct qnode *start = nullptr;

    void enqueue(int x){
        struct qnode *p = new struct qnode;
        p->data = x;
        p->next = NULL;
        if (start!=NULL){
            struct qnode *temp = new struct qnode;
            temp = start;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = p;
        }
        else{
            start = p;
        }
    }
    
    int dequeue(){
        if (start == NULL){
            cout<<"QUEUE UNDERFLOW"<<endl;
            return -1;
        }
        else{
            int x = start->data;
            start = start->next;
            return x;
        }
    }

    void display_q(){
        if (start==NULL){
            cout<<"Queue is empty"<<endl;
        }

        else{
            struct qnode *p = new struct qnode;
            p = start;
            cout<<"Queue: ";
            while(p!= NULL){
                cout<<p->data<<" ";
                p = p->next;
            }
            cout<<endl;
        }
    }

    int front(){
        if (start != NULL){
            return start->data;
        }
        else{
            return -1;
        }
    }

    int back(){
        if (start == NULL){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        else{
            struct qnode *temp = new struct qnode;
            temp = start;
            while(temp->next != NULL){
                temp = temp->next;
            }
            return temp->data;
        }
    }

    bool isEmpty(){
        if (start == NULL){
            return true;
        }
        return false;
    }
};

struct node{
    int vertex, weight;
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
}

void printGraph(struct Graph* gr){
    for(int i = 0; i < gr->n; i++){
        struct node* temp = gr->arr[i];
        cout<<"Vertex:"<<i<<":-";
        while(temp!=NULL){
            cout<<"|"<<temp->vertex<<", "<<temp->weight<<"|->";
            temp = temp->next;
        }
        cout<<endl;
    }
}

bool search_al(struct node* head, int v, int* w){
    struct node* temp = head;
    while(temp){
        if (temp->vertex == v){
            *w = temp->weight;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

struct node* weight_acc(struct node* head, int v){
    struct node* temp = head;
    while(temp){
        if (temp->vertex == v){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}


bool BFS(struct Graph* gr, int s, int t, int parent[]){
    bool visited[gr->n];
    for(int i=0; i<gr->n; i++){
        visited[i] = false;
    }
    Queue q;
    q.enqueue(s);
    visited[s] = true;
    parent[s] = -1;
    while(!(q.isEmpty())){
        int u = q.dequeue();
        //cout<<"u: "<<u<<endl;
        struct node* temp = gr->arr[u];
        while(temp){
            //q.display_q();
            if (visited[temp->vertex] == false){
                if (temp->vertex == t){
                    parent[temp->vertex] = u;
                    return true;
                }
                q.enqueue(temp->vertex);
                parent[temp->vertex] = u;
                visited[temp->vertex] = true;
            }
            temp = temp->next;
        }
    }
    return false;
}

int fordFulkerson(struct Graph* gr, int s, int t){
    int u, v;
    struct Graph* residual = createGraph(gr->n);
    for (int i=0; i<gr->n; i++){
        struct node* temp = new struct node;
        temp = gr->arr[i];
        while(temp){
            addEdge(residual, i, temp->vertex, temp->weight);
            temp = temp->next;
        }
    }
    cout<<endl;
    printGraph(residual);
    int parent[gr->n] = {0};
    int max_flow = 0;
    while (BFS(residual, s, t, parent)){
        int path_flow = INT_MAX;
        for (v = t; v!=s; v = parent[v]){
            //cout<<2<<endl;
            u = parent[v];
            struct node* x = weight_acc(residual->arr[u], v);;
            path_flow = min(path_flow, x->weight);
        }
        for (v = t; v != s; v = parent[v]){
            u = parent[v];
            struct node* temp = weight_acc(residual->arr[u], v);
            temp->weight -= path_flow;
            temp = weight_acc(residual->arr[v], u);
            if (temp != NULL){
                temp->weight += path_flow;
            }
        }
        printGraph(residual);
        max_flow += path_flow;
        cout<<max_flow<<endl;
    }

    return max_flow;
}

int main(){
    struct Graph* g = createGraph(6);
    addEdge(g, 0, 1, 16);
    addEdge(g, 0, 2, 13);
    addEdge(g, 1, 2, 10);
    addEdge(g, 2, 1, 4);
    addEdge(g, 1, 3, 12);
    addEdge(g, 2, 4, 14);
    addEdge(g, 3, 2, 9);
    addEdge(g, 4, 3, 7);
    addEdge(g, 3, 5, 20);
    addEdge(g, 4, 5, 4);
    printGraph(g);
    cout<<fordFulkerson(g, 0, 5)<<" ok"<<endl;

}

