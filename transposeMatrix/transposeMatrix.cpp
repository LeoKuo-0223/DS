#include<iostream>
using namespace std;

class MatrixTerm{
	public:
		int row,col,value;
		friend class SparseMatrix;
	private:
	
};

class SparseMatrix{
	public:
		int terms;
		int rows;
		int cols;
		SparseMatrix(int r,int c,int t){
			rows=r;
			cols=c;
			terms=t;
		}
		MatrixTerm *smArray;
		void FastTranspose();
	private:
};

void SparseMatrix::FastTranspose(){
	SparseMatrix b(cols,rows,terms);
	MatrixTerm bsmArray[terms];

	if(terms>0){
		int *rowSize = new int[cols];
		int *rowStart = new int[cols];
		for(int i=0;i<cols;i++) {rowSize[i]=0; rowStart[i]=0;}
		for(int i=0;i<terms;i++) rowSize[smArray[i].col]++;
		rowStart[0]=0; //initial rowStart 
		for(int i=1;i<cols;i++) rowStart[i] =rowStart[i-1]+rowSize[i-1]; 
		b.smArray  = bsmArray;
for(int i=0;i<cols;i++){
	cout<<rowSize[i];
}
cout<<endl;
for(int i=0;i<cols;i++){
	cout<<rowStart[i];
}
cout<<endl;
		for(int i=0;i<terms;i++){
			int j=rowStart[smArray[i].col];
			b.smArray[j].row = smArray[i].col;
			b.smArray[j].col = smArray[i].row;
			b.smArray[j].value = smArray[i].value;
			rowStart[smArray[i].col]++;
		}
		delete []rowSize;
		delete []rowStart;
	}
	for(int i=0;i<terms;i++){
		cout<<b.smArray[i].row<<" "<<b.smArray[i].col<<" "<<b.smArray[i].value<<endl;
	}
	return ;
}
int main(){
	SparseMatrix a(6,6,8);
	MatrixTerm smArray[a.terms];
	a.smArray=smArray;
	cout<<"Input row col value\n";
	for(int i=0;i<a.terms;i++){
		cin>>a.smArray[i].row>>a.smArray[i].col>>a.smArray[i].value;
	}
	
	cout<<"Fast transposing\n";
	cout<<"Row col value\n";
	a.FastTranspose();
	return 0;

}
