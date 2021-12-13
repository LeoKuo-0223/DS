#include<stdio.h>
void swap(int *a,int i, int smallerIndex){
	if(i==smallerIndex) return;
	int temp;
	temp = a[i];
	a[i]=a[smallerIndex];
	a[smallerIndex]=temp;
	return;
}

void selectionSort(int *a,const int n){
	for(int i=0;i<n;i++){
		int smallerIndex=i;
		for(int j=i+1;j<n;j++){
			if(a[j]<a[i] && a[j]<a[smallerIndex]){
				smallerIndex=j;
			}
		}
		swap(a,i,smallerIndex);

	}
}

int main(){
	int n=0;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	selectionSort(a,n);
	for(int i=0;i<n;i++){
		printf("% d ",a[i]);
	}

}
