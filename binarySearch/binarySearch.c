#include<stdio.h>
int BinarySearch(int *a,const int x,const int n){
	int left=0;
	int right=n-1;
	while(left<=right){
		int middle=(left+right)/2;
		if(x<a[middle]) right=middle;
		else if(x>a[middle]) left=middle;
		else return middle;
	}
	return -1;
}

int main(){
	int n,x;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	printf("which num do you want to search?");
	scanf("%d",&x);
	printf("Index of the num you search: %d ",BinarySearch(a,x,n));
}
