#include <stdio.h>
#include <math.h>

int draw_triangle(int side1,int side2,int side3);
void type_triangle(int side1,int side2,int side3);
int perimeter_triangle(int side1,int side2,int side3);
double area_triangle(int side1,int side2,int side3,int perimeter);

int main(){
	int side1,side2,side3,perimeter,ret;
	double area;
	printf("The length of the first side:\n");
	scanf("%d",&side1);
	printf("The length of the second side:\n");
	scanf("%d",&side2);
	printf("The length of the third side:\n");
	scanf("%d",&side3);
	ret=draw_triangle(side1,side2,side3);
	if(ret==1){
		printf("According to the triangle inequality theorem, this triangle can be drawn.\n\n");
	}
	else{
		printf("According to the triangle inequality theorem, this triangle cannot be drawn.\n\n");
		return 0;
	}
	type_triangle(side1,side2,side3);
	perimeter=perimeter_triangle(side1,side2,side3);
	printf("The perimeter of the triangle:%d\n",perimeter);;
	area=area_triangle(side1,side2,side3,perimeter);
	printf("The area of the triangle:%lf\n",area);
	return 0;
}

int draw_triangle(int side1,int side2,int side3){
	int control,ret=0;
	if(side2>side1){  //For "side1-side2<side3" side1 has to be bigger one
		control=side1;
		side1=side2;
		side2=control;
	}
	if(side1+side2>side3 && side1-side2<side3){

		ret=1;
		return ret;
	}

	return ret;
}

void type_triangle(int side1,int side2,int side3){
	if(side1==side2 && side1==side3){
		printf("It is a Equilateral Triangle\n");
	}
	else if(side1==side2 || side1==side3 || side2==side3){
		printf("It is a Isosceles Triangle\n");
	}
	else{
		printf("It is a Scalene Triangle\n");
	}
}

int perimeter_triangle(int side1,int side2,int side3){
	int perimeter;
	perimeter=side1+side2+side3;
	return perimeter;
}

double area_triangle(int side1,int side2,int side3,int perimeter){
	double area,halfp;
	halfp=perimeter/2;
	area=sqrt(halfp*(halfp-side1)*(halfp-side2)*(halfp-side3));
	return area;
}
























