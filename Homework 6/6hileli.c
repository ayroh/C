#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_direction();
int find_length(char arr[]);
char find_place(char arr[]);
int find_if_empty(int length,int direction,char place[]);
int place_word(int length,int direction,char word[],char start[]);
int control_answer(char placeans[],char wordans[],int length,int *count);

/*															1 = up 			 (^) 						a = 1		i or I = 9		q = 17
															2 = top-right 	 (^>)						b = 2		j = 10			r = 18
															3 = right 		 (>)						c = 3		k = 11			s = 19
															4 = bottom-right (v>)						d = 4		l = 12			t = 20
															5 = bottom		 (v)						e = 5		m = 13
															6 = bottom-left  (<v)						f = 6		n = 14
															7 = left 		 (<)						g = 7		o = 15
															8 = top-left   	 (<^)						h = 8		p = 16				*/

char puzzle[20][20];

int main() {

	char point,str[15],words[10][15],place[3],placeans[3],wordans[15];
	int j,i,b=123,character,a,k = 0,cot = 0,start,direction,length,answercount = 0,indicator,wordcount = 0,answer,dircontrol = 0;
	srand(time(NULL));
	FILE *fp;

	for(i =0; i<20; i++) { 		// this declarement is because i want to know if that point of array is empty
		for(j= 0; j<20; j++) {
			puzzle[i][j] = '.';
		}
	}

	fp = fopen("words.txt","r");
	if(fp == NULL) {
		printf("patates\n");
	}

	for(i = 0; i < 10; i++){
		AndAnotherOne:
		a = 1 + rand()%100;
		for(j = 1; j < a; j++) {
			fgets(str,15,fp);
		}
		fgets(words[i],15,fp);
		
		if(a == 100){
		 		words[i][4] = 10;
				words[i][5] = '\0';   // At the end of file 'bait' word doesn't have '\n' char at the end of it.So i give it.
		}
		
		for(j = i-1;j > -1;j--){		  // Controling if that word is already in the game.
			if(strstr(words[j],words[i]) != NULL){
				goto AndAnotherOne;	
			}
		}
		fseek(fp,0,SEEK_SET);
	}
		i = 0;
		while(wordcount != 10){
			
			length = find_length(words[i]) - 1;
			direction = find_direction();
			find_place(place);   			// place[0] contains row - place[1] contains column and if column has 2 digits place[2] contains second digit
				AnotherOne:
			indicator = find_if_empty(length,direction,place);
				if(indicator == 0){
					direction = (direction + 1)%8;
					if(direction == 0){
						direction = 8;
					}
					if(dircontrol != 7){
						dircontrol++;
						goto AnotherOne;
					}
				}
				else if(indicator == 1){
					dircontrol = 0;
					wordcount++;
						place_word(length,direction,words[i],place);
					memset(place,0,3);   // The way i control if column place has 2 digits is controling " place[2] == '\0' " so i need to clear it before getting a new word 
					i++;
				}
		}
	AndAndAnotherOne:
	printf("\n\n    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20\n");
	printf("    ___________________________________________________________\n");
	for(i =0; i<20; i++) { 	//	printing last
	character = 97 + i;
	printf("%c  |",character);
		for(j= 0; j<20; j++) {
			
			if(puzzle[i][j] == '.'){
				printf(".  ");
			/*	a = 1 + 96 + rand()%26;
				printf("%c  ",a);*/
			}
			else{
				printf("%c  ",puzzle[i][j]);
			}
			
		}
		if(i%2 == 1){
		printf("                      %d.word: %s",k+1,words[k]);
		k++;
		}
		else{
			printf("\n");
		}
	}
	k = 0;
	printf("\nPlease enter coordinate and word with one space character between them(a1 word):\n");
	scanf("%s%s",placeans,wordans);
	if(strstr(placeans,"exit") != NULL 	|| strstr(placeans,"EXIT") != NULL || strstr(wordans,"exit") != NULL || strstr(wordans,"EXIT") != NULL){
		fclose(fp);
		return;
	}
	length = find_length(wordans);
	answer = control_answer(placeans,wordans,length,&answercount);
	if(answer != 0){
		for(i = 0;i < 10;i++){
			if(strstr(words[i],wordans) != NULL){
				for(j = 0;j < length;j++){
				words[i][j] = toupper(words[i][j]);
				}
				place_word(length,answer,words[i],placeans);
				break;
			}
		}
	}
	else if(answer == 0){
		printf("\nSorry mate...Try again.\n");
	}
			if(answercount == 10){
				printf("\nCongratulations!You finished the game bruh.\nPress anything to close the game.\n");
				getchar(); // For clearing buffer from last scanf i use getchar() twice
				getchar();
				fclose(fp);
				return;
			}
			goto AndAndAnotherOne;
		










	fclose(fp);
}

int find_direction() {
	int a;
	a = 1 + rand()%8;
	return a;
}


int find_length(char arr[]) {
	int i,len = 0;
	for(i = 0; arr[i] != '\0'; i++) {
		len++;
	}
	return len;
}

char find_place(char arr[]){
	int i,a;
	a = 1 + 96 + rand()%20; // finding row between a to t as char
	arr[0] = a;
	
	a = 1 + rand()%20;		// finding column between 1 to 20 as char
	if(a > 9){
		if(a == 20){
			arr[1] = '2';
			arr[2] = '0';
			return;
		}
		arr[1] = '1';
		a = a%10 + 48;
		arr[2] = a;
	}
	else{
		arr[1] = a + 48;
	}
}

int find_if_empty(int length,int direction,char place[]){
	int i = 0,j = 0,num1,num2,column,row;
	if(place[2] != '\0'){
		num1 = 10 * (place[1] - 48);
		num2 = place[2] - 48;
		column = num1 + num2 - 1;
	}
	else{
		column = place[1] - 49;
	}
	row = place[0] - 97;
	
	switch(direction){
		case 1:
			if((row - length) < 0){
				return 0;
			}
				
			for(i = row;i > (row - length);i--){
				if(puzzle[i][column] != '.'){
					return 0;
				}
			}
		break;
		case 2:
			i = row;
			j = column;
			
			if((row - length) < 0 || (column + length) > 20){
				return 0;
			}
			
			while(i > (row - length) && j < (column + length)){
					if(puzzle[i][j] != '.'){
						return 0;
					}
				i--;
				j++;
			}
		break;
		case 3:
			if((column + length) > 20){
				return 0;
			}
			
			for(j = column;j < (column + length);j++){
				if(puzzle[row][j] != '.'){
					return 0;
				}
			}
		break;
		case 4:
			i = row;
			j = column;
			
			if((row + length) > 20 || (column + length) > 20){
				return 0;
			}
			while(i < (row + length) && j < (column + length)){
				if(puzzle[i][j] != '.'){
					return 0;
				}
				i++;
				j++;
			}
		break;
		case 5:
			if((row + length) > 20){
				return 0;
			}
			for(i = row;i < (row + length);i++){
				if(puzzle[i][column] != '.'){
					return 0;
				}
			}
		break;
		case 6:
			i = row;
			j = column;
			if((row + length) > 20 || (column - length) < 0){
				return 0;
			}
			while(i < (row + length) && j > (column - length)){
				if(puzzle[i][j] != '.'){
					return 0;
				}
				i++;
				j--;
			}
		break;
		case 7:
			if((column - length) < 0){
				return 0;
			}
			for(j = column;j > (column - length);j--){
				if(puzzle[row][j] != '.'){
					return 0;
				}
			}
		break;
		case 8:
			i = row;
			j = column;
//			printf("%d - %d\n%d - %d \n",row,length,column,length);
			if((row - length) < 0 || (column - length) < 0){
				return 0;
			}
			while(i > (row - length) && j > (column - length)){
				if(puzzle[i][j] != '.'){
					return 0;
				}
				i--;
				j--;
			}
		break;
	}
	
return 1;
}


int place_word(int length,int direction,char word[],char start[]){
	
	int i = 0,j = 0,k = 0,num1,num2,column,row;
		if(start[2] != '\0') {
			num1 = 10 * (start[1] - 48);
			num2 = start[2] - 48;
			column = num1 + num2 - 1;
		} else {
			column = start[1] - 49;
		}
		row = start[0] - 97;
		
	switch(direction){
		case 1:
			for(i = row; i > (row - length); i--) {
				puzzle[i][column] = word[k];
				k++;
			}
		break;
		case 2:
			i = row;
			j = column;

			while(i > (row - length) && j < (column + length)) {
				puzzle[i][j] = word[k];
				i--;
				j++;
				k++;
			}
		break;
		case 3:
			for(j = column; j < (column + length); j++) {
				puzzle[row][j] = word[k];
				k++;
			}
		break;
		case 4:
			i = row;
			j = column;

			while(i < (row + length) && j < (column + length)) {
				puzzle[i][j] = word[k];
				i++;
				j++;
				k++;
			}
		break;
		case 5:
			for(i = row; i < (row + length); i++) {
				puzzle[i][column] = word[k];
				k++;
			}
		break;
		case 6:
			i = row;
			j = column;
			
			while(i < (row + length) && j > (column - length)) {
				puzzle[i][j] = word[k];
				i++;
				j--;
				k++;
			}
		break;
		case 7:
			for(j = column; j > (column - length); j--) {
				puzzle[row][j] = word[k];
				k++;
			}
		break;
		case 8:
			i = row;
			j = column;

			while(i > (row - length) && j > (column - length)) {
				puzzle[i][j] = word[k];
				i--;
				j--;
				k++;
			}
		break;
	}
	
}

int control_answer(char placeans[],char wordans[],int length,int *count){
	
	int i = 0,j = 0,k = 0,num1,num2,column,row;
		if(placeans[2] != '\0') {
			num1 = 10 * (placeans[1] - 48);
			num2 = placeans[2] - 48;
			column = num1 + num2 - 1;
		} 
		else {
			column = placeans[1] - 49;
		}
		row = placeans[0] - 97;
			
			k = 0;
			i = row;
			j = column;
			for(i = row; i > (row - length); i--) {
				if(puzzle[i][column] != wordans[k]){
					break;
				}
				k++;
			}
			if(k == length){
				*count += 1;
				return 1;
			}


			i = row;
			j = column;
			k = 0;
			while(i > (row - length) && j < (column + length)) {
				if(puzzle[i][j] != wordans[k]){
					break;
				}
				i--;
				j++;
				k++;
			}
			if(k == length){
				*count += 1;
				return 2;
			}
			
			
			i = row;
			j = column;
			k = 0;
			for(j = column; j < (column + length); j++) {
				if(puzzle[row][j] != wordans[k]){
					break;
				}
				k++;
			}
			if(k == length){
				*count += 1;
				return 3;
			}
			
			
			
			i = row;
			j = column;
			k = 0;
			while(i < (row + length) && j < (column + length)) {
				if(puzzle[i][j] != wordans[k]){
					break;
				}
				i++;
				j++;
				k++;
			}
			if(k == length){
				*count += 1;
				return 4;
			}
			
			

			i = row;
			j = column;
			k = 0;
			for(i = row; i < (row + length); i++) {
				if(puzzle[i][column] != wordans[k]){
					break;
				}
				k++;
			}
			if(k == length){
				*count += 1;
				return 5;
			}


			i = row;
			j = column;
			k = 0;
			while(i < (row + length) && j > (column - length)) {
				if(puzzle[i][j] != wordans[k]){
					break;
				}
				i++;
				j--;
				k++;
			}
			if(k == length){
				*count += 1;
				return 6;
			}
			

			i = row;
			j = column;
			k = 0;
			for(j = column; j > (column - length); j--) {
				if(puzzle[row][j] != wordans[k]){
					break;
				}
				k++;
			}
			if(k == length){
				*count += 1;
				return 7;
			}

			i = row;
			j = column;
			k = 0;
			while(i > (row - length) && j > (column - length)) {
				if(puzzle[i][j] != wordans[k]){
					break;
				}
				i--;
				j--;
				k++;
			}
			if(k == length){
				*count += 1;
				return 8;
			}
	return 0;
}












