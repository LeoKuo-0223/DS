#include <stdio.h>
#include <stdlib.h>
#define MAX 100 
struct node
{
     int data;
     struct node* left;
     struct node* right;
     struct node* parent;
};
struct node *stack[MAX];
int top=-1;		
 
int isEmpty(){
	return top==-1; 
} 
void push(struct node *data){
	if(top>=MAX){
	 return;	
	}else{
		stack[++top]=data;
	}
 
} 
void pop(){
	if(isEmpty()) return;
	else top--;
}


 
void insert(struct node *node, int *a, int index, int n,struct node *lastnode)
{
     int back;
     while (index < n-1) {
		 	back=0;
          if(node->left==NULL){
			  if(a[index+1]!=-1){ 
				   index++;
				   node->left = malloc(sizeof(struct node));
				   node->left->data = a[index];
				   node->parent = lastnode;
				   push(node);
				   node=node->left;
			  }else if(a[index+2]!=-1){
				   index+=2;
				   node->right = malloc(sizeof(struct node));
				   node->right->data = a[index];
				   node->parent = lastnode;
				   push(node);
				   node = node->right;

			  }else {
				  index+=2;
				  back=1; //left is empty but a[index+1]==-1
			  }
          }else if(node->right==NULL){
			  if(a[index+1]!=-1){
				   index++;
				   node->right = malloc(sizeof(struct node));
				   node->right->data = a[index];
				   node->parent = lastnode;
				   push(node);
				   node = node->right;
			  }else {
				  index++;
				  back=1; //right is empty but a[index+1]==-1
			  }
          }else {
			  back=1; //left and right is not empty
		  }
		  if(back){
			  	node = stack[top];
				pop();
		  }
	 }

}



void printInorder(struct node* node)
{
     if (node == NULL)
          return;
     printInorder(node->left);
     printf("%d ", node->data); 
     printInorder(node->right);
}
void printPreorder(struct node* node)
{
     if (node == NULL)
          return;
     printf("%d ", node->data);
     printPreorder(node->left); 
     printPreorder(node->right);
}

 
void swapTree(struct node*node)
{
	struct node*temp;
	if(node!=NULL) return;
		temp=node->left;
		node->left=node->right;
		node->right=temp;
		swapTree(node->left);
		swapTree(node->right);
		
}
int main()
{    
     int num, value;
     int a[100];
     scanf("%d", &num);
     for (int i = 0; i < num; i++){
          scanf("%d",&a[i]);
     }     
     struct node *root;
     root = malloc(sizeof(struct node));;
	 root->data = a[0];
     insert(root, a, 0, num,NULL);

     swapTree(root);

     printPreorder(root);
     printf("\n");
     printInorder(root);
     printf("\n"); 

      return 0;
}
