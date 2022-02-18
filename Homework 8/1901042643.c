#include <stdio.h>
#include <math.h>

/*												
												       	  3   8	 																				
													    7       4	  									
														    S    	<--- MY ORIENTATION DESIGN										
													    2  	    5																						
													   	  6   1	 
*/

int generate_hofstadters_sequence (int *arr, int n); //   I cant do it without returning so i use int
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);
double calculatesd(int arr[],double *sum,int n,double *mean);
void install_pipes (int visited[8][8], int x, int y, int orientation);
char* remove_duplicates (char* str);
int is_end(int visited[8][8]);
void menu ();

int cnt = 0,cnt2 = 0,arro[64]; // i don't want to change function prototypes so i declared global counters and an array for printing only right orientation set 
void main(){
	srand(time(NULL));
	menu();
}

void menu(){
	char str[100];
	int choice1,choice2,arr[500],n,i,j,k,x,y,end,orientation,max_value = 0,index = 0,cont = 0,visited[8][8];
	double mean = 0,sd;
	for(i = 0;i < 8;i++){
		for(j = 0;i < 8;i++){
			visited[i][j] = 0; // Empty all points
		}
	}
	
	memset(str,10,100); //  For control at the remove_duplicates
	memset(arr,0,500);
AnotherOne:
	printf("Welcome to Homework 8, please choose one of the parts to continue\n__________________________\n\n1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n\n");
	scanf(" %d",&choice1);
	switch(choice1) {
		case 1:
AndAnotherOne:
			printf("Please make your choice:\n_______________\n1) Fill Array\n2) Find Biggest Number\n3) Calculate Sum\n4) Calculate Standard Deviation\n5) Exit\n\n");
			scanf("%d",&choice2);

			switch(choice2) {
				case 1:
					printf("Enter a number.\n");
					scanf("%d",&n);
					generate_hofstadters_sequence(arr,n);
					printf("Sequence is: ");
					for(i = 0; i < n; i++) {
						printf("%d ",arr[i]);
					}
					printf("\n\n");
					cont = 1;
					goto AndAnotherOne;
				case 2:
					if(cont == 0){
						printf("First fill the Array please.(Case 1)\n\n");
					}
					else{
					max_value = arr[0];
					max_value = find_max(arr,n,max_value);
					printf("%Max value of the array is: %d\n\n",max_value);
					}
					goto AndAnotherOne;
				case 3:
					if(cont == 0){
						printf("First fill the Array please.(Case 1)\n\n");
					}
					else{
					sum_array(arr);
					printf("Sum of the numbers in the array is: %d\n\n",arr[n-1]);
					for(i = n-2; i >= 0; i--) {	// for shifting back
						arr[i+1] = arr[i];
					}
					arr[0] = 1;
				}
					goto AndAnotherOne;
				case 4:
				if(cont == 0){
						printf("First fill the Array please.(Case 1)\n\n");
					}
					else{
					sd = std_array(arr,&mean,n,index);
					printf("Standard Deviation of the array is: %.3lf\nMean of the array is: %.3lf\n\n",sd,mean);
					mean = 0;
					sd = 0;
					}
					goto AndAnotherOne;
				case 5:
					goto AnotherOne;
				default:
					printf("Make a valid choice.\n\n");
					goto AndAnotherOne;
			}

		case 2:
			for(k = 0;k < 10;k++){
				for(i = 0;i < 8;i++){
					for(j = 0;j < 8;j++){
						visited[i][j] = 0; // Empty all points
					}
			}
			end = 0;				
			cnt = 0;
			cnt2 = 0;
				while(end != 1){
				orientation = 1 ;		// at first its either q5 or q1 so i chose 1
				x = 0;
				y = 0;
				visited[0][0] = 1;
				install_pipes(visited,x,y,orientation);
				end = is_end(visited);
				if(end == 1){
					printf("\n");
					for(i = 0;i < 64;i++){
							printf("O%d, ",arro[i]); //printing correct ways
							arro[i] = 0;
					}
					printf("\n\n");
					break;
				}
				for(i = 0;i < 8;i++){
					for(j = 0;j < 8;j++){
						visited[i][j] = 0; // Empty all points
					}
			}
		}
	}
			goto AnotherOne;
			break;
		case 3:
			printf("Please enter a string (max 100 char): \n");
			gets(str); // For clearing buffer i use 2 gets
			gets(str);
			remove_duplicates(str);
			printf("\n%s\n",str);
			goto AnotherOne;
		case 4:
			break;
		default:
			printf("Make a valid choice.\n\n");
			goto AnotherOne;
	}
}

int generate_hofstadters_sequence (int *arr, int n) {
	int i;
	if(arr[n-1] != 0){ // if arr[n-1] has a value already returning it back
		return arr[n-1];
	}
	if (n == 1 || n == 2) {
		i = 1;
	} else {
		i = generate_hofstadters_sequence(arr,n - generate_hofstadters_sequence(arr,n-1)) + generate_hofstadters_sequence (arr,n - generate_hofstadters_sequence(arr,n-2));
	}
	arr[n-1] = i;
	return i;
}


int find_max (int arr[], int index, int max_value){
	if(index == 0) {
		return max_value;
	}
	if(arr[index] > max_value) {
		max_value = arr[index];
	}
	find_max(arr,index-1,max_value);
}

int sum_array (int arr[]) {
	int a;
	if(*(arr+1) == 0) {
		return;
	}
	a = *(arr+1); // for shifting array to left at the end i will shift back and use "arr[0] = 1;"
	*(arr+1) += *arr;
	*arr = a;
	arr++;
	sum_array(arr);
}


double std_array (int arr[], double *mean, int n,int index) {
	double sum = 0,sd = 0;
	int i;

	sum_array(arr);
	sum = arr[n-1];
	for(i = n-2; i >= 0; i--) {	// for shifting back
		arr[i+1] = arr[i];
	}
	arr[0] = 1;
	*mean = sum/n;
	sum = 0;
	sd = calculatesd(arr,&sum,n,mean);
	return sd;
}

double calculatesd(int arr[],double *sum,int n,double *mean) {
	if(*arr == 0) {
		return;
	}
	*sum += pow(*arr - *mean, 2);
	calculatesd(arr+1,sum,n,mean);
	return sqrt(*sum/n);
}


void install_pipes (int visited[8][8], int x, int y, int orientation){
		if(cnt == 64){ 			// after 64 times success jumping that means its over
			int i;
			cnt = 0;
			cnt2 = 0;
		}
	switch(orientation){
		case 1:
			if(visited[x+2][y+1] == 1 || x+2 > 7 || y+1 > 7){
				orientation += 1;
				if(cnt2 == 8){   // if all 8 orientation filled that means it can't go on
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;  // total visited count
			cnt2=0; // orientation count
			x += 2;
			y += 1;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 2:
			if(visited[x+1][y-2] == 1 || x+1 > 7 || y-2 < 0){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x += 1;
			y -= 2;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 3:
			if(visited[x-2][y-1] == 1 || x-2 < 0 || y-1 < 0){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x -= 2;
			y -= 1;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 4:
			if(visited[x-1][y+2] == 1 || x-1 < 0 || y+2 > 7){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x -= 1;
			y += 2;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 5:
			if(visited[x+1][y+2] == 1 || x+1 > 7 || y+2 > 7){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x += 1;
			y += 2;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 6:
			if(visited[x+2][y-1] == 1 || x+2 > 7 || y-1 < 0){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x += 2;
			y -= 1;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 7:
			if(visited[x-1][y-2] == 1 || x-1 < 0 || y-2 < 0){
				orientation += 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x -= 1;
			y -= 2;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
		case 8:
			if(visited[x-2][y+1] == 1 || x-2 < 0 || y+1 > 7){
				orientation = 1;
				if(cnt2 == 8){
					return;
				}
				cnt2++;
				install_pipes(visited,x,y,orientation);
			}
			else{
			arro[cnt] = orientation;
			cnt++;
			cnt2=0;
			x -= 2;
			y += 1;
			visited[x][y] = 1;
			orientation = 1 + rand()%8;
			install_pipes(visited,x,y,orientation);
		}
	}
}


char* remove_duplicates (char* str){
	int i = 0;
	if(*str == 0){
		return;
	}
	if(*str == *(str+1)){
		while(*(str+i) != 10){   // i declared all str array to 10 first
			*(str+i) = *(str+i+1);
			i++;
		}
		i = 0;
	}
	if(*str == *(str+1)){ // this means we have a case like "pataaaates" more than one 'a' in a row
		remove_duplicates(str);
	}
	else{
	remove_duplicates(str+1);
	}
	return str;
}

int is_end(int visited[8][8]){
	int i,j;
	for(i = 0;i < 8;i++){
		for(j = 0;j < 8;j++){
			if(visited[i][j] == 0){
				return 0;
			}
		}
	}
	return 1;
}




