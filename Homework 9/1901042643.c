#include <stdio.h>

struct Hospital{
	char* name;
	char citiesServed[3];
};
	
struct card {
	const char *face;
	const char *suit;
};


int numPathsHome(int street, int avenue);
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4],char a[10]); // Instead of using global array variable i take as parameter
void shuffle_deck(char faces[13][10],char suits[4][10],struct card cards[52]);
int combinationUtil(int arr[], int data[], int start, int end, int index, int r,char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]);
 

void main(){
	
	int s,a,result,choice = 2,i;
	
	srand(time(NULL));
	char locations[4][3] = { {'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F'}, {'C', 'E', 'F'} };
	char cities[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };
	int numHospitals;
	struct Hospital results[4];
	int arr[] = {1, 2, 3, 4}; // because i have 4 locations
    int r,j,index =0; 
    int n = sizeof(arr)/sizeof(arr[0]); 
	int data[20];
	
	char faces[13][10] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	char suits[4][10] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	struct card cards[52];
	while(choice < 5 && choice > 0){
	printf("\nMake Your Choce:\nPart 1 (Stay Home Problem)\nPart 2 (COVID-19 Health Coverage)\nPart 3 (Shuffle the deck)\nPart 4 -> Exit\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("\nEnter the street number: ");
				scanf("%d",&s);
			printf("Enter the avenue number: ");
				scanf("%d",&a);
			printf("Number of optimal paths to take back home: %d\n",numPathsHome(s,a));
		break;
		case 2:
			
	printf("Enter the maximum number of hospital can be constructed: ");
	scanf("%d",&numHospitals);
    r = numHospitals;
    
    if(combinationUtil(arr, data, 0, n-1, 0, r,cities,locations,numHospitals,results) == 1){
    	for(i = 0;i < r;i++){
    		printf("Hospital - %c\nHospital locations: ",results[i].name);
    		for(j = 0;j < 3;j++){
    			printf("%c",results[i].citiesServed[j]);
			}
			printf("\n");
		}
	}
	else{
		printf("No,some cities are not covered.\n");
	}
		break;
		case 3:
			for(i = 0;i < 52;i++){
				cards[i].face = (struct card*) malloc(sizeof("Diamonds"));		// allocating memory as long as the longest word in the array
				cards[i].suit = (struct card*) malloc(sizeof("Three"));
			}
			shuffle_deck(faces,suits,cards);
			for(i = 0;i < 52;i+=2)	printf("%s of %s          %s of %s\n",cards[i].face,cards[i].suit,cards[i+1].face,cards[i+1].suit);
		break;
		case 4:choice = 10;break;
	}
}
}

int numPathsHome(int street,int avenue){ // Every time i see a crossroad i call function for both ways.When i see a wall i return 1 and sum them all
	if(street == 1 || avenue == 1)	return 1;
	else return numPathsHome(street - 1,avenue) + numPathsHome(street,avenue - 1);
}

int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4],char a[10]){
	char temp[30],temp2[6];
	memset(temp2,0,6); // clearing arrays
	memset(temp,0,30);
	int i = 0,j = 0,count = 0,k = 0;
	while(a[i] != '\0'){ // adding all information to an array from combination 
		j = a[i]-49; // char to int
		for(k = 0;k < 3;k++){
			temp2[k] = _locations[j][k];
		}
		strcat(temp,temp2);
		i++;
	}
	
	for(i = 0;i < 6;i++){  // controling cities one by one if that combination contains all cities
			for(j = 0;j < strlen(temp);j++){
				if(temp[j] == _cities[i]){
					count++;
					break;
				}
			}
		}
	if(count == 6){ // if it contains save it to the struct and return
		for(i = 0;i < _numHospitals;i++){
		results[i].name = i+49;
		k = a[i] - 49;
			for(j = 0;j < 3;j++){
				results[i].citiesServed[j] = _locations[k][j];
			}
		}
		return 1;
		}
	else{
		return 0;
	}

}


void shuffle_deck(char faces[13][10],char suits[4][10],struct card cards[52]){
	int i,j = 0;
	for(i = 0;i < 52;i++){
		strcpy(cards[i].face,faces[rand()%13]); 														// first i copy
		strcpy(cards[i].suit,suits[rand()%4]);
		for(j = 0;j < i;j++){
			if(strcmp(cards[i].suit,cards[j].suit) == 0 && strcmp(cards[i].face,cards[j].face) == 0){   // then i control if i already use that combination
				i--;
				break;
			}
		}
	}
}

// I find all combinations of number of hospital and control every combination of locations
int combinationUtil(int arr[], int data[], int start, int end, int index, int r,char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]) { 
    int i,j,k;
    char a[10];
    
    	if (index == r){
	   		for (j=0; j<r; j++) a[j] = data[j] + 48;
	   			a[j] = '\0';
	   			k = canOfferCovidCoverage(_cities,_locations,_numHospitals,results,a);
		        if(k == 1)	return 1;
	       		return 0;
	}
        for (i=start; i<=end && end-i+1 >= r-index; i++){ 
		    data[index] = arr[i]; 
		    k = combinationUtil(arr, data, i+1, end, index+1, r,_cities,_locations,_numHospitals,results);
		    if(k == 1)		return k;
    }
}




