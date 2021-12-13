#include<iostream>
#include<string.h>
#include"stack.h"

char expression[]="A/B-C+D*E-A*C";

char nextchar(int n){
	if(n<=sizeof(expression)/sizeof(expression[0])) return expression[n];
	else {
		cout<<"out of array";
		return 'x';
	}
}
int priorInstack(char notation){
	switch(notation){
		case '*': case '/': case '%':
			return 2;
			break;
		case '+': case '-':
			return 3;
			break;
		case '(':
			return 4;//low priority in stack
			break;
		default:
			return 8;
			break;
	}
}

int priorIncoming(char notation){
	switch(notation){
		case '*': case '/': case '%':
			return 2;
			break;
		case '+': case '-':
			return 3;
			break;
		case '(':
			return 1;//high priority in coming
			break;
		default:
			return 8;
			break;
	}
}

void convert(){
	Stack<char> stack;
	stack.push('#');
	char x;
	for(int i=0;(x=nextchar(i))!='\0';i++){
		if(x>=65&&x<=90){
			cout<<x;
		}else if(x==')'){
			for(;stack.Top()!='(';stack.pop()){
				cout<<stack.Top();
			}
			stack.pop(); //pop out '('
		}else{
			//cout<<stack.Top();
			while(priorInstack(stack.Top())<=priorIncoming(x)){
				cout<<stack.Top();
				stack.pop();
			}
			stack.push(x);
		}
	}
	for(;!stack.isEmpty();stack.pop()){
		cout<<stack.Top();
	}
}

int main(){
	convert();
	return 0;
}
