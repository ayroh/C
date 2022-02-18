#include <stdio.h>
#include <string.h>

void menu();
void read_news(char buffer[500], char file_path[10], int is_Only_Title);
void append_file(char* file_path, char c);
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x), int a);


void main(){
	menu();
}

void menu(){
	char cnt1 = '0',cnt2 = '0',cnt3 = '0',cnt4 = '0',filerecord,choice1,choice2,choice3,choice4,choice5,choice6,forseek,buffer[500],file_path[10];
	int i,cntsharp = 0;

	FILE *frecord; 	                                    /* This way i can take record of what user reads with file */
	if(fopen("readed_news_id.txt","r+") == NULL){                 /* "readed_news_id.txt" comes with written "2" in it.So 'b' choice automatically prints that 2 is readed.Please remove it before code starts */
	frecord = fopen("readed_news_id.txt","w+");               /* w+ mode will overwrite the file so i need to create it just for once so r+ for next times */
	fclose(frecord);
	}

	AnotherOne:

printf("************DAILY PRESS**************\n\nToday's news are listed for you : \n\n");
printf("Title of 1. news:");
read_news(buffer,"news/1.txt",1);

printf("Title of 2. news:");
read_news(buffer,"news/2.txt",1);

printf("Title of 3. news:");
read_news(buffer,"news/3.txt",1);

printf("Title of 4. news:");
read_news(buffer,"news/4.txt",1);

printf("\n\nWhat do you wanna do?\na.Read a new\nb.List the readed news\nc.Get decrypted information from the news\n");
scanf(" %c",&choice1);
switch(choice1){
	case 'a':
		printf("\nWhich new text you want to read?\n");
		scanf(" %c",&choice2);
		switch(choice2){
		case '1':
		frecord = fopen("readed_news_id.txt","r+");
		while(!feof(frecord)){ /* This way i can record if user already read it */
			fscanf(frecord,"%c",&forseek);
			if(forseek == '1'){
				printf("This new is readed.Do you want to read again? Yes(1) / No(0):\n");
				scanf(" %c",&choice4);
				if(choice4 == '1'){
				read_news(buffer,"news/1.txt",0);
				}
				cnt1 = '1';
				break;
			}
		}
		fclose(frecord);
		if(cnt1 != '1'){
				read_news(buffer,"news/1.txt",0);
				cnt1 = '1';
				append_file("readed_news_id.txt",cnt1);
				}
		break;

		case '2':
			
		frecord = fopen("readed_news_id.txt","r+");
		while(!feof(frecord)){ 
			fscanf(frecord,"%c",&forseek);
			if(forseek == '2'){
				printf("This new is readed.Do you want to read again? Yes(1) / No(0):\n");
				scanf(" %c",&choice4);
				if(choice4 == '1'){
				read_news(buffer,"news/2.txt",0);
				}
				cnt2 = '2';
				break;
			}
		}
		fclose(frecord);
		if(cnt2 != '2'){
				read_news(buffer,"news/2.txt",0);
				cnt2 = '2';
				append_file("readed_news_id.txt",cnt2);
				}
		break;


		case '3':
			frecord = fopen("readed_news_id.txt","r+");
		while(!feof(frecord)){ 
			fscanf(frecord,"%c",&forseek);
			if(forseek == '3'){
				printf("This new is readed.Do you want to read again? Yes(1) / No(0):\n");
				scanf(" %c",&choice4);
				if(choice4 == '1'){
				read_news(buffer,"news/3.txt",0);
				}
				cnt3 = '3';
				break;
			}
		}
		fclose(frecord);
		if(cnt3 != '3'){
				read_news(buffer,"news/3.txt",0);
				cnt3 = '3';
				append_file("readed_news_id.txt",cnt3);
				}
		break;



		case '4':
			frecord = fopen("readed_news_id.txt","r+");
		while(!feof(frecord)){ 
			fscanf(frecord,"%c",&forseek);
			if(forseek == '4'){
				printf("This new is readed.Do you want to read again? Yes(1) / No(0):\n");
				scanf(" %c",&choice4);
				if(choice4 == '1'){
				read_news(buffer,"news/4.txt",0);
				}
				cnt4 = '4';
				break;
			}
		}
		fclose(frecord);
		if(cnt4 != '4'){
				read_news(buffer,"news/4.txt",0);
				cnt4 = '4';
				append_file("readed_news_id.txt",cnt4);
				}
		break;



		default:
			printf("You chose wrong news\n");
		break;
		}
		printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice3);
		if(choice3 == 'y'){
			goto AnotherOne;
		}
		break;

	case 'b':
	frecord = fopen("readed_news_id.txt","r+");
	printf("Readed news are listed below:\n");
		
	while(!feof(frecord)){
		fscanf(frecord,"%c",&filerecord);
		
		if(filerecord == '1'){
			printf("1. new is readed\n");
		}
		else if(filerecord == '2'){
			printf("2. new is readed\n");
		}
		else if(filerecord == '3'){
			printf("3. new is readed\n");
		}
		else if(filerecord == '4'){
			printf("4. new is readed\n");
		}
		filerecord = '0';
	}
	fclose(frecord);
	
	printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice3);
		if(choice3 == 'y'){
			goto AnotherOne;
		}
	break;

	case 'c':
	printf("Which news would you like to decrypt? \n");
	scanf(" %c",&choice5);
	
	switch(choice5){
		case '1':
		read_magic_numbers("news/1.txt",buffer);

		printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice6);
		if(choice6 == 'y'){
			goto AnotherOne;
		}
		
		break;
		case '2': /* I don't know why but in windows this case gives an error that prints '#' continuously after it encounters '#'.But it runs in ubuntu */
		read_magic_numbers("news/2.txt",buffer);
		
		printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice6);
		if(choice6 == 'y'){
			goto AnotherOne;
		}

		break;
		case '3':
		read_magic_numbers("news/3.txt",buffer);
		
		printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice6);
		if(choice6 == 'y'){
			goto AnotherOne;
		}

		break;
		case '4':
		read_magic_numbers("news/4.txt",buffer);
		
		printf("\n\nDo you want to continue reading? Yes(y) / No(n):\n");
		scanf(" %c",&choice6);
		if(choice6 == 'y'){
			goto AnotherOne;
		}

		break;
	}
	break;
}
}




void read_news(char buffer[500], char file_path[10], int is_Only_Title){
	int i = 0;
	char character = '0';
	FILE *fp;
	fp = fopen(file_path,"r+");
	if(is_Only_Title == 1){
		while(character != '\n'){
		character = fgetc(fp);
		printf("%c",character);
		i++;
	}
	fclose(fp);
		return;
	}

	while(character != '\n'){
		character = fgetc(fp);
	}
	while(!feof(fp)){
		buffer[i] = fgetc(fp);
		printf("%c",buffer[i]);
		i++;
	}
	fclose(fp);
	return;
}

void read_magic_numbers(char buffer_magic[10], char buffer_news[500]){
	int i = 0,numMagic,sum = 0;

	FILE *fp;
	fp = fopen(buffer_magic,"r+");
	while(!feof(fp)){
		buffer_news[i] = fgetc(fp);
		if(buffer_news[i] == '#'){
		fscanf(fp,"%d",&numMagic);
		sum += g_func(f_func,numMagic);
		fseek(fp,-1,SEEK_CUR);		
		}
		printf("%c",buffer_news[i]);
		i++;
	}
	if( strstr(buffer_magic,"1") != 0 ){
	printf("\n\nNumber of people tested = %d\n",sum);
	}
	else if( strstr(buffer_magic,"2") != 0 ){
	printf("\n\nNumber of sick people = %d\n",sum);
	}
	else if( strstr(buffer_magic,"3") != 0 ){
	printf("\n\nNumber of deaths = %d\n",sum);
	}
	else if( strstr(buffer_magic,"4") != 0 ){
	printf("\n\nExpected number of sick people = %d\n",sum);
	}
}

void append_file(char * file_path, char c){
	FILE *fappend;
	fappend = fopen(file_path,"a+");
	fprintf(fappend,"%c",c);
	fclose(fappend);
	return;
}



double f_func(int x){
	double y;
	y = (x*x*x) - (x*x) + 2;
	return y;
}

double g_func(double f(int x), int a){
double x;
x = f(a);
x *= x;
return x;
}
