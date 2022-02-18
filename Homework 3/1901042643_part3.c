#include <stdio.h>

int andop(int a,int b);

int main(){
	int a,b,lcont1=1,lcont2=2,bcont1=1,bcont2=1,length1,length2,result;
	while(lcont1!=lcont2 || bcont1!=0 || bcont2!=0){  /* 3 control points that controls equality of length of numbers and are there binary */
	bcont1=0;
	bcont2=0;
	lcont1=1;
	lcont2=1;
	printf("First Integer: ");
	scanf("%d",&a);
	printf("Second Integer: ");
	scanf("%d",&b);
	length1=a;
	length2=b;
	while(length1>1){
		if(length1%10>1){
			bcont1+=1;
		}
		length1/=10;
		lcont1+=1;
	}
	while(length2>1){
		if(length2%10>1){
			bcont2+=1;
		}
		length2/=10;
		lcont2+=1;
	}
	if(lcont1!=lcont2){
		printf("Integers should have the same length, please enter 2 new integers.\n");
}
	if(bcont1!=0 || bcont2!=0){
		printf("Integers should be binary, please enter 2 new integers.\n");
}
}
result = andop(a,b);
printf("%d AND %d = %d\n",a,b,result);
}


int andop(int a,int b){
int controlnumber,number,mult = 1; /* in this function i equalize a+b to 2 number.With first one i control every digit in order.If it is 2(1+1) then it has to be 1,if it is 1(1+0) then it has to be 0,and 0 has to be 0 */
controlnumber = a + b;			   /* With mult number (i increase 1 digit every for loop) i decrease our number by controling control number  */
number = controlnumber;
while(controlnumber>1){
	if(controlnumber%10==2){
		number -= mult;
	}
	else if(controlnumber%10==1){
		number -= mult;
	}
	mult *= 10;
	controlnumber /= 10;
}
return number;
}
