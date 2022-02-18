#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_genres(char genres[],int genrecount[]);
void find_platforms(char platforms[],int platformcount[]);
void find_numbers(float dig[],char namebuffer[]);
float find_scores();
int find_gandp(float gandp[],char namebuffer[],char genre[],char platform[]);
void years(int year,int untorsin);
float strtoflo(char name[],char arr[]);
void flotostr(float number,char arr[]);
int find_popular(char namebuffer[]);


int main(){
	int i,j,choice,year,untorsin,pop,genrecount[12] = {0,0,0,0,0,0,0,0,0,0},platformcount[10] = {0,0,0,0,0,0,0,0,0};
	char name[100],genre[100],platform[50],namebuffer[100];
	float single[2][5],ave_score;
	
	find_genres(genre,genrecount);           // finding genre + count , platform + count and average_score at first so i just print it when user wants
	find_platforms(platform,platformcount);
	ave_score = find_scores();				 
	
	
	AnotherOne:
	printf("\n\n0: List of the Genres\n1: List of the Platforms\n2: List of the Games Through the Years\n3: All Informations of a Single Game\n4: Average of the User Scores\n");
	printf("5: Georographical Information of a Single Game\n6: Frequence of the Genres\n7: Frequence of the Platforms\n8: Exit\n\nPlease select an operation:\n");
	scanf("%d",&choice);
	switch(choice){
		case 0:
			printf("\n%s\n",genre);	
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;		
		case 1:
			printf("\n%s\n",platform);
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 2:
			printf("Enter a year: \n");
			scanf("%d",&year);
			printf("Until (0) or Since (1) %d?:\n",year);
			scanf("%d",&untorsin);
			years(year,untorsin);
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 3:
			memset(namebuffer,0,100);
			printf("\nPlease enter the name of the game:\n");
			wrongname:
			scanf("%s",namebuffer);
			pop = find_gandp(single[0],namebuffer,genre,platform);
			if(pop == 0){
				printf("Please enter a proper name:\n");
				goto wrongname;
			}
			find_numbers(single[1],namebuffer);
			printf("\nName:                        %s",namebuffer);
			printf("\nGenre:                       ");
			flotostr(single[0][0],genre);
			printf("\nPlatform:                    ");
			flotostr(single[0][1],platform);
			printf("\nYear                         %.0f",single[1][0]);
			printf("\nSales In NA:                 %.2f",single[1][1]);
			printf("\nSales In EU:                 %.2f",single[1][2]);
			if(single[1][3] == 0){
			printf("\nTotal Sales:                 Not Available");
			}
			else{
			printf("\nTotal Sales:                 %.2f",single[1][3]);
		}
			printf("\nUser Score:                  %.2f\n",single[1][4]);
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 4:
			printf("\nAverage: %f",ave_score);
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 5:
			memset(namebuffer,0,100);
			printf("\nPlease enter the name of the game:\n");
			wronggame:
			scanf("%s",namebuffer);
			pop = find_popular(namebuffer);
			if(pop == 0){
				printf("Please enter a proper name:\n");
				goto wronggame;
			}
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 6:
			i = 0;
			j = 0;
			while(platform[i] != 0){
				while(platform[i] != '\n'){
					printf("%c",platform[i]);
					i++;
				}
				i++;
				printf("                 %d\n",platformcount[j]);
				j++;
			}
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 7:
			i = 0;
			j = 0;
			while(genre[i] != 0){
				while(genre[i] != '\n'){
					printf("%c",genre[i]);
					i++;
				}
				i++;
				printf("                 %d\n",genrecount[j]);
				j++;
			}
			printf("\nEnter any character to get back to the menu.\n");
			getchar();
			getchar();
			goto AnotherOne;
		case 8:
		break;
		default:
			printf("\nTRY AGAIN");
			goto AnotherOne;
	}
}



void find_genres(char genres[],int genrecount[]){
	memset(genres,0,100); // when i take char as a parameter it fills it with some nonsense chars so i clear it
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	
	char row[200],genrebuffer[20]; 
	int i = 0,k = 0,j = 0,numbuff = 0;
	fscanf(fp,"%s",row);     // i jump first row
	for(j = 0;j < 2000;j++){
	fscanf(fp,"%s",row);     // genres are at second word so i jump first word at every row
		while(row[i] != ','){
			i++;
		}
		i++;
		while(row[i] != ','){
		genrebuffer[k] = row[i];
		k++;
		i++;
	}
	genrebuffer[k] = 0;
	if(strstr(genres,genrebuffer) == NULL){    // controling that if that word is already at genres
		strcat(genres,genrebuffer);
		strcat(genres,"\n");
	}
	numbuff = strtoflo(genrebuffer,genres);    // counting words
	
	if(numbuff == 1){
		genrecount[0] += 1;
	}
	else if(numbuff == 2){
		genrecount[1] += 1;
	}
	else if(numbuff == 3){
		genrecount[2] += 1;
	}
	else if(numbuff == 4){
		genrecount[3] += 1;
	}
	else if(numbuff == 5){
		genrecount[4] += 1;
	}
	else if(numbuff == 6){
		genrecount[5] += 1;
	}
	else if(numbuff == 7){
		genrecount[6] += 1;
	}
	else if(numbuff == 8){
		genrecount[7] += 1;
	}
	else if(numbuff == 9){
		genrecount[8] += 1;
	}
	else if(numbuff == 10){
		genrecount[9] += 1;
	}
	else if(numbuff == 11){
		genrecount[10] += 1;
	}
	else if(numbuff == 12){
		genrecount[11] += 1;
	}
	memset(genrebuffer,0,20); // clearing buffer
	i = 0;
	k = 0;
	}
	fclose(fp);	
}




void find_platforms(char platforms[],int platformcount[]){
	memset(platforms,0,50);		// when i take char as a parameter it fills it with some nonsense chars so i clear it
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	
	char row[200],platformbuffer[20];
	int i = 0,k = 0,l = 0,j = 0,numbuff = 0;

	fscanf(fp,"%s",row); 		// i jump first row
	for(j = 0;j < 2001;j++){
	fscanf(fp,"%s",row);
	for(l = 0;l < 2;l++){  		// platforms are at third word so i jump first 2 word at every row
		while(row[i] != ','){
			i++;
		}
		i++;
	}	
		while(row[i] != ','){
		platformbuffer[k] = row[i];
		k++;
		i++;
	}
	platformbuffer[k] = 0;
	if(strstr(platforms,platformbuffer) == NULL){  // controling that if that word is already at platforms
		strcat(platforms,platformbuffer);
		strcat(platforms,"\n");
	}
	
	numbuff = strtoflo(platformbuffer,platforms);  // counting words
	if(numbuff == 1){
		platformcount[0] += 1;
	}
	else if(numbuff == 2){
		platformcount[1] += 1;
	}
	else if(numbuff == 3){
		platformcount[2] += 1;
	}
	else if(numbuff == 4){
		platformcount[3] += 1;
	}
	else if(numbuff == 5){
		platformcount[4] += 1;
	}
	else if(numbuff == 6){
		platformcount[5] += 1;
	}
	else if(numbuff == 7){
		platformcount[6] += 1;
	}
	else if(numbuff == 8){
		platformcount[7] += 1;
	}
	else if(numbuff == 9){
		platformcount[8] += 1;
	}
	else if(numbuff == 10){
		platformcount[9] += 1;
	}
	
	memset(platformbuffer,0,20); // clearing buffer
	i = 0;
	k = 0;
	}
	fclose(fp);	
}




void years(int year,int untorsin){
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	char namebuffer[100],row[200],yearbuffer[5],a;
	int i = 0,k = 0,j = 0,yearnumber = 0,l,b;
	
	fscanf(fp,"%s",row);			 // i jump first row
		if(untorsin == 0){			// until
		if(year < 1986){
			printf("Please enter a number that higher than 1986!\n");
			fclose(fp);
			return;
		}
			while(!feof(fp)){
			memset(namebuffer,0,100);
			memset(yearbuffer,0,5);
			memset(row,0,200);
			i = 0;
			k = 0;
			j = 0;
			
			fscanf(fp,"%s",row);
			
			for(l = 0;l < 3;l++){  // years are at fourth word so i jump first 3 word at every row
				while(row[i] != ','){
				i++;
				}
			i++;
			}		
			while(row[i] != ','){
				yearbuffer[k] = row[i];
				k++;
				i++;
			}
			yearnumber = atoi(yearbuffer);
			
			if(year <= yearnumber){
				break;
			}
			
			while(row[j] != ','){
				namebuffer[j] = row[j];
				j++;
			}
			
			printf("%s\n",namebuffer);
			
		}
	}
		else if(untorsin == 1){
			if(year > 2005){
				printf("Please enter a number that lower than 2006!\n");
				fclose(fp);
				return;
			}
		memset(row,0,200);
			while(year > yearnumber){
			fscanf(fp,"%s",row);
			memset(yearbuffer,0,5);
				i = 0;
				k = 0;
				for(l = 0;l < 3;l++){  // years are at fourth word so i jump first 3 word at every row
				while(row[i] != ','){
				i++;
				}
			i++;
			}
			while(row[i] != ','){
				yearbuffer[k] = row[i];
				k++;
				i++;
			}
			yearnumber = atoi(yearbuffer);
			memset(row,0,200);
			}
			fseek(fp,-20,SEEK_CUR);
			while(a != '\n'){
				fscanf(fp,"%c",&a);
				fseek(fp,-2,SEEK_CUR);
			}
			fseek(fp,2,SEEK_CUR);

			while(!feof(fp)){
			memset(namebuffer,0,100);
			memset(row,0,200);
			j = 0;	
				
			fscanf(fp,"%s",row);
			
			while(row[j] != ','){
				namebuffer[j] = row[j];
				j++;
			}
			
			printf("%s\n",namebuffer);
				
			}
		}
	fclose(fp);
}


void find_numbers(float dig[],char namebuffer[]){
	char row[200],numbuffer[10];
	int i = 0,k = 0,j = 0,yearnumber = 0,l;
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	for(i = 0;i < 2001;i++){
		fscanf(fp,"%s",row);
		if(strstr(row,namebuffer) != NULL){
			break;
		}
		memset(row,0,200);
	}
	for(i = 0;i < 3;i++){
	while(row[j] != ','){ // name
		j++;
	}
	j++;
}
	
	
	memset(numbuffer,0,10);
	while(row[j] != ','){ // year
		numbuffer[k] = row[j];
		k++;
		j++;
	}
	j++;
	dig[0] = atof(numbuffer);
	memset(numbuffer,0,10);
	k = 0;
	
		while(row[j] != ','){// na_sales
		numbuffer[k] = row[j];
		k++;
		j++;
	}
	j++;
	dig[1] = atof(numbuffer);
	memset(numbuffer,0,10);
	k = 0;
		while(row[j] != ','){// eu_sales 
		numbuffer[k] = row[j];
		k++;
		j++;
	}
	j++;
	dig[2] = atof(numbuffer);
	memset(numbuffer,0,10);
	k = 0;
		while(row[j] != ','){//global sales
		numbuffer[k] = row[j];
		k++;
		j++;
	}
	if(numbuffer[0] == 'n'){
		dig[3] = 0;
	}
	else{
		dig[3] = atof(numbuffer);
	}
	j++;
	memset(numbuffer,0,10);
	k = 0;
		while(row[j] != 0){ // user scores
		numbuffer[k] = row[j];
		k++;
		j++;
	}
	dig[4] = atof(numbuffer);
}


int find_gandp(float gandp[],char namebuffer[],char genre[],char platform[]){
	char buffer[20],row[200],numbuffer[10];
	int i = 0,k = 0,j = 0,yearnumber = 0,l;
	float asd;
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}

	for(i = 0;i < 2001;i++){
		fscanf(fp,"%s",row);
		if(strstr(row,namebuffer) != NULL){
			break;
		}
		memset(row,0,200);
	}
	if(i == 2001){
		return 0;
	}
	i = 0;
	while(row[i] != ','){
		namebuffer[i] = row[i];
		i++;
	}
	while(row[j] != ','){ // name
		j++;
	}
	j++;
	while(row[j] != ','){ // genre
		buffer[k] = row[j];
		k++;
		j++;
	}
	buffer[k] = 0;
	j++;
	gandp[0] = strtoflo(buffer,genre);
	memset(buffer,0,20);
	k = 0;
	while(row[j] != ','){ // platform
		buffer[k] = row[j];
		k++;
		j++;
	}
	buffer[k] = 0;
	j++;
	gandp[1] = strtoflo(buffer,platform);
	
	fclose(fp);
	return 1;
}



float strtoflo(char name[],char arr[]){
	float count = 0;
	int i = 0,j = 0;
	char buffer[20],k,*control;
	while(1){
		memset(buffer,0,20);
		i = 0;
	while(arr[j] != '\n'){
		buffer[i] = arr[j];
		i++;
		j++;
	}
	j++;
	count++;
		if(strstr(name,buffer) != NULL){
			control = strstr(name,buffer);
			if(strcmp(control,buffer) == 0){ // if i don't use strcmp , strstr find ps first and use it.So i can't count psp
			return count;
			}
		}
	}
}

void flotostr(float number,char arr[]){
	int count = 0;
	int i = 0,j = 0;
	char buffer[20];
	
	while(number > count){
		memset(buffer,0,20);
		i = 0;
	while(arr[j] != '\n'){
		buffer[i] = arr[j];
		i++;
		j++;
	}
	count++;
	j++;
	}
	printf("%s",buffer);	
}



float find_scores(){
	int i = 0,k = 0,l = 0,count = 0;
	float score = 0,scoresum = 0;
	char scorebuffer[20],row[200];
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	fscanf(fp,"%s",row);
	while(!feof(fp)){
			count++;
			memset(scorebuffer,0,20);
			memset(row,0,200);
			i = 0;
			k = 0;
			
			fscanf(fp,"%s",row);
			
			for(l = 0;l < 7;l++){  // score are at eighth word so i jump first 7 word at every row
				while(row[i] != ','){
				i++;
				}
			i++;
			}
			
			while(row[i] != 0){
				scorebuffer[k] = row[i];
				k++;
				i++;
			}
			scorebuffer[k] = 0;
			score = atof(scorebuffer);
			scoresum += score;
		}
		scoresum /= count;
	fclose(fp);
	return scoresum;
}


int find_popular(char namebuffer[]){
	char row[200],salebuffer[10];
	int i,k = 0,l;
	float eu,na;
	FILE *fp;
	fp = fopen("Video_Games.txt","r");
	if(fp == NULL){
		printf("patates");
	}
	fscanf(fp,"%s",row);
	for(i = 0;i < 2001;i++){
		fscanf(fp,"%s",row);
		if(strstr(row,namebuffer) != NULL){
			break;
		}
		memset(row,0,200);
	}
	if(i == 2001){
		return 0;
	}
	i = 0;
	while(row[i] != ','){
		namebuffer[i] = row[i];
		i++;
	}
			memset(salebuffer,0,10);
			i = 0;
			
			for(l = 0;l < 4;l++){  // sales starts at fifth word so i jump first 4 word at every row
				while(row[i] != ','){
				i++;
				}
			i++;
			}
			while(row[i] != ','){
				salebuffer[k] = row[i];
				k++;
				i++;
			}
			salebuffer[k] = 0;
			na = atof(salebuffer);
			memset(salebuffer,0,10);
			k = 0;
			i++;
			while(row[i] != ','){
				salebuffer[k] = row[i];
				k++;
				i++;
			}
			salebuffer[k] = 0;
			eu = atof(salebuffer);
			if(eu > na){
				printf("\n%s was more popular in Europe.\n",namebuffer);
			}
			else if(na > eu){
				printf("\n%s was more popular in North America.\n",namebuffer);
			}
			else{
				printf("\n%s's sales are equal in both Europe and North America.\n",namebuffer);
			}
	fclose(fp);
	return 1;
}




