#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
using namespace std;
#define NUM 100


class Stack{	//declare the Stack Class
	public:
		Stack();
		bool isEmpty() const;
		void push(int);
		void pop();
		int Top() const;
	private:
		int top;
		int array[NUM];
};
Stack::Stack(){	//constructor of Stack class
	top=-1;			//empty stack with top value -1
}

bool Stack::isEmpty() const{		//read only function for checking the stack is empty or not
	return top== -1;
}

void Stack::push(int integer){			//push integer into the stack
	if(top==top-1) cout<<"stack is full";	
	else array[++top]=integer;
}

void Stack::pop(){		//pop out the top object from stack
	if(isEmpty()) cout<<"stack is empty";
	else array[top--];
}

int Stack::Top() const{		//read the top object in the stack
	if(isEmpty()) cout<<"stack is empty";
	else {
		return array[top];
	}
}
//declare variables use in functions
char *mazeChar;		//pointer
char fileInput;		//charr type variable receive every character in the txt file
int mazeNum;		//save the value of maze in type integer
int maze[17][17];
int mark[17][17];	//record position 
Stack rowStack;		//record row, column, direction information
Stack colStack;		
//Stack dirStack;
int PosC,PosR,endPosC,endPosR;
ifstream fin;
int step=0;


void initialStack(int row,int col){	//initialize the first position
	rowStack.push(row);
	colStack.push(col);
	mark[row][col]=1;
	cout<<step<<":"<<rowStack.Top()<<","<<colStack.Top()<<endl;
}

int moveRow(int dir){	//determine the row of next step by parameter "direction"
	switch(dir){
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return -1;
		break;
	case 3:
		return 0;
		break;
	default:
		break;
	}
}
int moveCol(int dir){	//determine the column of next step by parameter "direction"
	switch(dir){
	case 0:
		return 1;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return -1;
		break;
	default:
		break;
	}
}
void path(){	//control the path of rat
	initialStack(PosR, PosC); 	//initialize position in the begining
	while(!rowStack.isEmpty() && !colStack.isEmpty()){	//go forward if stacks are not empty, in other word, there are still some routes can try
		int row=rowStack.Top();			//take out row and column value from stack
		int col=colStack.Top();
		int dir=0;						//"0":right, "1": down, "2": up. "3":left
		while(dir<4){					//if there is another direction can try, keep trying
			int i = row+moveRow(dir);	//[i][j] means next position with different directions
			int j = col+moveCol(dir);
			//cout<<moveRow(dir)<<","<<moveCol(dir)<<","<<dir<<endl; //check every direction before next step
			if(i==endPosR && j==endPosC){	//when next step reach the EXIT
				step++;						//following statements will record the final step.
				mark[i][j]=1;
				cout<<step<<":"<<i<<","<<j<<endl;
				cout<<"successfully escaped!!\n";
				rowStack.push(i);
				colStack.push(j);
				return;
			}
			if(maze[i][j]!=1 && mark[i][j]!=1){		//when next position is not barrier and it is a new position (rat has never been to)
				step++;								//following statements record the position in the stack and print the step
				mark[i][j]=1;
				rowStack.push(i);
				colStack.push(j);
				cout<<step<<":"<<i<<","<<j<<endl;
				break;					//because the rat has already arrived in new position, break the while loop
										//	and research available direction again
			}else {						
				dir++;			//if there is a wall stand at the "dir" direction, change "dir" value, try another directions
			}
		}
		if(dir>3){		//if there isn't any direction can go, rat will go back along with the road just passed
			//cout<<"back"<<endl;		//check the rat go back or not
			step++;
			rowStack.pop();		//pop out the row and column value because the rat go back to the last position
			colStack.pop();
			if(!rowStack.isEmpty() || !colStack.isEmpty()){ //if any stack is not empty (still have some route can try), print the step
				cout<<step<<":"<<rowStack.Top()<<","<<colStack.Top()<<endl;
			}
		}

	}
	cout<<"Failed to escape."<<endl;
	for(int i=0;i<17;i++){
		for(int j=0;j<17;j++) mark[i][j]=0;	//reset the record of coodinates for next mazing problem
	}
	step=0; //reset step count
}

int main(){
	cout<<"enter filename : maze.txt\n";
	fin.open("maze.txt");		//open maze.txt file which is in the same folder as this .cpp file
	if(fin.is_open()){
		for(int i=0;i<17;i++){
			for(int j=0;j<18;j++){
				fin.get(fileInput);		//get maze information from maxe.txt
				if(j!=17){	//in order to omit new line character
					mazeChar = &fileInput;		//pointer point to "fileInput" variable
					maze[i][j]=atoi(mazeChar);		//initialize maze into 2D array
					cout<<maze[i][j];		//plot maze
				}
			}
			cout<<"\n";
		}
	}else {
		cout<<"fail to open file"<<endl;	
		exit(1); //shut down program
	}
	fin.close();
	while(true){	//infinite loop until enter (-1, -1) coodinate is entered
		cout<<"enter start position : ";
		cin>>PosR>>PosC;
		if(PosR==-1 && PosC==-1){
			cout<<"end the code.";
			exit(0);	//exit success
		}else{
			cout<<"enter exit position : ";
			cin>>endPosR>>endPosC;
		}
		path(); //function to control the rat and print the steps
	}
}
