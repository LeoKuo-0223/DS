#include <stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
#include <sstream>
#include<stdbool.h>
#include <queue>
#include <set>
using namespace std;

typedef struct adjNode{ //define adjacent list's node type
 long val, cost;
 adjNode* next;
}adjNode;

typedef struct graphEdge{   //define adjacent list's edge type
 long start_ver, end_ver, weight;
}graphEdge;

class Graph{
    long N;  // number of nodes in the graph
    // insert new nodes into adjacency list from given graph
    adjNode* getAdjListNode(long value, long weight, adjNode* head){
        adjNode* newNode = new adjNode;
        newNode->val = value;
        newNode->cost = weight;
        newNode->next = head;   // point new node to current head
        return newNode;
    }
    private:
        long root;  
        bool *visited;  //vertex visited record
    public:
        long *costRecord;   //point to the cost record array
        adjNode **head;            //adjacency list as array of pointers
        Graph(vector<graphEdge> edges, long n, long N,long _root){         // Constructor
            root=_root;
            head = new adjNode*[N]();   // allocate new node
            this->N = N;
            // initialize head pointer for all vertices
            for (long i = 0; i < N; ++i){
                head[i] = nullptr;
            }
            // construct undirected graph by adding edges to it
            for (long i = 0; i < n; i++)  {
                long start_ver = edges[i].start_ver;
                long end_ver = edges[i].end_ver;
                long weight = edges[i].weight;
                // insert in the beginning
                adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver-1]);  
                adjNode* newNode_reverse = getAdjListNode(start_ver, weight, head[end_ver-1]);  //using to build two ways edge
                // point head pointer to new node
                head[start_ver-1] = newNode;    //Ex: vertex with value 1 saves in head[0]
                head[end_ver-1] = newNode_reverse;
            }
        }
        
        // Destructor
        ~Graph() {
            for (long i = 0; i < N; i++)
            delete[] head[i];
            delete[] head;
        }
        void DFS(const long index);  //overloading for DFS() for recursive
        void DFS();     //depth first search function
       

};
void Graph::DFS(const long _root){
    long index=_root-1; //get the index value 
    visited[index]=true;
    adjNode *ptr=head[index];
    // cout<<"visited vert: "<<_root<<endl;
    for(ptr;ptr!=nullptr;ptr=ptr->next){ //get in to next vertex which is adjacent to _root vertex
        if(head[(ptr->val)-1]!=nullptr&&visited[ptr->val-1]==false){   //if edge exist, and the vertex hasn't been visited
            costRecord[(ptr->val-1)]=costRecord[index]+ptr->cost;   //compute the cost 
            DFS(ptr->val); //visit next vertex
        }
    }
}
void Graph::DFS(){  
    visited = new bool[N];
    costRecord = new long[N];    //create memory space for costRecord,visited array
    fill(costRecord,costRecord+N,0);    //initial the value 
    fill(visited,visited+N,false);
    DFS(root);  //start to DFS from root
}

const vector<string> split(const string &str, const char &delimiter) {  //split the string by designated char value
    vector<string> result;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter)) {
        result.push_back(tok);
    }
    return result;
}

int main(){
    vector<graphEdge> edges;    //saving edges
    Graph *graph; 
    long root;
    long num_vertices;
    char filetext[100];
    string filename;
    string outputfileName;
    ifstream fin;
    ofstream outputfin;
    cout<<"Please input the file: ";
    cin>>filename;
    outputfileName = filename;
    outputfileName.replace(outputfileName.find("input"), 5, "output");  //create output file name
    outputfin.open(outputfileName);     //create new file for output in the directory
    fin.open(filename);     //open input file
    if(fin.is_open()){
        fin.getline(filetext,sizeof(filetext));
        num_vertices = atoi(filetext);  //convert string to integer
        // cout<<"num_vertices: "<<num_vertices<<endl;
        for(long i=0;i<num_vertices-1;i++){
            fin.getline(filetext,sizeof(filetext));
            vector<string> edge_info;
            string str_(filetext);  //convert char array to string type
            edge_info = split(str_,' ');
            long vertex_u = stoi(edge_info[0]);  //convert string to integer
            long vertex_v = stoi(edge_info[1]);
            long vertex_c = stoi(edge_info[2]);
            edges.push_back({vertex_u,vertex_v,vertex_c});
            // cout<<"(u,v,c)="<<"("<<vertex_u<<","<<vertex_v<<","<<vertex_c<<")"<<endl;
        }

        fin.getline(filetext,sizeof(filetext));
        root = atoi(filetext);  //convert string to integer
        // cout<<"root: "<<root<<endl;
        graph =new Graph(edges, edges.size(), num_vertices,root);   //create graph for edges saving aboved
        graph->DFS();

        for(long i=0;i<num_vertices;i++){
            outputfin<<i+1<<" "<<graph->costRecord[i]<<endl;
        }
    }else{
        cout<<"fail to open file"<<endl;	
        exit(1); //shut down program
    }
    fin.close();
    outputfin.close();
    return 0;
}