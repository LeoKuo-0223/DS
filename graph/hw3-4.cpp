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

struct comparator;
class Edge;

bool existInAnySet(long v,long size,long *index);
const vector<string> split(const string &str, const char &delimiter);
template <typename T>
std::set<T> Union(const std::set<T>& a, const std::set<T>& b);
bool createCycle(Edge edge);
void insert_set(Edge edge);

vector<long> Cost_Collector;    //use to save the cost
vector<set<long>> vertices_set;     //vector contain sets

class Edge{     //define the Edge class which contain two vertex and cost
    long vertex_1;
    long vertex_2;
    long cost;
    public:
        Edge(long _vertex1,long _vertex2,long _cost){   //constructor
            vertex_1 = _vertex1;
            vertex_2 = _vertex2; 
            cost = _cost;
        }
        long getvertex_1() const{ return vertex_1;} //define function to get the members of the class
        long getvertex_2() const{ return vertex_2;}
        long getcost() const{ return cost;}
};


struct comparator{  //using to build the min heap
    bool operator()(const Edge e1, const Edge e2)
    {
        return e1.getcost() > e2.getcost(); //compare two cost
    }
};

bool createCycle(Edge edge){    //check the edge will create the cycle or not
    long v1=edge.getvertex_1();
    long v2=edge.getvertex_2();
    long size = vertices_set.size();    
    for(long i=0;i<size;i++){
        if(vertices_set[i].count(v1)==1 && vertices_set[i].count(v2)==1){   //search element in sets
            return true;    //if found v1 and v2 in the same set, it means that cycle will be created
        }
    }
    return false;   //no cycle
}

template <typename T>
std::set<T> Union(const std::set<T>& a, const std::set<T>& b){  //union two set because the edge will connect these two components
  std::set<T> result = a;
  result.insert(b.begin(), b.end());
  return result;
}

void insert_set(Edge edge){     //Let the edge be saved into the vertices_set
    long v1=edge.getvertex_1();
    long v2=edge.getvertex_2();
    long size = vertices_set.size();
    long v1set_Index,v2set_Index;
    long *ptr_v1set_Index=&v1set_Index;     //pointer point to the v1set_Index and v2set_Index
    long *ptr_v2set_Index=&v2set_Index;

    bool v1_inAnySet=existInAnySet(v1,size,ptr_v1set_Index);
    bool v2_inAnySet=existInAnySet(v2,size,ptr_v2set_Index);

    if(v1_inAnySet&&v2_inAnySet){   //if two vertex v1,v2 are already exist in two different set in vertices_set
        set<long> union_set = Union(vertices_set[v1set_Index],vertices_set[v2set_Index]);   //new set for concatenating two set
        vector<set<long>>::iterator itr;
        itr=vertices_set.begin();
        vertices_set.erase(itr+v1set_Index);    //delete the set that contain v1 from vertices_set
        vertices_set.erase(itr+v2set_Index);    //delete the set that contain v1 from vertices_set
        vertices_set.push_back(union_set);  //add new set into vertices_set
    }else if(v1_inAnySet || v2_inAnySet){   //if one of the vertices exist in the vertices_set
        if(v1_inAnySet&&!v2_inAnySet){  //v1 exist
            vertices_set[v1set_Index].insert(v2);   //insert v2
        }else if(v2_inAnySet&&!v1_inAnySet){    //v2 exist
            vertices_set[v2set_Index].insert(v1);   //insert v1
        }
    }else{  //both two vertices are not exist in vertices_set
        set<long> newset;   //create new set 
        newset.insert(v1);  //add two vertices into set 
        newset.insert(v2);
        vertices_set.push_back(newset); //push this new set into vector
    }
}

bool existInAnySet(long v,long size,long *index){   //check if there is any set in vector "vertices_set" contain vertex v as its element
    for(long i=0;i<size;i++){
        if(vertices_set[i].count(v)==1){    //if found v exist in set i
            *index=i;   //save the index of the set 
            return true;
        }
    }
    return false;   //do not exist in all current sets
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
    priority_queue<Edge, vector<Edge>, comparator> *minHeap;    //declare min Heap pointer
    long num_vertices;
    long num_edge;
    char filetext[100];
    string filename;
    string outputfileName;
    ifstream fin;
    ofstream outputfin;
    cout<<"Please input the map file: ";
    cin>>filename;
    outputfileName = filename;
    outputfileName.replace(outputfileName.find("input"), 5, "output");  //create output file name
    outputfin.open(outputfileName);     //create new file for output in the directory
    fin.open(filename);     //open input file
    if(fin.is_open()){
        fin.getline(filetext,sizeof(filetext)); 
        vector<string> parameter;
        string str_(filetext);  //convert char array to string type
        parameter = split(str_,' ');
        num_vertices = stoi(parameter[0]);  //convert string to integer
        num_edge = stoi(parameter[1]);
        minHeap = new priority_queue<Edge, vector<Edge>, comparator>;   //point to a new min Heap
        for(long i=0;i<num_edge;i++){
            fin.getline(filetext,sizeof(filetext));
            vector<string> edge_info;
            string str_(filetext);  //convert char array to string type
            edge_info = split(str_,' ');
            long vertex_u = stoi(edge_info[0]);  //convert string to integer
            long vertex_v = stoi(edge_info[1]);
            long vertex_c = stoi(edge_info[2]);
            // cout<<"(u,v,c) = ("<<vertex_u<<","<<vertex_v<<","<<vertex_c<<")"<<endl;
            minHeap->push(Edge(vertex_u,vertex_v,vertex_c));    //push a set of edge which contain two vertex and its cost
        }
        // implement the Kruskal's Algorithm
        while(Cost_Collector.size()<num_vertices-1 && minHeap->empty()==false){
            Edge lowestCost_edge = minHeap->top();  //determin the lowest cost edge from heap
            // cout<<"(Lu,Lv,Lc) = ("<<lowestCost_edge.getvertex_1()<<","<<lowestCost_edge.getvertex_2()<<","<<lowestCost_edge.getcost()<<")"<<endl;
            minHeap->pop(); //pop out this (u,v) and rearrange the heap
            
            if(createCycle(lowestCost_edge)==false){    //if (u,v) does not create a cycle
                Cost_Collector.push_back(lowestCost_edge.getcost());    //saving the cost of the edge in to vector
                insert_set(lowestCost_edge);    //form a set for new edge of insert it into existed set
            }else{
                continue;   //discard this (u,v)
            }
        }

        long total_cost=0;
        for(long j=0;j<Cost_Collector.size();j++){  //calculate the total cost by adding all the element in vector "Cost_Collevtor"
            total_cost+=Cost_Collector[j];
        }
        outputfin<<total_cost;

    }else{
        cout<<"fail to open file"<<endl;	
        exit(1); //shut down program
    }
    fin.close();
    outputfin.close();
    return 0;
}