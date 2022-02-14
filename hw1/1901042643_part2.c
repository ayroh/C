#include <stdio.h>
#include <math.h>

int number_length(int number);
int find_digit(int number,int index);

int main(){
	int number,length,index,index2,answer;
	printf("Enter a number (maximum 6 digits):\n");
	scanf("%d",&number);
	length=number_length(number);
	printf("Your number has %d digits\n\n",length);
	printf("When your number written 100 times next to each other, which digit of this number would you like to see? :\n");
	scanf("%d",&index);
	index2=index;      /* for last printf */
	if(index%length==0){  /* in this case we don't need to use pow() so we take index as 0 because user wants us to return last digit */
		index=0;
	}
	else{
	index=length-(index%length);  /* we will use index through 6(or what user says) digits so we need to mod it and i will use power method so i need 10^(length-index) not index */
 }
	number=find_digit(number,index);
	printf("\n%d.th digit of the big number sequence: %d",index2,number);
	return 0;
}

int number_length(int number){
	int length;
	length=1+log10(number);  /* log10 gives us minus 1 of the numbers length so we add 1 */
	return length;
}

int find_digit(int number,int index){
	int div;
	div=pow(10,index);    /* my method is that i will switch wanted digit to last digit and mod it with 10 */
	number=(number/div)%10;
	return number;
}
