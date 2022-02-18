#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct point{
	float x;
	float y;
	char name[5];
};

struct line{
	struct point p1;
	struct point p2;
	char name[5];
};

struct polygon{
	struct point pN[20];
	int cornercount;
	char name[5];
};

float point_distance(struct point p1,struct point p2){ 
	return sqrt(pow(p2.x - p1.x,2)+pow(p2.y - p1.y,2));
}


void linepoint_distance(char output[],struct line l1,struct point p1){  //oke
					

	FILE *fp = fopen(output,"a");
	float m1,m2,c1,c2,intersection_X,intersection_Y,result;
	m1 = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
	c1 = l1.p1.y - m1 * l1.p1.x;  //    c = y - m * x
	m2 = (-1)/m1;  // treating as line to the point and creating an equation
	c2 = p1.y - m2 * p1.x;
	if(m1 == 0){    // slope is 0
		result = p1.y - l1.p1.y;
		if(result < 0) result *= -1;
		fprintf(fp,"Distance(%s,%s) = %.1f\n",l1.name,p1.name,result);
		fclose(fp);
		return;
	}
	else if(m2 == 0){  // slope is infinity
		result = p1.x - l1.p1.x;
		if(result < 0) result *= -1;
		fprintf(fp,"Distance(%s,%s) = %.1f\n",l1.name,p1.name,result);
		fclose(fp);
		return;	
	}
        intersection_X = (c2 - c1) / (m1 - m2);
        intersection_Y = m1 * intersection_X + c1;
        struct point p2;
        p2.x = intersection_X;
        p2.y = intersection_Y;
        fprintf(fp,"Distance(%s,%s): %.1f\n",l1.name,p1.name,point_distance(p1,p2)); // returning distance between point and intersection point
        fclose(fp);
}

void angle(char output[],struct line l1,struct line l2){
	FILE *fp = fopen(output,"a");
	float m1,m2,c1,c2;
	m1 = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
	m2 = (l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x);
	if(m1 == -0) m1 = 0;
	if(m2 == -0) m2 = 0;
	int temp;
	if(m1 > m2){
		temp = m2;
		m2 = m1;
		m1 = temp;
	}
	float PI = 3.14159265;
	float a = (m2 - m1);
	float b = 1 + m1 * m2;
	float result = a/b;
	if(m1 == m2){
		result = 0;
	}
	else if(isnan(b) == 1){
		result = 90;
	}
	else result = atan(result) * 180 / PI;  // radian to degree
		fprintf(fp,"Angle(%s,%s) = %.1f\n",l1.name,l2.name,result);
		fclose(fp);
		return;
}

void poli_perimeter(char output[],struct polygon pg1){
	FILE *fp = fopen(output,"a");
	float perimeter = 0;
	int i;
	for(i = 0;i < pg1.cornercount - 1;i++){
		perimeter += point_distance(pg1.pN[i],pg1.pN[i + 1]); // adding all border lengths
	}
	perimeter += point_distance(pg1.pN[i],pg1.pN[0]);   // and last one
	fprintf(fp,"Perimeter(%s) = %.1f\n",pg1.name,perimeter);
	fclose(fp);
}

void poli_area(char output[],struct polygon pg1){  // I used shoelace formula for this one
	FILE *fp = fopen(output,"a");
	float area = 0;
	int i;
	for(i = 0;i < pg1.cornercount - 1;i++){
		area += (pg1.pN[i].x * pg1.pN[i + 1].y) - (pg1.pN[i + 1].x * pg1.pN[i].y);
	}
	area /= 2;
	fprintf(fp,"Area(%s) = %.1f\n",pg1.name,area);
	fclose(fp);
}

int jump_blanks(int k,char c[100]){ 	// jumping blanks to reach to the other data
	while(c[k] == ' ') k++;
	return k;
}

int jump_nl(int i,char arr[2000]){	 // jumping to next line if we reach the "//"
	while(arr[i] != '\n') i++;
	return i+1;
}


void main(){
	
	char arr[2000],c[100],num[10],num2[10],linecontrol[10],output[20];
	float distance;
	memset(linecontrol,'\0',10);
	memset(num,'\0',10);
	memset(arr,'\0',2000);
	memset(c,'\0',100);
	FILE *fp;
	struct point *pptr = (struct point*)malloc(sizeof(struct point));
	struct line *lptr = (struct line*)malloc(sizeof(struct line));
	struct polygon *poliptr = (struct polygon*)malloc(sizeof(struct polygon));
	fp = fopen("commands.txt","r");
	if(fp == NULL){
		printf("File can not opened.\n");
		return;
	}
	int i = 0,j = 0,k = 0,m = 0,n = 0,b = 0,v = 0;
	int count,pointcount = 0,policount = 0,linecount = 0,linePolicount = 0,pointPolicount = 0,numcont1,numcont2,endcontrol;
	 while(!feof(fp)) {
      arr[i] = fgetc(fp);
      i++;
  	}
  	arr[i-1] = '\0';
  	arr[i] = '\n';
  	i = 0;
  	while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/')){    // I am reading file line by line
  		c[k] = arr[i];
  		k++;
  		i++;
 	  }
 	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
 	else i++;
 	k = 0;
 	if(strstr(c,"data") == NULL) return;				// data
 		memset(c,'\0',sizeof(c));
 	  		while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/')){
		  		c[k] = arr[i];
		  		k++;
		  		i++;
 		  	}
 		  	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
 		  	else i++;

 		  	k = 0;
 		count = atof(c);					//       number of geometric objects
 		memset(c,'\0',sizeof(c));
	 		for(j = 0;j < count;j++){
	 			k = 0;
	 			m = 0;
	 			memset(c,'\0',sizeof(c));
	 			while(arr[i] != '\n' && (arr[i] != '/' || arr[i + 1] != '/')){
			  		c[k] = arr[i];
			  		k++;
			  		i++;
	 		  	}
	 		  	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
	 		  	else i++;
	 		  	k = 0;
	 		  	k = jump_blanks(k,c);
	 		  	if(isdigit(c[k]) != 0){ // this means we will create a point
	 		  		pointcount++;
	 		  		pptr = (struct point*) realloc(pptr,pointcount * sizeof(struct point));
	 		  		while(c[k] != ' '){ // x coordinate
	 		  			num[m] = c[k];
	 		  			m++;
	 		  			k++;
					   }
					(pptr + pointcount - 1)->x = atof(num);
					m = 0;
					memset(num,'\0',10);
					k = jump_blanks(k,c);
					while(c[k] != ' '){ // y coordinate
						num[m] = c[k];
	 		  			m++;
	 		  			k++;
					}
					(pptr + pointcount - 1)->y = atof(num);
					memset(num,'\0',10);
					m = 0;
					k = jump_blanks(k,c);
					while(c[k] != ' '){ // name
						num[m] = c[k];
	 		  			m++;
	 		  			k++;
					}
					strcpy((pptr + pointcount - 1)->name,num);
					if(isdigit((pptr + pointcount -1)->name[2]) == 0) (pptr + pointcount -1)->name[2] = '\0'; // assigning NULL to end of names to print correctly
					else if(isdigit((pptr + pointcount -1)->name[3]) == 0) (pptr + pointcount -1)->name[3] = '\0';

				   }
				else if(strstr(c,"PG") != NULL){  // this means we will create a polygon
				   	policount++;
				   	if(c[0] == 'L'){  // this means we will use lines
				   		for(n = 0;c[n] != 'G';n++) if(c[n] == 'L')linePolicount++;
				   			poliptr = (struct polygon*) realloc(poliptr,policount * sizeof(struct polygon));
				   			(poliptr + policount - 1)->cornercount = linePolicount;  // number of corners
				   			n = 0;
				   		for(b = 0;b < linePolicount;b++){
				   			while(c[n] != 'L') n++;
				   			n++;
			   				memset(num,'\0',10);
			   				num[0] = c[n];   // i assume that lines has 2 points that has 1 digit "L12"  (not L112)
			   				if(strstr(linecontrol,num) == NULL) strcat(linecontrol,num); 
			  				num[0] = c[n + 1];
							if(strstr(linecontrol,num) == NULL) strcat(linecontrol,num);
				   			for(v = 0;v < pointcount;v++){  // finding name of point from point order to copy it to polygon
			   					if((pptr + v)->name[1] == linecontrol[b]) break;
							}
							(poliptr + policount - 1)->pN[b].x = (pptr + v)->x;
							(poliptr + policount - 1)->pN[b].y = (pptr + v)->y;
							strcpy((poliptr + policount -1)->pN[b].name,(pptr + v)->name);
				   			n++;
				   		}
				   		n = 0;
				   		while(c[n] != 'G') n++;
				   		(poliptr + policount -1)->name[0] = c[n - 1];
				   		(poliptr + policount -1)->name[1] = c[n];
				   		(poliptr + policount -1)->name[2] = c[n + 1];
				   	}
				   	else{            // this means we will use points
				   		pointPolicount = 0;
				   		for(n = 0;c[n] != 'G';n++) if(c[n] == 'P')pointPolicount++;
				   		pointPolicount-=1; 	// because "PG" also starts with 'P'
				   			poliptr = (struct polygon*) realloc(poliptr,policount * sizeof(struct polygon));
				   			(poliptr + policount - 1)->cornercount = pointPolicount;
				   		n = 0;
				   		for(b = 0;b < pointPolicount;b++){

				   			while(c[n] != 'P') n++;
				   			n++;
				   			memset(num,'\0',10);
		   					num[0] = c[n];
			   				if(isdigit(c[n + 1] != 0)) num[1] = c[n + 1];// controling situation like P13 two digits
		   					numcont1 = atof(num);  	// polygon point number like 'P1' or 'P2'
			   				memset(num,'\0',10);
		   					for(v = 0;v < pointcount;v++){  // finding name of point from point order to copy it to polygon
		   						num[0] = (pptr + v)->name[1];
		   						if(isdigit((pptr + v)->name[2]) != 0) num[1] = (pptr + v)->name[2];
			   					numcont2 = atof(num);
			   					if(numcont2 == numcont1) break;
							}
							(poliptr + policount - 1)->pN[b].x = (pptr + v)->x;
							(poliptr + policount - 1)->pN[b].y = (pptr + v)->y;
							strcpy((poliptr + policount - 1)->pN[b].name,(pptr + v)->name);
				   		}
				   		while(c[n] != 'G') n++;
				   		(poliptr + policount -1)->name[0] = c[n - 1];
				   		(poliptr + policount -1)->name[1] = c[n];
				   		(poliptr + policount -1)->name[2] = c[n + 1];
				   	}
				 }
				 else{  		// this means we will create line
				 	linecount++;
				 	lptr = (struct line*)realloc(lptr,linecount * sizeof(struct line));
				 	memset(num,'\0',10);
				 	n = 0;
				 	while(c[n] != 'P') n++;
		   				n++;
				 	for(v = 0;v < pointcount;v++){  // finding name of point from point order to copy it to line
			   			if((pptr + v)->name[1] == c[n]) break;
					}
				 		(lptr + linecount - 1)->p1.x = (pptr + v)->x;
				 		(lptr + linecount - 1)->p1.y = (pptr + v)->y;
				 		strcpy((lptr + linecount - 1)->p1.name,(pptr + v)->name);
				 		while(c[n] != 'P') n++;
		   				n++;
				 	for(v = 0;v < pointcount;v++){  // finding name of point from point order to copy it to line
			   			if((pptr + v)->name[1] == c[n]) break;
					}
						(lptr + linecount - 1)->p2.x = (pptr + v)->x;
				 		(lptr + linecount - 1)->p2.y = (pptr + v)->y;
				 		strcpy((lptr + linecount - 1)->p2.name,(pptr + v)->name);
				 		while(c[n] != 'L') n++;
				 		(lptr + linecount - 1)->name[0] = c[n];
				 		(lptr + linecount - 1)->name[1] = c[n + 1];
				 		(lptr + linecount - 1)->name[2] = c[n + 2];
				 }
				 
			 }
		 	while(strstr(c,"actions") == NULL){
		 		k = 0;
		 		memset(c,'\0',sizeof(c));
		 		while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/')){
		  		c[k] = arr[i];
		  		k++;
		  		i++;
		 	  }
		 		if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
		 		else i++;
		 	}
		 	k = 0;
		 	memset(c,'\0',sizeof(c));

			while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/')){
		  		c[k] = arr[i];
		  		k++;
		  		i++;
 		  	}
 		  	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
 		  	else i++;
 		  	strcpy(output,c);  								//  output file
 		  	FILE *fpw = fopen(output,"w");  				// erasing/creating output file
 		  	fclose(fp);
 		  	k = 0;
 		  	memset(c,'\0',sizeof(c));
		 	while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/')){
		  		c[k] = arr[i];
		  		k++;
		  		i++;
 		  	}
 		  	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
 		  	else i++;
 			count = atof(c);			// number of actions

	 		for(j = 0;j < count;j++){
				memset(c,'\0',sizeof(c)); 		  	
 			  	k = 0;
	 			while(arr[i] != '\n' || (arr[i] == '/' && arr[i + 1] == '/') || i == endcontrol){
		  		c[k] = arr[i];
		  		k++;
		  		i++;
 		  	}

 		  	if(arr[i] == '/' && arr[i + 1] == '/') i = jump_nl(i,arr);
 		  	else i++;

				
			if(strstr(c,"Distance") != NULL){
				if(strstr(c,"L") != NULL){
					k = 0;
					while(c[k] != 'L') k++;
					memset(num,'\0',10);
					m = 0;
					while(c[k] != ' '){
						num[m] = c[k];
						m++;k++;
					}
					for(v = 0;v < linecount;v++){  // finding name of line from line order
						if(strstr((lptr + v)->name,num) != NULL) break;
					}
					k = 0;
					m = 0;
					while(c[k] != 'P') k++;
					k++;
					memset(num2,'\0',10);
					num2[0] = c[k];
					numcont1 = atof(num2);
					for(b = 0;b < pointcount;b++){  // finding name of point from point order to copy it to polygon
		   				num2[0] = (pptr + b)->name[1];
		   				if(isdigit((pptr + b)->name[2]) != 0) num2[1] = (pptr + b)->name[2];
		 				numcont2 = atof(num2);
	  					if(numcont2 == numcont1) break;
					}
					num2[2] = num2[1];
					num2[1] = num2[0];
					num2[0] = 'P';
					if(b == pointcount){
						FILE *fpd = fopen(output,"a");
						fprintf(fpd,"Distance(%s,%s) = NOT_IMPLEMENTED (%s does not exists.)\n",num,num2,num2);
						fclose(fpd);
					}
					else if(v == linecount){
						FILE *fpd = fopen(output,"a");
						fprintf(fpd,"Distance(%s,%s) = NOT_IMPLEMENTED (%s does not exists.)\n",num,num2,num);
						fclose(fpd);	

					}
					else linepoint_distance(output,*(lptr + v),*(pptr + b));

				}
				else{
					k = 0;
					while(c[k] != 'P') k++;
					k++;
					memset(num,'\0',sizeof(num));
					num[0] = c[k];
					numcont1 = atof(num);
					for(v = 0;v < pointcount;v++){  // finding name of point from point order to copy it to polygon
		   				num[0] = (pptr + v)->name[1];
		   				if(isdigit((pptr + v)->name[2]) != 0) num[1] = (pptr + v)->name[2];
		 				numcont2 = atof(num);
	  					if(numcont2 == numcont1) break;
					}
					while(c[k] != 'P') k++;
					k++;
					memset(num,'\0',sizeof(num));
					num[0] = c[k];
					numcont1 = atof(num);
					memset(num,'\0',sizeof(num));
					for(b = 0;b < pointcount;b++){  // finding name of point from point order to copy it to polygon
		   				num[0] = (pptr + b)->name[1];
		   				if(isdigit((pptr + b)->name[2]) != 0) num[1] = (pptr + b)->name[2];
		 				numcont2 = atof(num);
	  					if(numcont2 == numcont1) break;
					
					}
					FILE *fp = fopen(output,"a");
			fprintf(fp,"Distance(%s,%s) = %.1f\n",(pptr + v)->name,(pptr + b)->name,point_distance(*(pptr + v),*(pptr + b)));
					fclose(fp);
				}
			}
			else if(strstr(c,"Angle") != NULL){
				k = 0;
				while(c[k] != 'L') k++;
				memset(num,'\0',sizeof(num));
				m = 0;
				while(c[k] != ' '){
					num[m] = c[k];
					m++;k++;
				}
				for(v = 0;v < linecount;v++){  // finding name of line from line order
					if(strstr((lptr + v)->name,num) != NULL) break;
				}
				k++;
				while(c[k] != 'L') k++;
				num[1] = c[k + 1];
				num[2] = c[k + 2];
				for(b = 0;b < linecount;b++){  // finding name of line from line order
					if(strstr((lptr + b)->name,num) != NULL) break;
				}
				angle(output,*(lptr + v),*(lptr + b));
			}
			else if(strstr(c,"Length") != NULL){
				if(strstr(c,"PG") != NULL){
					memset(num,'\0',sizeof(num));
					k = 0;
					while(c[k] != 'P') k++;
						num[0] = c[k];
						num[1] = c[k + 1];
						num[2] = c[k + 2];
					for(v = 0;v < policount;v++){  // finding name of line from line order
						if(strstr((poliptr + v)->name,num) != NULL) break;
					}
					if(v == policount){
						FILE *fp = fopen(output,"a");
						fprintf(fp,"Length(%s) = NOT_IMPLEMENTED (%s does not exists.)\n",num,num);
						fclose(fp);
					}
					else poli_perimeter(output,*(poliptr + v));

					}
				else{
					memset(num,'\0',10);
					k = 2;
					while(c[k] != 'L') k++;
					num[0] = c[k];
					k++;
					m = 1;
					while(isdigit(c[k]) != 0){
						num[m] = c[k];
						m++;k++;
					}
					for(v = 0;v < linecount;v++){  // finding name of line from line order
						if(strstr((lptr + v)->name,num) != NULL) break;
					}
				if(v == linecount){
					FILE *fp = fopen(output,"a");
					fprintf(fp,"Length(%s) = NOT_IMPLEMENTED ( %s does not exists.)\n",num,num);
					fclose(fp);	
				}
				else{
					FILE *fp = fopen(output,"a");
					fprintf(fp,"Length(%s): %.1f\n",(lptr + v)->name,point_distance((lptr + v)->p1,(lptr + v)->p2));
					fclose(fp);
				}
				}
			}
			else if(strstr(c,"Area") != NULL){
				memset(num,'\0',sizeof(num));
				k = 0;
				while(c[k] != 'P') k++;
					num[0] = c[k];
					num[1] = c[k + 1];
					num[2] = c[k + 2];
				for(v = 0;v < policount;v++){  // finding name of line from line order
					if(strstr((poliptr + v)->name,num) != NULL) break;
				}
				if(v == policount){
					FILE *fp = fopen(output,"a");
					fprintf(fp,"Length(%s) = NOT_IMPLEMENTED (%s does not exists.)\n",num,num);
					fclose(fp);
				}
				else{
					poli_area(output,*(poliptr + v));
				}
			}
	 	}
	 	printf("Program worked properly.\n");
}
