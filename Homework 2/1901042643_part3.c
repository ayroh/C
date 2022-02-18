#include <stdio.h>
#include <math.h>


int main(){
	double money,Euro=6.69,Dollar=6.14;
	int selection;
	printf("***** Welcome to ABC Exchange Office *****\n\n");
	printf("Enter your amount:\n");
	scanf("%lf",&money);
	printf("Please select your currency\n");
	printf("1. Turkish Lira\n");
	printf("2. Euro\n");
	printf("3. Dollar\n");
	printf("You have %lf Turkish Liras\n",money);
	printf("Choose which currency you want to convert\n");
	scanf("%d",&selection);
	switch(selection){
		case 1:
				printf("You have %lf Turkish Liras\n",money);
			break;
		case 2:
				printf("You have %lf Euros\n",money/Euro);
			break;
		case 3:
				printf("You have %lf Dollars\n",money/Dollar);
			break;
		default:printf("Your selection is invalid.\n"); break;
	}
}
