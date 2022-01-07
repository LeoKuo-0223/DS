#include <stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
#include <sstream>
#include<stdbool.h>
using namespace std; 
vector<int> output;     //saving the path

class Graph{    //delare the Graph class
    public:
        Graph(int vertex_Index,int num_vertices){   //initial the number of vertices and index of the first vertex
            Index = vertex_Index;
            num = num_vertices;
        };
        vector<vector<int>> graph_matrix;   //adjacent matrix for graph
        void DFS(const int index);  //overloading for DFS() for recursive
        void DFS();     //depth first search function
    private:
        bool *visited;  //record visited or not
        int num;
        int Index;

};

void Graph::DFS(const int index){
    visited[index] = true;  //already pass through
    output.push_back(index);    //record this vertex
    for(int i=0;i<num;i++){ //always enter the vertex with the smallest index
        if(graph_matrix[index][i]==1&&visited[i]==false){   //if edge exist and the vertex hasn't been visited
            DFS(i); //enter the vertex
        }
    }
}

void Graph::DFS(){  
    visited = new bool[num];    //create memory space for visited array
    fill(visited,visited+num,false);    //initial the value of visited array
    DFS(Index); 
    delete []visited;   //release memory
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
    int num_set;
    int num_vertices;
    int vertex_index;
    char filetext[4096];
    Graph *graph;       //declare the pointer with Graoh type
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
        num_set= atoi(filetext);    //get the number of set
        for(int s=0;s<num_set;s++){ 
            vector<string> parameter;   //declare for saving the vertex_index and num_vertices in string type
            fin.getline(filetext,sizeof(filetext)); 
            string str_(filetext);  //convert char array to string type
            parameter = split(str_,' ');
            num_vertices = stoi(parameter[0]);  //convert string to integer
            vertex_index = stoi(parameter[1]);
            // cout<<"(num,index)="<<num_vertices<<" "<<vertex_index<<endl;
            graph = new Graph(vertex_index,num_vertices);   //let the pointer point to new Graph object
            graph->graph_matrix.resize(num_vertices);   //assign the 2d vector which contains "num_vertices" 1d vector
            for(int i=0;i<num_vertices;i++){    
                vector<string> matrix_value;    
                fin.getline(filetext,sizeof(filetext));
                string Matrix_(filetext);
                matrix_value = split(Matrix_,' ');  //split the string to extract each number in adjacent matrix
                for(int j=0;j<num_vertices;j++){
                    graph->graph_matrix[i].push_back(stoi(matrix_value[j]));    //save the value into graph 
                    // cout<<graph->graph_matrix[i][j];
                }
            }
            graph->DFS();   //DFS function start
            if(outputfin.is_open()){
                for(int j=0;j<output.size();j++){
                    outputfin<<output[j]<<" ";
                    // cout<<output[j];
                }
                outputfin<<'\n';
                // cout<<endl;
            }
            output.clear();
        }
    }else{
        cout<<"fail to open file"<<endl;	
        exit(1); //shut down program
    }
    fin.close();
    outputfin.close();
    return 0;
}