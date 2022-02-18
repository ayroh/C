#include <stdio.h>
#include <math.h>

int isprime(int a);


void main(){
	int N,flag,i;
		printf("Please enter an integer: ");
		scanf("%d",&N);
		for (i=2;i<N; ++i){
			flag=isprime(i);
			if(flag==0){
				printf("\n%d is a prime number\n",i);
			}
			else{
				printf("\n%d is not a prime number, it is dividible by %d\n",i,flag);
			}
		}
}

int isprime(int a){
	int i;
		for (i=2;i<=sqrt(a); ++i){ /* Control for using function you described for every number between 2 and Square root of number */
			if(a%i==0){
				return i;  /* if it is not a prime it will return number that divides our number */
			}
		}
	return 0; 	/* if it is not a prime number we don't have to return anything because main functions knows current number so it can print it */
}
