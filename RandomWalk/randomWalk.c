#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int n,m,problem,count=0,PosC,PosR;
int **floorMark;
int finish=0,quit=0;
char mode;

void buildArray(int n,int m){
	floorMark = calloc(n, sizeof(int*));
	for(int i=0;i<n;i++){
		floorMark[i] = calloc(m, sizeof(int));
	}
}
int move(int k){
	switch(k){
		case 0: case 1: case 2:
			return 1;
			break;
		case 3: case 4:
			return 0;
			break;
		case 5: case 6: case 7:
			return -1;
			break;
	}
}
void check(){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(floorMark[i][j]==0) {
				return;
			}
			if(i==n-1 && j==m-1) {
				finish=1;
			}
		}
		
	}
}
void reset(){
	count=0;
	finish=0;
}
void path(){
	while(!finish){
		int row = PosR+move((rand()%8)+0);
		int col = PosC+move((rand()%8)+0);
		if((row > -1 && row < n) && (col > -1 && col < m)){
			PosR=row; PosC=col;
			count++;
			floorMark[row][col]++;	
		}
		check();
	}
	printf("%d\n",count);
	for(int i=0;i<n;i++){
		printf("   ");
		for(int j=0;j<m;j++){
			printf("%2d ",floorMark[i][j]);
		}
		printf("\n");
	}
}
int main(){
	srand(time(NULL));
	do{
		scanf("%c",&mode);
		if(mode=='a'){
			scanf("%d %d",&n,&m);
			PosR=n/2; PosC=m/2;
			buildArray(n,m);
			path();
			for(int i=0;i<n;i++) {
				free(floorMark[i]);
			}
			free(floorMark);
		}else if(mode=='b'){
			scanf("%d",&problem);
			if(problem==1){
				n=15; m=15;
				PosR=10; PosC=10;
				buildArray(n,m);
				path();
				for(int i=0;i<n;i++) {
					free(floorMark[i]);
				}
				free(floorMark);
			}else{
				
				n=39; m=19;
				PosR=1; PosC=1;
				buildArray(n,m);
				path();
				for(int i=0;i<n;i++) {
					free(floorMark[i]);
				}
				free(floorMark);
			}
		}
		reset();
	}while(mode!='q');
	return 0;
}
