#include <stdio.h>
#include <math.h>

void decrypt_and_print(char * file_path);
char decrypt_numbers(int number);
void deep_decrypt_and_print (char* file_path);
void track_machine();
void refresh_position(int* X, int* Y, double* D, double* R);
void encrypt_messages(char* message);
void menu();
void decrypt_part4(char* message);
char encrypt_symbols(char character);

void main(){
	menu();
}

void menu(){
	int choice;
	AnotherOne: /* For menu loop */
	printf("\n\n1-) Decrypt and print encrypted_p1.img\n2-) Decrypt and printf encrypted_p2.img\n3-) Switch on the tracking machine\n4-) Encrypt the message\n5-) Switch off\n6-) Decrypt Part 4(For Control)\n\nPlease make your choice:");
	scanf("%d",&choice);
	switch(choice){
	case 1:
	decrypt_and_print ("encrypted_p1.img");
	goto AnotherOne;
	break;
	case 2:
	deep_decrypt_and_print("encrypted_p2.img");
	goto AnotherOne;
	break;
	case 3:
	track_machine();
	goto AnotherOne;
	break;
	case 4:
	encrypt_messages("decrypted_p4.img");
	goto AnotherOne;
	break;
	case 5:break;
	case 6:
	decrypt_part4("encrypted_p4.img");
	goto AnotherOne;
	break;
	}

}


void decrypt_and_print(char * file_path) {
		FILE *fp;
		int num;
		char character;
		fp = fopen(file_path,"r+");
		if(fp == NULL){
			printf("File couldn't opened.\n");
			return;
		}
		while(!feof(fp)){
 		fscanf(fp, "%c",&character);
 		num = character - 48; /* From ASCII to integer */
 		character = decrypt_numbers(num);
		printf("%c", character);
}
fclose(fp);
}


char decrypt_numbers(int number) {

	switch (number) {
	case 0:return ' ';
	case 1:return '-';
	case 2:return '_';
	case 3:return '|';
	case 4:return '/';
	case 5:return '\\';
	case 6:return 'O';
	default:printf("\n");return 0;
	}
}


void deep_decrypt_and_print (char *file_path){
	FILE *fp;
	fp = fopen(file_path,"r+");
	if(fp == NULL){
		printf("File couldn't opened.\n");
		return;
	}
	int num,sum,i,count=-1;
	char character;
	while(!feof(fp)){
		sum = 0;
	fseek(fp,count,SEEK_SET); /* With count we can keep track of our function beginning */
	for(i=0 ; i<3 ; i++){
	fscanf(fp,"%c",&character);
	if(character == '\n'){ /* "\n" means we reach the end of line so we need to fast forward count */
		printf("\n");
		count+=2;
		break;
	}
	sum = sum + character - 48;	/* ASCII to integer */
}
	sum = sum%7;
	character = decrypt_numbers(sum);
	printf("%c",character);
	count++;
}
fclose(fp);
}



void track_machine() {
	int i,j,*X,*Y,px,py,die = 0;
	double *D,*R,pd,pr;
	char choice = 'r';
	X = &px;  /* Adding addresses to pointers */
	Y = &py;
	D = &pd;
	R = &pr;
	*X = 1; /* Starting point */
	*Y = 1;
	*D = 0;
	*R = 7.07; /* For first view i calculated Distance to out camp */
	while(choice == 'r'){
		die = 0;
	for(i=11;i>0;i--){ 		/* x axis */
		for(j=1;j<12;j++){  /* y axis */
			if(*X==j && *Y==i){
				printf("E	");
				if(j == 6 && i == 6){ /* if enemies at our base */
					die++;
				}
			}
			else if(i==6 && j==6){
				printf("O	");
			}
			else{
				printf(".	");
			}
		}
	printf("\n");
	}
	if(die == 1){   /* if enemies at our base */
		printf("Seems like you already died...Press anything to try again.\n");
		getche();
		getche();
		printf("\nJust kidding.It is not a game.\n");
		return;
	}
	printf("Enemies X position is: %d, Y position: %d, Displacement: %0.2lf, Distance to our camp: %0.2lf\nCommand Waiting...:\n\n\n",*X,*Y,*D,*R);
	scanf(" %c",&choice);
	if(choice == 'e'){
		break;
}
	refresh_position(X,Y,D,R);
}
}

void refresh_position(int* X, int* Y, double* D, double* R) {
	int oldX = *X,oldY = *Y;
	srand(time(NULL));
	*X = 1 + rand()%11; /* having random numbers between 0 and 11 */
	*Y = 1 + rand()%11;
	*D = ((*X-oldX)*(*X-oldX))+((*Y-oldY)*(*Y-oldY));
	*D = sqrt(*D);
	*R = ((6-*X)*(6-*X))+((6-*Y)*(6-*Y));
	*R = sqrt(*R);
}


void encrypt_messages(char* message) {
FILE *akt,*dec;
	int sum,num=0,i,new1=0,curcont1,curcont2;
	char character,basechar;
	
	dec = fopen(message,"r+");
	akt = fopen("encrypted_p4.img","w+");
	
	fseek(dec,-2,SEEK_END); /* For some reason cursor doesn't reach the end of file and i find out cursor ends from second to last.So i control every time before it reaches to that point. */
	curcont1 = ftell(dec);
	fseek(dec,0,SEEK_SET);
	fprintf(akt,"000");
		while(curcont1 != curcont2){
			sum = 0;

			fscanf(dec,"%c",&basechar);
			
			while(basechar == '\n'){
				fscanf(dec,"%c",&basechar);
				
				if(basechar != '\n'){  
				fprintf(akt,"\n00");
				
			}
			}
			basechar = encrypt_symbols(basechar);
			num = basechar - 48;    /* ASCII to integer */
			fseek(akt,-2,SEEK_CUR);
			
				for(i = 0;i < 2;i++){
					fscanf(akt,"%c",&character);
					while(character == '\n'){     /* "\n" means we reach the end of line so we need to fast forward count */
					fscanf(akt,"%c",&character);
					}
					sum = sum + character - 48;
				}
			new1 = num - sum;
	while(new1 < 0){
				new1+=7;
		}
			new1 = new1 + '0';
			fseek(akt,0,SEEK_CUR);	/* I don't know why but without this code function doesn't run */
			fprintf(akt,"%c",new1);
			curcont2 = ftell(dec);
	}
	printf("\nEncryption is succesfull.\n");
		fclose(dec);
		fclose(akt);
}


char encrypt_symbols(char character){
	switch(character){
	case ' ':return '0';
	case '-':return '1';
	case '_':return '2';
	case '|':return '3';
	case '/':return '4';
	case '\\':return '5';
	case 'O':return '6';
}
}

void decrypt_part4(char* message){
	int i,sum;
	char character;
	FILE *fp;
 	fp = fopen(message,"r+");
 	if(fp == NULL){
 		printf("patates");
	 }
 while(1){
 	
 	fseek(fp,4,SEEK_CUR);
 	sum = 0;
 for(i = 0;i < 3;i++){
 	
	fscanf(fp,"%c",&character);

	while(character == '\n'){
		printf("\n");
		fscanf(fp,"%c",&character);
			if(character != '\n'){
			fseek(fp,2,SEEK_CUR);
			fscanf(fp,"%c",&character);
		}
	}
	fseek(fp,-2,SEEK_CUR);
	sum = sum + character - 48;
}
	sum %= 7;
	character = decrypt_numbers(sum);
	if(character != 0){
 	printf("%c",character);
}
	else{
	fclose(fp);
	break;	
}
}
}


