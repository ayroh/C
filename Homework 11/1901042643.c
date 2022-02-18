#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct sitrakt{
	int num;
	struct sitrakt *next;
}list;

typedef struct separate{
	int n1;
	int n2;
}result;

int *read_array(char *filename);
list * read_linkedlist(char *filename);
list *add_node(list * iter,int num);
float * stats_array(int *arr);
float * stats_linkedlist(list *node);

result *generate_numbers(int *arr,list *node);
int find_duplicates(int i,int arr[]);

int N;

int main(){
	printf("***********************PART 1*************************\n\n\n");
	int i,numbercount = 0;	// number + 1 which is '-1' at the end of the array

	double average = 0,arrave = 0,llave = 0;

	clock_t begin = clock();
	int *arr = read_array("list.txt");
	clock_t end = clock();
	arrave += (double)(end-begin)/CLOCKS_PER_SEC;
	printf("Execution time of read_array() = %lf\n",(double)(end-begin)/CLOCKS_PER_SEC);

	begin = clock();
	list *node = read_linkedlist("list.txt");
	end = clock();
	llave += (double)(end-begin)/CLOCKS_PER_SEC;
	printf("Execution time of read_linkedlist() = %lf\n\n",(double)(end-begin)/CLOCKS_PER_SEC);

	begin = clock();
	node = read_linkedlist("list.txt");
	end = clock();
	llave += (double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	arr = read_array("list.txt");
	end = clock();
	arrave += (double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	arr = read_array("list.txt");
	end = clock();
	average += (double)(end-begin)/CLOCKS_PER_SEC;
	arrave += (double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	node = read_linkedlist("list.txt");
	end = clock();
	average += (double)(end-begin)/CLOCKS_PER_SEC;
	llave += (double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	node = read_linkedlist("list.txt");
	end = clock();
	average += (double)(end-begin)/CLOCKS_PER_SEC;
	llave += (double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	arr = read_array("list.txt");
	end = clock();
	average += (double)(end-begin)/CLOCKS_PER_SEC;
	arrave += (double)(end-begin)/CLOCKS_PER_SEC;

	llave /= 4;
	arrave /= 4;
	average /= 4;

	printf("Average of last four read_array() calls: %lf 			   (I called both functions 4 times with ALLAALLA order)\n",arrave);
	printf("Average of last four read_linkedlist() calls: %lf\n\n",llave);
	printf("Average of last four function calls: %lf     			   (Average of 2 functions)\n\n",average);

	printf("\nSize of array: %ld bytes -> (*arr) * N\n",(sizeof(*arr) * (N + 1)));  // N = 150000 as i 
	printf("Size of linked list: %ld bytes -> (*node) * N\n\n\n",(sizeof(*node) * N));

	begin = clock();
	float *ararr = stats_array(arr);
	end = clock();
	printf("Execution time of stats_array: %lf\n\n",(double)(end-begin)/CLOCKS_PER_SEC);
	printf("(Array) Min Value: %f\n",*ararr);	
	printf("(Array) Max Value: %f\n",*(ararr + 1));
	printf("(Array) Mean Value: %f\n",*(ararr + 2));
	printf("(Array) Standard Deviation: %f\n\n\n",*(ararr + 3));

	begin = clock();
	float *llarr = stats_linkedlist(node);
	end = clock();
	printf("Execution time of stats_linkedlist: %lf\n\n",(double)(end-begin)/CLOCKS_PER_SEC);
	printf("(LL) Min Value: %f\n",*llarr);	
	printf("(LL) Max Value: %f\n",*(llarr + 1));
	printf("(LL) Mean Value: %f\n",*(llarr + 2));
	printf("(LL) Standard Deviation: %f\n\n\n",*(llarr + 3));

	printf("--------------RESULT-----------------\n\n");
	printf(" Using structs to store and use data\n");
	printf(" requires slightly more time than\n");
	printf(" using arrays (in my ubuntu at least).So array wins the race\n\n\n");



	printf("***********************PART 2*************************\n\n\n");
	srand(time(NULL));
	int *narr;
	list *nlist;
	
	int n;
	printf("Please enter number of numbers you want in your array and linked list(minimum 10): ");
	scanf("%d",&n);
	int index,pos_neg,number;
	numbercount = 0;
	int number_of_wrongs = n / 10;			// i declare  n / 10 wrongs which you chose n before
	int randomnumbers[n/10];				// taking list of numbers that randomed
		
		numbercount++;
		narr = (int*)malloc(sizeof(int));		// first i malloc to realloc later
		nlist = (list*)malloc(sizeof(list));
		nlist->next = NULL;
		number = rand()%100 + 1;					// number between 1-100
		*narr = nlist->num = number;
		list *iter = nlist;

	for(i = 1;i < n;i++){		// implementing numbers
		numbercount++;
		narr = (int*)realloc(narr,numbercount * sizeof(int));
		number =rand()%100 + 1;					// number between 1-100
		*(narr + i) = number;
		iter = add_node(nlist,number);
	}
	for(i = 0;i < n/10;i++){		// implementing wrongs ones
		randomnumbers[i] = rand()%n;						// random positions
		if(find_duplicates(i,randomnumbers) == 0){
			i--;
			continue;
		}
		index = randomnumbers[i];
		pos_neg = rand()%2;						// 0 means positive and 1 means negative
		if(pos_neg == 0) *(narr + index)+=1;
		else *(narr + index)-=1;
	}
	iter = nlist;
	result *words = generate_numbers(narr,nlist);			// finding wrong ones
	printf("\nArray   |   Linked List\n------------------\n");
	for (i = 0; i < n/10; i++){
		printf("  %d    |   %d\n",words[i].n1,words[i].n2);
	}
	printf("\n");

}

int *read_array(char *filename){
	int *arr = (int*)malloc	(sizeof(int));  // i have to allocate first to use realloc
	FILE *fp = fopen(filename,"r");
	int i = 0,numbercount = 0;
	char buffer[10];
	while(1){
		numbercount++;
		arr = (int*)realloc(arr,numbercount * sizeof(int));
		i = -1;		// to start with i = 0 after i++
		do{
			i++;
			buffer[i] = fgetc(fp);
			if(feof(fp)){
				arr = (int*)realloc(arr,numbercount * sizeof(int));
				*(arr + numbercount - 1) = -1;
				N = numbercount - 1;   // just for multiplying bytes.I find numbercount again when i need one to make it even
				fclose(fp);
				return arr;		
			}
		}
		while(buffer[i] != ',');
		*(arr + numbercount - 1) = strtol(buffer,NULL,10);
	}
}


list *read_linkedlist(char *filename){
 	FILE *fp = fopen(filename,"r");
 	list *node = (list*)malloc(sizeof(list));
 	list *iter = node;
 	int i = -1,num;
 	char buffer[10];
 	memset(buffer,'\0',sizeof(buffer));

 	do{				// taking first number and declaring next pointer to NULL for adding other nodes easily
 		i++;
 		buffer[i] = fgetc(fp);
 	}
 	while(buffer[i] != ',');
 	buffer[i] = '\0';
 	node->num = strtol(buffer,'\0',10);
 	node->next = NULL;

 	while(1){
 		memset(buffer,'\0',sizeof(buffer));
 		i = -1;
 		do{
 			i++;
 			buffer[i] = fgetc(fp);
 			if(feof(fp)){
 				fclose(fp);
 				return node;
 			}
 		}
 		while(buffer[i] != ',');
 		buffer[i] = '\0';
 		num = strtol(buffer,'\0',10);

 		iter->next = (list*)malloc(sizeof(list));  // instead of using function to add node, i used this way to improve speed
 		iter->next->num = num;
 		iter->next->next = NULL;
 		iter = iter->next;
 	}
 	return node;
}

float * stats_array(int *arr){
	int i = 0,numbercount = 0;
	float min,max,std = 0,mean;
	float *result = (float*)malloc(4 * sizeof(float));
	double sum = 0,meanbuffer;
	min = max = arr[0];
	while(arr[i] != -1){
		numbercount++;
		if(max < arr[i]) max = arr[i];
		else if(min > arr[i]) min = arr[i];
		sum += arr[i];
		i++;
	}

	meanbuffer = sum/numbercount;
	sum = 0;
	i = 0;
	mean = meanbuffer;		// when i take mean as float it changes around 0.8. So i use double type buffer
	while(arr[i] != -1){
		sum += (arr[i] - mean) * (arr[i] - mean) / numbercount;
		i++;
	}
	std = sqrt(sum);
	result[0] = min;
	result[1] = max;
	result[2] = mean;
	result[3] = std;
	return result;
}


float * stats_linkedlist(list *node){
	int numbercount = 0;
	float min,max,std = 0,mean;
	float *arr = (float*)malloc(4 * sizeof(float));
	double sum = 0,meanbuffer;
	list *iter = node;
	min = max = iter->num;

	while(iter->next != NULL){
		numbercount++;
		if(max < iter->num) max = iter->num;
		else if(min > iter->num) min = iter->num;
		sum += iter->num;
		iter = iter->next;
	}
	sum+=iter->num;		// even "next" is NULL "num" is not. So i take num and increment numbercount
	numbercount++;

	meanbuffer = sum/numbercount;
	iter = node;
	sum = 0;
	mean = meanbuffer;		// when i take mean as float it changes around 0.8. So i use double type buffer
	while(iter->next != NULL){
		sum += ((iter->num) - mean) * ((iter->num) - mean) / numbercount;
		iter = iter->next;
	}
	std = sqrt(sum);
	*arr = min;
	*(arr + 1) = max;
	*(arr + 2) = mean;
	*(arr + 3) = std;
	return arr;
}


list * add_node(list* iter,int num){

	while(iter->next != NULL) iter = iter->next;
	iter->next = (list*)malloc(sizeof(list));
	iter->next->next = NULL;
	iter->next->num = num;
	return iter;
}

result *generate_numbers(int *arr,list *node){
	int i = 0,j = 0;
	result *final = (result*)malloc(sizeof(result));
	while(node->next != NULL){
		if(node->num != arr[i]){
			j++;
			final = (result*)realloc(final,j * sizeof(result));
			final[j - 1].n1 = node->num;
			final[j - 1].n2 = arr[i];
		}
		i++;
		node = node->next;
	}
	return final;
}

int find_duplicates(int i,int arr[]){
	int j;
	for(j = 0;j < i;j++){
		if(arr[j] == arr[i]) return 0;
	}
	return 1;
}