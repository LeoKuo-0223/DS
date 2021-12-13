#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
#define NUM 100
using namespace std;
int mode;

class Node;
class BST;

template<class T>
class Stack{    //declare the Stack Class
   public:
         Stack();
         bool isEmpty() const;
         void push(T);
         void pop();
         T Top() const;
     private:
         int top;
         T *array = new T[NUM];
 };

template<class T>
Stack<T>::Stack(){ //constructor of Stack class
     top=-1;         //empty stack with top value -1
}

template<class T>
bool Stack<T>::isEmpty() const{        //read only function for checking the stack is empty or not
     return top== -1;
}

template<class T>
void Stack<T>::push(T item){          //push integer into the stack
     if(top==top-1) cout<<"stack is full";
     else array[++top]=item;
}

template<class T>
void Stack<T>::pop(){      //pop out the top object from stack
     if(isEmpty()); //cout<<"stack is empty";
     else array[top--];
 }

template<class T>
T Stack<T>::Top() const{     //read the top object in the stack
     if(isEmpty()) {//cout<<"stack is empty";
      return -1;
     }else {
         return array[top];
     }
 }

template<class T>
class Queue{        //declare class queue
    private:
        T *queue[NUM];
        int capacity;
        int front;
        int rear;
    public:
        Queue(){
            front = rear=0;
        }
        bool IsEmpty();
        T* Front();
        T* Rear();
        void Push(T *x);
        void Pop();
};

template<class T>
bool Queue<T>::IsEmpty(){       //check the queue is empty or not
    return front==rear;
}

template<class T>
T* Queue<T>::Front(){       //return the front element
    if(IsEmpty()){
        throw "queue is empty";
    }
    return queue[(front+1)%capacity];
}

template<class T>
T* Queue<T>::Rear(){        //return the rear element
    if(IsEmpty()){
        throw "queue is empty";
    }
    return queue[rear];
}

template<class T>
void Queue<T>::Push(T *x){      //add new element to queue
    if((rear+1)%capacity==front){
        throw "queue is full";
    }
    rear = (rear+1)%capacity;
    queue[rear] = x;
}

template<class T>
void Queue<T>::Pop(){       //delete element from queue
    if(IsEmpty()){
        throw "queue is empty";
    }
    front = (front+1)%capacity;
}


class Node{             //declare class Node
    friend BST;
    public:
        Node(){
            leftchild = NULL;
            rightchild = NULL;
            parent = NULL;
            key = -1;
        }
    private:
        Node *leftchild;
        Node *rightchild;
        Node *parent;
        int key;
};

class BST{          //declare Binary Search Tree
    friend Node;
    // private:
    //     Node *root;
    public:
        Node *root;
        BST(Node *node){
            if(node==NULL){
                root = new Node();
            }else{
                root = node;
            }
     
        }
        void DeleteAllNode(Node*node);
        void Insert(int key);
        void Delete(int key);
        void Search(int key);
        void inorderT(Node *node);
        void preorderT(Node *node);
        void postorderT(Node *node);
        void levelorder();
        void visit(Node *node){ cout<<" "<<node->key;}
        void printTraversal(){
            cout<<"The tree in prefox order : ";
            preorderT(root);
            cout<<endl<<"The tree in infix order : ";
            inorderT(root);
            cout<<endl<<"The tree in postfix order : ";
            postorderT(root);
            cout<<endl<<"The tree in level order : ";
            levelorder();
            cout<<endl;
        }
        void path(BST bst,int *map,int count,int swordloc,int meatloc);
};

void BST::Insert(int key){      
    Node *current_node = root;
    if(current_node->key==-1){// if root has no key, default key for new node is -1
        root->key = key;
        if(mode!=2) cout<<"Number "<<key<<" is inserted"<<endl;
        return;
    }
    for(;;){
        if(key==current_node->key){ //find the node
            cout<<"Error. Number "<<key<<" exists."<<endl;
            break;
        }else if(key<current_node->key){    //enter into leftchild
            if(current_node->leftchild!=NULL){
                current_node = current_node->leftchild;
            }else{
                current_node->leftchild = new Node();
                current_node->leftchild->parent = current_node;
                current_node->leftchild->key = key;
                if(mode!=2) cout<<"Number "<<key<<" is inserted"<<endl;
                break;
            }
        }else if(key>current_node->key){    //enter into rightchild
            if(current_node->rightchild!=NULL){
                current_node = current_node->rightchild;
            }else{
                current_node->rightchild = new Node();
                current_node->rightchild->parent = current_node;
                current_node->rightchild->key = key;
                if(mode!=2) cout<<"Number "<<key<<" is inserted"<<endl;
                break;
            }
        }
    }
}

void BST::Search(int key){  //same concept with insert, compare nodes with its key
    Node *current_node = root;
    for(;;){
        if(key==-1) return;
        if(key==current_node->key){
            cout<<"Bingo! "<<key<<" is found"<<endl;
            break;
        }else if(key<current_node->key){
            if(current_node->leftchild!=NULL){
                current_node = current_node->leftchild;
            }else{
                cout<<"SORRY. "<<key<<" is not found"<<endl;
                break;
            }
        }else if(key>current_node->key){
            if(current_node->rightchild!=NULL){
                current_node = current_node->rightchild;
            }else{
                cout<<"SORRY. "<<key<<" is not found"<<endl;
                break;
            }
        }
    }
}


void BST::Delete(int key){  //delete specific node with designated key
    Node *current_node = root;
    for(;;){ //find node for designated key
        if(key==-1) return;
        if(key==current_node->key){
            cout<<"Number "<<key<<" is deleted."<<endl;
            break;
        }else if(key<current_node->key){
            if(current_node->leftchild!=NULL){
                current_node = current_node->leftchild;
            }else{
                cout<<"SORRY. "<<key<<" is not exist"<<endl;
                return;
            }
        }else if(key>current_node->key){
            if(current_node->rightchild!=NULL){
                current_node = current_node->rightchild;
            }else{
                cout<<"SORRY. "<<key<<" is not exist"<<endl;
                return;
            }
        }
    }

    Node *y = 0;      // pointer, point to the node which will be deleted 
    Node *x = 0;      // pointer, point to the child of the deleted node
    //case 1 no child
    if (current_node->leftchild == NULL || current_node->rightchild == NULL){
        y = current_node;
    }
    else{   //find successor of the node, the min key in right subtree
        Node *min_inRight =current_node->rightchild;
        while(min_inRight->leftchild!=NULL){
            min_inRight = min_inRight->leftchild;
        }
        y = min_inRight;        // let y point to the successor of deleted node
    }                                      
    if (y->leftchild != NULL){      //Let x point to the child of node, it might be NULL
        x = y->leftchild;                  
    } else{
        x = y->rightchild;
    }

    if (x != NULL){                 //if y has child, let its child link to y's parent
        x->parent = y->parent;             
    }
    // link deleted node's child to BST in different case

    if (y->parent == NULL){                // if deleted node is root of BST, let x become the root of BST
        this->root = x;
    } else if (y == y->parent->leftchild){    // if y is its parent's leftchild
        y->parent->leftchild = x;           // let x become y's parent's new leftchild
    }else{                                   
        y->parent->rightchild = x;          // vice versa, x become new rightchild
    }                                       
    //if y is different with the designated node, 
    //it means that y's data should transfer to the node which data should be remove
    if (y != current_node) {                 
        current_node->key = y->key;         //remove the key(in other word, delete the node)                                   
    }

    delete y;                               //release the memory
    y = 0;

}

void BST::preorderT(Node *node){    //rLV
    if(node!=NULL){
        visit(node);
        preorderT(node->leftchild);
        preorderT(node->rightchild);
    }
}

void BST::inorderT(Node *node){     //LrV
    if(node!=NULL){
        inorderT(node->leftchild);
        visit(node);
        inorderT(node->rightchild);
    }
}

void BST::postorderT(Node *node){   //LVr
    if(node!=NULL){
        postorderT(node->leftchild);
        postorderT(node->rightchild);
        visit(node);
    }
}

void BST::levelorder(){     //using Queue to implement the level order
    Queue<Node> q;
    Node *currentnode = root;
    while(currentnode!=NULL){
        visit(currentnode);
        if(currentnode->leftchild!=NULL) q.Push(currentnode->leftchild);
        if(currentnode->rightchild!=NULL) q.Push(currentnode->rightchild);
        if(q.IsEmpty()) return;
        currentnode = q.Front();
        q.Pop();
    }
}

void BST::DeleteAllNode(Node* node){    //after the function of finding meaty, release the memory of BST
    if(node->leftchild!=NULL) DeleteAllNode(node->leftchild);
    if(node->rightchild!=NULL) DeleteAllNode(node->rightchild);
    delete node;
}

void BST::path(BST bst,int *map,int count,int swordloc,int meatloc){    //bring the parameter to find the path
    int ansPath[50]={-1};               //use to save the fastest path
    Node *current_node_sword = bst.root;    
    Node *current_node_meat= bst.root;
    Stack<int> nodeStack_sword;     //use to record the path of finding sword, and go back with Top(),pop() function
    
    bool findcommonNode = false;
    int commonNode_key;
    int pathToMeat[100];
    int steps_meat=0;
    int steps_ans=0;
    for(;;){    //path to sword
        nodeStack_sword.push(current_node_sword->key);  
        ansPath[steps_ans] = current_node_sword->key;   //record each step before finding out the sword
        // cout<<"ansPath"<<ansPath[steps_ans]<<endl;
        if(swordloc==current_node_sword->key){      //same concept with search function in BST class
            //cout<<"find sword in "<<current_node_sword->key<<endl;
            break;
        }else if(swordloc<current_node_sword->key){
            if(current_node_sword->leftchild!=NULL){
                current_node_sword = current_node_sword->leftchild;
            }

        }else if(swordloc>current_node_sword->key){
            if(current_node_sword->rightchild!=NULL){
                current_node_sword = current_node_sword->rightchild;
            }
        }
        steps_ans++;
        
    }
    for(;;){ //path to meaty (from root)
        pathToMeat[steps_meat] = current_node_meat->key;    //record each step before finding out the meaty
        if(meatloc==current_node_meat->key){
            //cout<<"find meat in "<<current_node_meat->key<<endl;
            steps_meat++;
            break;
        }else if(meatloc<current_node_meat->key){
            if(current_node_meat->leftchild!=NULL){
                current_node_meat = current_node_meat->leftchild;
            }

        }else if(meatloc>current_node_meat->key){
            if(current_node_meat->rightchild!=NULL){
                current_node_meat = current_node_meat->rightchild;
            }
        }
        steps_meat++;
    }
    
    // if the path of finding sword and meaty have the common node, the path through that node is the fastest route
    while(!nodeStack_sword.isEmpty()&&!findcommonNode){
        ansPath[steps_ans] = nodeStack_sword.Top(); //go back to find the fastest route by Stack
        for(int j=steps_meat;j>=0;j--){
            if(nodeStack_sword.Top()==pathToMeat[j]){
                commonNode_key = nodeStack_sword.Top();
                //cout<<"common key: "<<commonNode_key<<endl;
                findcommonNode=true;
                
            }
        }
        steps_ans++;
        nodeStack_sword.pop();
    }
    for(int j=0;j<steps_meat;j++){  //go through the path of finding meaty from the common node mentioned above
        if(pathToMeat[j]==commonNode_key){
            
            for(int i=j+1;i<steps_meat;i++){
                ansPath[steps_ans] = pathToMeat[i];
                steps_ans++;
            }
            break;
        }
    }
    cout<<endl<<"Capoo successfully found his favorite meaty<3."<<endl;
    cout<<endl<<"Shortest path to find the meaty :"<<endl;
    
    for(int i=0;i<steps_ans;i++){   //print the path
        if(i!=steps_ans-1){
            cout<<ansPath[i]<<"->";
        }else{
            cout<<ansPath[i]<<endl;
        }

    }

    
}

int main(){
    char action;
    bool escape=false;
    bool finishmode=false;
    string filename;
    char filetext[5];
    int map[14];
    int count=0;
    int swordloc,meatloc,broccoliIndex;
    while(!escape){
        cout<<"(1)Binary search Tree"<<endl;
        cout<<"(2)Finding Meaty."<<endl;
        cout<<"(0)Escape and face to music next year"<<endl;
        cin>>mode;
        if(mode==1){            //part 1
            BST bst(NULL);
            finishmode=false;
            while(!finishmode){
                cout<<"(I)nsert a number."<<endl;
                cout<<"(D)elete a number."<<endl;
                cout<<"(S)earch a number."<<endl;
                cout<<"(P)rint 4 kinds of orders."<<endl;
                cout<<"(R)eturn"<<endl;
                cin>>action;
                if(action=='i'){                            //insert
                    cout<<"Enter numbers : ";
                    for(;;){
                        int key;
                        cin>>key;
                        if(key!=-1){
                            bst.Insert(key);
                        }else break;
                    }
                }else if(action=='d'){                          //delete
                    cout<<"Enter numbers to deleted : ";
                    for(;;){
                        int key;
                        cin>>key;
                        if(key!=-1){
                            bst.Delete(key);
                        }else break;
                    }
                }else if(action == 's'){                        //search
                    cout<<"Enter numbers to searching : ";
                    for(;;){
                        int key;
                        cin>>key;
                        if(key!=-1){
                            bst.Search(key);
                        }else break;
                    }
                }else if(action=='p'){                          //traversal
                    bst.printTraversal();
                }else if(action=='r'){finishmode=true;}
            }
            bst.DeleteAllNode(bst.root);                        //release the memory
        }else if(mode==2){          //part 2
            BST bst(NULL);
            count=0;
            finishmode=false;
            ifstream fin;
            cout<<"Please input the map file: ";
            cin>>filename;
            fin.open(filename);		        //open bstmap file by input string
            if(fin.is_open()){
                cout<<"Load file success."<<endl<<endl;

                while(!fin.eof()){
                    fin.getline(filetext, sizeof(filetext));        //read file line by line
                    map[count] = atoi(filetext);        //change string to integer
                    count++;
                }
            }else {
                cout<<"fail to open file"<<endl;	
                exit(1); //shut down program
            }
            fin.close();

            for(int i=0;i<count;i++){           //build bst for bstmap.txt
                bst.Insert(map[i]);
            }
            cout<<"Please input the sword location: ";
            cin>>swordloc;
            cout<<"Please input the Meaty's location: ";
            cin>>meatloc;
            cout<<"Please input the broccoli traps' index (0~9): ";
            cin>>broccoliIndex;
            cout<<endl;
            for(int i=0;i<count;i++){
                int temp = map[i];
                bool deleted = false;
                while(temp!=0){                         //delete the node if that node's key has the broccoli's Index
                    int part = temp%10;
                    temp/=10;
                    if(part==broccoliIndex && !deleted){
                        bst.Delete(map[i]);
                        deleted = true;
                    }
                }
            }
            bst.path(bst,map,count,swordloc,meatloc);       //find the fastest route for saving meaty
            bst.DeleteAllNode(bst.root);        //release memory
            
        }else if(mode==0){      //escape, finish the program
            escape=true;
        }
    }


    return 0;
}





