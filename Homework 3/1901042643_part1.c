
#include <stdio.h>

int sum(int n,int flag);
int mult(int n,int flag);

void main(){
int opchoice,flag,number,result;
	printf("Enter an integer: ");
		scanf("%d",&number);
	printf("Please enter '0' for sum, '1' for multiplication\n");
		scanf("%d",&opchoice);
	printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
		scanf("%d",&flag);
			switch(opchoice){
			case 0:
				result = sum(number,flag);
				printf(" = %d\n",result);
			break;
			case 1:
				result = mult(number,flag);
				printf(" = %d\n",result);
			break;
			default:
			printf("Unsupported operation.\n");
			break;
}
}


int sum(int n,int flag){
	int i,sum = 0;
		if(flag==0){
			for(i=2;i<=n-2;i+=2){
				sum+=i;
				printf("%d + ",i);
			}
		}
		else if(flag==1){
			for(i=1;i<=n-2;i+=2){
				sum+=i;
				printf("%d + ",i);
			}
		}
		else{
			printf("Invalid value for odd/even selection.\n");
			return 0;
		}
		sum+=i;		/* I put last print here for better view (without '*' symbol) */
		printf("%d",i);
	return sum;
	}


int mult(int n,int flag){
	int i,product = 1; /* product=1 because it is a multiplication */
		if(flag==0){ 
			for(i=2;i<=n-2;i+=2){
				product*=i;
				printf("%d * ",i);
			}
		}
		else if(flag==1){
			for(i=1;i<=n-2;i+=2){
				product*=i;
				printf("%d * ",i);
			}
		}
		else{
			printf("Invalid value for odd/even selection.\n");
			return 0;
		}
		product*=i;		/* Same reason with sum function */
		printf("%d",i);
	return product;
}
