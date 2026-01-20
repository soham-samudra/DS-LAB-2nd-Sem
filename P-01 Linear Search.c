#include<stdio.h>
void main() {

	int n,i,key,pos;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
		{
		scanf("%d",&arr[i]);
		}
	scanf("%d",&key);
int flag=0;
    for (i=0;i<n;i++) {
       if(key == arr[i])
       {flag=1;
	   pos=i;}
	}
	if (flag == 1) {
		printf("found at position %d\n", pos);
	} else {
		printf("%d not found\n", key);
	}
}