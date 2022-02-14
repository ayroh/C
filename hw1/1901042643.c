#include <stdio.h>
#include <math.h>

void find_root();
void find_newtonian_root();
int find_multiple_closest(int a,int b);
int root1,root2;/* We find roots in first function for using it as comparison with estimated root in second fonction.So i declare this roots as global variables for using for both functions */

void main(){
	int x,y;
	find_root();
		
	find_newtonian_root();
	
	printf("\nEnter 2 integer\n");
	scanf("%d%d",&x,&y);
	if(y>x){//Control for sending big number first
	find_multiple_closest(y,x);
	}
	else{
	find_multiple_closest(x,y);
	}

}

void find_root(){
	int delta,a,b,c;
	printf("Enter the coefficients of quadratic equation for finding roots\n");
	scanf("%d %d %d",&a,&b,&c);
	delta=(b*b)-(4*a*c);
	if(delta<0){
		printf("Your equation %dx^2 %dx %d does not have any real roots.\n\n",a,b,c);
	}
	if(delta>0){
		root1=(-b+sqrt(delta))/(2*a);
		root2=(-b-sqrt(delta))/(2*a);
		printf("Your equation %dx^2 %dx %d have real roots {%d,%d}.\n\n",a,b,c,root1,root2);
	}
	if(delta==0){
		root1=(-b)/(2*a);
		printf("Your equation %dx^2 %dx %d have real root {%d}.\n\n",a,b,c,root1);
	}
}

void find_newtonian_root(){
	
	float i,a,b,c,initial,diff,estroot,fx,control;
	int s=1;//Number of steps
	printf("Enter the coefficients and initial number of quadratic equation\n");
	scanf("%f %f %f %f",&a,&b,&c,&initial);
	printf("\n");
		printf("Step  	x 	  f(x)	        Difference\n\n");
		if(root2>root1){/*I choose root1 for big root cuz we need a comparison root with estimated root*/
			control=root1;
			root1=root2;
			root2=control;
		}
	diff=initial-root1;//at first we need to do it 1 time for finding first estroot without printing it
	estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
	initial=estroot;	
	
			 estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
			diff=initial-root1;
			fx=(a*initial*initial+b*initial+c);
			printf("x%d      %.4f     %.4f        %.4f\n",s,initial,fx,diff);
			initial=estroot;
			s=s+1;
			
			 estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
			diff=initial-root1;
			fx=(a*initial*initial+b*initial+c);
			printf("x%d      %.4f     %.4f        %.4f\n",s,initial,fx,diff);
			initial=estroot;
			s=s+1;
			
			 estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
			diff=initial-root1;
			fx=(a*initial*initial+b*initial+c);
			printf("x%d      %.4f     %.4f        %.4f\n",s,initial,fx,diff);
			initial=estroot;
			s=s+1;
			
			 estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
			diff=initial-root1;
			fx=(a*initial*initial+b*initial+c);
			printf("x%d      %.4f     %.4f        %.4f\n",s,initial,fx,diff);
			initial=estroot;
			s=s+1;
			
			 estroot=initial-(a*initial*initial+b*initial+c)/(a*2*initial+b);
			diff=initial-root1;
			fx=(a*initial*initial+b*initial+c);
			printf("x%d      %.4f     %.4f        %.4f\n",s,initial,fx,diff);
			initial=estroot;
			s=s+1;

}

int find_multiple_closest(int a,int b){
	int c=a/b,d=c+1;
	if(a%b==0){
		printf("Closest number to %d that is multiple of %d is itself.\n",a,b);
	}
		c=a-(c*b);
		d=(d*b)-a;
	if(c>d && d>0){
		printf("Closest number to %d that is multiple of %d is %d.\n",a,b,d+a);
	}
	if(d>c && c>0){
		printf("Closest number to %d that is multiple of %d is %d.\n",a,b,a-c);		
	}
}
