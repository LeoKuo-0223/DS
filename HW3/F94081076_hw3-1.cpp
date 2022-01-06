#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;
vector<int> output; 

struct Node{    //define node type, contain left, right child node and key value
    int key;
    struct Node *left, *right;
};
 
struct Node* newNode(int key){  //create node and allocate memory for the node
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}
 
void inorderTraversal(struct Node* root){   //define inorder Traversal
    if (root == NULL) {
        return;
    }else{
        inorderTraversal(root->left);
        // cout<<root->key<<" ";
        output.push_back(root->key);
        inorderTraversal(root->right);
    }
}
 

void preorderTraversal(struct Node* root){  //define preorder Traversal
    if (root == NULL) {
        return;
    }else{
        // cout<<root->key<<" ";
        output.push_back(root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root){ //define postorder Traversal
    if (root == NULL) {
        return;
    }else{
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        // cout<<root->key<<" ";
        output.push_back(root->key);
    }
}
 

struct Node* InPreBuildNode(int inorder[], int start, int end,int preorder[], int *pIndex){
    //build node structure when giving inorder and preorder
    if (start > end) {  //whene there is no unused value in preorder list
        return NULL;    //Let the child be the null value
    }else{
        //the node represnent the root in each subtree
        struct Node* node = newNode(preorder[(*pIndex)++]); //new the node for the preorder list one by one
        int i;  //record the index for the inorder list whose key value is the same as the preorder list aboved
        for (i = start; i <= end; i++){
            if (inorder[i] == node->key) break;
        }
        //split the inorder list into the part, represnt left subtree and right subtree respectively
        //create node by recursive
        node->left = InPreBuildNode(inorder, start, i - 1, preorder, pIndex);
        node->right = InPreBuildNode(inorder, i + 1, end, preorder, pIndex);
        return node;  
    }

}

struct Node* InPostBuildNode(int inorder[], int start, int end,int postorder[], int *pIndex){
    //build node structure when giving inorder and postorder
    if (start > end) {  //whene there is no unused value in postorder list
        return NULL;    //Let the child be the null value
    }else{
        struct Node* node = newNode(postorder[(*pIndex)--]);
        int i;  //record the index for the inorder list whose key value is the same as the postorder list aboved
        for (i = start; i <= end; i++){
            if (inorder[i] == node->key)  break;
        }
        //split the inorder list into the part, represnt left subtree and right subtree respectively
        //create node by recursive
        node->right = InPostBuildNode(inorder, i + 1, end, postorder, pIndex);
        node->left = InPostBuildNode(inorder, start, i - 1, postorder, pIndex);
        return node;
    }
}
 

struct Node* InPreBuildTree(int inorder[], int preorder[], int n){  //build tree by calling build node function recursively
    int preorderIndex = 0;  //initial the index for preorder list
    return InPreBuildNode(inorder, 0, n - 1, preorder, &preorderIndex);
}

struct Node* InPostBuildTree(int inorder[], int postorder[], int n){    //build tree by calling build node function recursively
	int postorderIndex = n-1;   //initial the index for the postorder list 
	return InPostBuildNode(inorder, 0, n-1, postorder, &postorderIndex);
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
	long num_Set;
	const char preinorder[] = "preorder-inorder";
	const char postinorder[] = "postorder-inorder";
	char orderType[18];
	int num_Node;
    char filetext[2048];
    string filename;
    string outputfileName;
    ifstream fin;
    ofstream outputfin;
    cout<<"Please input the file: ";
    cin>>filename;
    outputfileName = filename;
    outputfileName.replace(outputfileName.find("input"), 5, "output");
    outputfin.open(outputfileName);
    fin.open(filename);		        //open bstmap file by input string
    if(fin.is_open()){  //success to open file
        fin.getline(filetext, sizeof(filetext));   //read file line by line
        num_Set= atoi(filetext);        //change char to integer in order to get the number of set
        for(int s=0;s<num_Set;s++){
            fin.getline(orderType, sizeof(orderType));  //get the order type

            if(strcmp(orderType, preinorder)==0){   //preorder-inorder mode
                fin.getline(filetext, sizeof(filetext));    //get the number of node
                num_Node= atoi(filetext);   //change char to integer

                int inorder[num_Node];
                int preorder[num_Node];

                vector<string> preret;      //declare the vector for saving the preorder value 
                fin.getline(filetext, sizeof(filetext));    //get preorder text into char array
                string prestr(filetext);        //convert the char array to string type
                preret = split(prestr,' ');     //use the split function to cut the string into severl part by ' ' 
                for(int j=0;j<num_Node;j++){
                    preorder[j] = stoi(preret[j]);  //stoi() convert the string to integer
                }

                vector<string> inret;
                fin.getline(filetext, sizeof(filetext));    //get inorder text into char array 
                string instr(filetext); //convert to string type
                inret = split(instr,' ');   //cut the string by ' '
                for(int j=0;j<num_Node;j++){
                    inorder[j] = stoi(inret[j]);    //stoi() convert the string to integer
                }

                int length = sizeof(inorder)/sizeof(inorder[0]);
                struct Node* root = InPreBuildTree(inorder, preorder, length);  //delare the root node and start to build the tree

                postorderTraversal(root);   //traversal by postorder
                // cout<<endl;
                if(outputfin.is_open()){
                    for(int x=0;x<num_Node;x++){
                        outputfin<<output[x]<<' ';  //write the answer in the output file
                    }
                    outputfin<<'\n';
                }
                output.clear();     //clear output vector

            }else if(strcmp(orderType, postinorder)==0){  //postorder-inorder mode
                fin.getline(filetext, sizeof(filetext));
                num_Node= atoi(filetext);       //get the number of node and convert it to integer type

                int inorder[num_Node];
                int postorder[num_Node];

                vector<string> postret; //delare the vector with string type for saving the the postorder value
                fin.getline(filetext, sizeof(filetext));    //get the postorder value into char array
                string poststr(filetext);   //consrt char array to string
                postret = split(poststr,' ');   //cut the string by ' '
                for(int j=0;j<num_Node;j++){
                    postorder[j] = stoi(postret[j]);    //convert the string value to integer
                }

                vector<string> inret;       //declare the vector with string type
                fin.getline(filetext, sizeof(filetext));    //get the inorder value into char array
                string instr(filetext);     //convert char array to string
                inret = split(instr,' ');       //cut the string by ' ' 
                for(int j=0;j<num_Node;j++){    
                    inorder[j] = stoi(inret[j]);        //convert the string to integer
                }

                int length = sizeof(inorder)/sizeof(inorder[0]);
                struct Node* root = InPostBuildTree(inorder, postorder, length);    //declare the root node and start to build tree

                preorderTraversal(root);    //traversal in preorder
                // cout<<endl;
                if(outputfin.is_open()){
                    for(int x=0;x<num_Node;x++){
                        outputfin<<output[x]<<' ';      //write the answer in the output file
                    }
                    outputfin<<'\n';
                }
                output.clear();     //reset output vector
		    }
        }
    }else{  //open file failed
        cout<<"fail to open file"<<endl;	
        exit(1); //shut down program
    }
    fin.close();
    outputfin.close();
    return 0;
}



