#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "term1901042643.h"
#define inch 72

double minx = 100000,maxx = -100000,miny = 100000,maxy = -100000;

Figure * start_figure(double width, double height){
	struct Figure *myfig;
	myfig = (Figure*)malloc(sizeof(Figure));
	myfig->width = width;
	myfig->height = height;
	return myfig;
}
	
void set_thickness_resolution(Figure * fig, double thickness, double resolution){
	fig-> thickness = thickness;
	fig-> resolution = resolution;
}

void set_color(Figure * fig, Color c){
	fig->colour.red = c.red;
	fig->colour.green = c.green;
	fig->colour.blue = c.blue;
}

void add_point(Point2D *dot,double x,double y){
	while(dot -> next != NULL)dot = dot -> next;
	dot -> next = (Point2D*)malloc(sizeof(Point2D));
	dot -> next -> x = x;
	dot -> next -> y = y;
	dot -> next -> next = NULL;
}

void draw_fx(Figure * fig, double f(double x),double start_x, double end_x,double step_size){		// i multiply every x and y number with resolution.Unless you use a function like x=3 and stepsize < 1 function will give right resolution
	double i = start_x;
	double x;
	fig -> pt = (Point2D*)malloc(sizeof(Point2D));
	fig -> pt -> x = i * fig -> resolution;
	fig -> pt -> y = f(i * fig -> resolution);
	fig -> pt -> next = NULL;
	Point2D *iter = fig -> pt;
	start_x += step_size;
	for(i = start_x;i <= end_x;i += step_size){
		add_point(fig -> pt,i * fig -> resolution,f(i * fig -> resolution));
	}
}



void draw_polyline(Point2D * poly_line, int n,double resolution,int is_it_test){
	int i;
	double x,y;
	if(is_it_test == 0){
		printf("Enter the x and y coordinates respectively.\n");
		scanf("%lf %lf",&x,&y);
	}
	else{
		x = 0;
		y = 0;
	}
	poly_line -> x = x * resolution;
	poly_line -> y = y * resolution;
	poly_line -> next = NULL;
	for(i = 1;i < n;i++){
	if(is_it_test == 0){
		printf("Enter the x and y coordinates respectively.\n");	
		scanf("%lf %lf",&x,&y);
	}
	else{
		x = 0;
		y = 0;
	}
	add_point(poly_line,x * resolution,y * resolution);
	}
}

void draw_polygon(Point2D * poly_line,double resolution,int is_it_test){
	int i = 0;
	double x,y;
	Point2D *cont = poly_line;
	if(is_it_test == 0){
		printf("Enter the x and y coordinates respectively.\n");
		scanf("%lf %lf",&x,&y);
	}
	else{
		x = 0;
		y = 0;
	}
	poly_line -> x = x * resolution;
	poly_line -> y = y * resolution;
	while(1){
	if(is_it_test == 0){
		printf("Enter the x and y coordinates respectively.\n");
		scanf("%lf %lf",&x,&y);
	}
	else{
		x = 0;
		y = 0;
		i++;
		if(i == 8) return;
	}
	add_point(poly_line,x * resolution,y * resolution);
	if(x * resolution == cont ->  x && y * resolution == cont -> y && is_it_test == 0) return;
	}
}

void draw_ellipse(Point2D * center, Point2D * width_height,int is_it_test){	//	First i do it like draw_fx function step by step.Then i discover arc function so do it that way.Both are here
/*	//		Formula is (x - h)^2 / a^2 + (y - k)^2 / b^2 = 1
	//		Point2D centre will be my ellipse
	//		step size will be 0.1
	double h = centre -> x,k = centre -> y,a = width_height -> x,b = width_height -> y;
	double x = h - a,y,y2;
	Point2D *iter = centre;
		y = k + sqrt(pow(b,2) * (1 - pow((x - h),2) / pow(a,2)));
		y2 = k - sqrt(pow(b,2) * (1 - pow((x - h),2) / pow(a,2)));
		centre -> x = x;
		centre -> y = y;
		centre -> y2 = y2;
		x += 0.5;
		while(x <= h + a){
		y = k + sqrt(pow(b,2) * (1 - pow((x - h),2) / pow(a,2)));
		y2 = k - sqrt(pow(b,2) * (1 - pow((x - h),2) / pow(a,2)));
		add_point_ellipse(centre,x,y,y2);
		x += 0.5;
		}
		while(iter -> next != NULL){
			printf("x %lf   y %lf    y2 %lf\n",iter->x,iter->y,iter->y2);
			iter = iter -> next;
		}
		printf("x %lf   y %lf    y2 %lf\n",iter->x,iter->y,iter->y2);*/
	center -> next = (Point2D*)malloc(sizeof(Point2D));
	center -> next -> next = NULL;
	if(is_it_test == 0){
		printf("Enter the Center(x,y) values respectively\n");
		scanf("%lf%lf",&center -> x,&center -> y);
		printf("Enter the Width (a) and Height (b) values respectively\n");
		scanf("%lf%lf",&center->next->x,&center->next->y);
	}
	else{		// for test function
		center -> x = 5;
		center -> y = 6;
		center -> next -> x = 10;
		center -> next -> y = 2;
	}
}

void draw_binary_tree(Tree * root){
	int x,y;
		printf("Enter a number for left leaf (Enter a few (-) number to end)\n");
		scanf("%d",&x);
		if(x > -1){
			root -> left = (Tree*)malloc(sizeof(Tree));
			root -> left -> data = x;
			root -> left -> left = NULL;
			root -> left -> right = NULL;
		draw_binary_tree(root -> left);
		}
		printf("Enter a number for right leaf (Enter a few (-) number to end)\n");
		scanf("%d",&x);
		if(x > -1){
		root -> right = (Tree*)malloc(sizeof(Tree));
		root -> right -> data = x;
		root -> right -> left = NULL;
		root -> right -> right = NULL;
		draw_binary_tree(root -> right);
		}
}

void scale_figure(double scale_x, double scale_y,char *file_name){		// i find BoundingBox and add "x y scale" to under of it and scale bounding box also
	char *copy = (char*)malloc(sizeof(char)),*copy2 = (char*)malloc(sizeof(char)),buffer[20];
	int count;
	FILE *fp = fopen(file_name,"r+");
	if(fp == NULL){
		printf("There is no file with that name.Try another day.\n");
		return;
	}
	while(strstr(buffer,"BoundingBox") == NULL){
		memset(buffer,0,20);
		fscanf(fp,"%s",buffer);
	}
	count = ftell(fp);
	fseek(fp,0,SEEK_SET);
	int i;
	for(i = 0;i < count;i++){
		copy = (char *)realloc(copy,(i + 1) * sizeof(char));
		copy[i] = fgetc(fp);
	}
	copy[i] = '\0';
	fscanf(fp,"%s",buffer);
	fscanf(fp,"%s",buffer);
	fscanf(fp,"%s",buffer);
	double dubbuf = atof(buffer);
	fscanf(fp,"%s",buffer);
	double dubbuf2 = atof(buffer);
	i = 0;
	while(!feof(fp)){
		copy2 = (char *)realloc(copy2,(i + 1) * sizeof(char));
		copy2[i] = fgetc(fp);
		i++;
	}
	copy2[i - 1] = '\0';
	fclose(fp);
	fp = fopen(file_name,"w");
	fprintf(fp,"%s %lf %lf %lf %lf\n%lf %lf scale%s",copy,(-1) * dubbuf * scale_x,(-1) * dubbuf2 * scale_y,dubbuf * scale_x,dubbuf2 * scale_y,scale_x,scale_y,copy2);
	fclose(fp);
}


void resize_figure(Point2D *start_roi, Point2D *end_roi,char *file_name){	// i find boundingbox and change it
	char *copy = (char*)malloc(sizeof(char)),*copy2 = (char*)malloc(sizeof(char)),buffer[20];
	int count;
	FILE *fp = fopen(file_name,"r+");
	if(fp == NULL){
		printf("There is no file with that name.Try another day.\n");
		return;
	}
	while(strstr(buffer,"BoundingBox") == NULL){
		memset(buffer,0,20);
		fscanf(fp,"%s",buffer);
	}
	count = ftell(fp);
	printf("%d\n\n\n",count);
	fseek(fp,0,SEEK_SET);
	int i;
	for(i = 0;i < count;i++){
		copy = (char *)realloc(copy,(i + 1) * sizeof(char));
		copy[i] = fgetc(fp);
	}
	copy[i] = '\0';
	while(buffer[0] != '\n') buffer[0] = fgetc(fp);
	i = 0;
	while(!feof(fp)){
		copy2 = (char *)realloc(copy2,(i + 1) * sizeof(char));
		copy2[i] = fgetc(fp);
		i++;
	}
	
	copy2[i - 1] = '\0';
	fclose(fp);
	fp = fopen(file_name,"w");
	fprintf(fp,"%s %lf %lf %lf %lf\n%s\n",copy,start_roi -> x,start_roi -> y,end_roi -> x,end_roi -> y,copy2);
	fclose(fp);
}

/*void append_figures(Figure * fig1, Figure * fig2);*/


void export_eps(Figure * fig, char * file_name){
		minx = 100000;maxx = -100000;miny = 100000;maxy = -100000;		// reset numbers
	if(fig -> type == 0){
		FILE *fp = fopen("cont.txt","w+");				// opening temporary file
		Point2D *iter = fig -> pt;
		fprintf(fp,"%lf setlinewidth\n2 setlinejoin\n%lf %lf moveto\n",fig -> thickness,iter -> x,iter -> y);
		if(iter -> y > maxy) maxy = iter -> y;		// controling every number for BoundingBox
		if(iter -> y < miny) miny = iter -> y;
		if(iter -> x > maxx) maxx = iter -> x;
		if(iter -> x < minx) minx = iter -> x;
		iter = iter -> next;
		while(iter -> next != NULL){
			if(iter -> y > maxy) maxy = iter -> y;
			if(iter -> y < miny) miny = iter -> y;
			if(iter -> x > maxx) maxx = iter -> x;
			if(iter -> x < minx) minx = iter -> x;
			
			fprintf(fp,"%lf %lf lineto\n",iter -> x,iter -> y);
			iter = iter -> next;
		}
			if(iter -> y > maxy) maxy = iter -> y;
			if(iter -> y < miny) miny = iter -> y;
			if(iter -> x > maxx) maxx = iter -> x;
			if(iter -> x < minx) minx = iter -> x;
			
			fprintf(fp,"%lf %lf lineto \nstroke",iter -> x ,iter -> y );
			fseek(fp,0,SEEK_SET);					// reset the cursor
			char *copy = (char*)malloc(sizeof(char));
			int i = 0;
			while(!feof(fp)){					// copy back from temporary file
				copy = (char *)realloc(copy,(i + 1) * sizeof(char));
				copy[i] = fgetc(fp);
				i++;
			}
			copy[i - 1] = '\0';
			fclose(fp);
			fp = fopen(file_name,"w+");
			fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
			if(fig -> width == 0 && fig->height == 0){		// There is no boundary
				maxx = (maxx + fig -> thickness / 2);
				minx = (minx - fig -> thickness / 2);
				maxy = (maxy + fig -> thickness / 2);
				miny = (miny - fig -> thickness / 2);
				fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n",minx,miny,maxx,maxy);
			}
			else fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n",(-1) * fig -> width / 2,(-1) * fig -> height / 2,fig -> width / 2,fig -> height / 2);
		
			fprintf(fp,"%lf %lf %lf setrgbcolor clippath fill\n%lf %lf %lf setrgbcolor\n",fig -> backcolour.red,fig -> backcolour.green,fig -> backcolour.blue,fig->colour.red,fig->colour.green,fig->colour.blue);
			fprintf(fp,"%s",copy);
			fclose(fp);
		}
	else if(fig -> type == 1){
		double h = fig -> pt -> x,k = fig -> pt -> y;
		double a = fig -> pt -> next -> x,b = fig -> pt -> next -> y,c;
		maxx = h + a ;
		minx = h - a ;
		maxy = k + b ;
		miny = k - b ;
		double rate1,rate2;
			if(b > a){		// my algorithm uses 'a' as big one
				c = a;
				a = b;
				b = c;
				rate1 = b / a;
				rate2 = 1;
				h /= rate1;		// Scaling also scales the boundingbox not only ellipse
			}
			else{
				rate1 = 1;
				rate2 = b / a;
				k /= rate2;		// Scaling also scales the boundingbox not only ellipse
			}
		FILE *fp = fopen("cont.txt","w+");
		fprintf(fp,"\n%lf %lf scale\n",rate1,rate2);
		fprintf(fp,"%lf %lf %lf setrgbcolor\n",fig->colour.red,fig->colour.green,fig->colour.blue);
		fprintf(fp,"%lf %lf %lf %d %d arc\nstroke\n",h,k,a,0,360);

		fseek(fp,0,SEEK_SET);
		char *copy = (char*)malloc(sizeof(char));
		int i = 0;
		while(!feof(fp)){		// copy back from temporary file
			copy = (char *)realloc(copy,(i + 1) * sizeof(char));
			copy[i] = fgetc(fp);
			i++;
		}
		copy[i - 1] = '\0';
		fclose(fp);
		fp = fopen(file_name,"w+");
			fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
			fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n%lf setlinewidth",minx - fig -> thickness /2,miny - fig -> thickness /2,maxx + fig -> thickness /2,maxy + fig -> thickness /2,fig -> thickness);
			fprintf(fp,"%s",copy);
			fclose(fp);
		}
		else if(fig -> type == 2){
			FILE *fp = fopen("cont.txt","w+");
			int x = 200,y = 200;
			fprintf(fp, "%lf %lf %lf setrgbcolor\n%lf setlinewidth\n",fig->colour.red,fig->colour.green,fig->colour.blue,fig -> thickness);
			fprintf(fp,"/Times-Bold findfont %lf scalefont setfont\n\n%d %d %lf 0 360 arc stroke\n%lf %lf moveto (%d) show\n",fig -> resolution /3,x,y,fig -> resolution /2,x-fig -> resolution / 12,y-fig -> resolution / 12,fig -> tre -> data);
			fclose(fp);
			
			if(y > maxy) maxy = y;
			if(y < miny) miny = y;
			if(x > maxx) maxx = x;
			if(x < minx) minx = x;
			if(fig -> tre -> left != NULL) export_tree_eps(fig -> tre -> left,"cont.txt",3,x,y,fig -> resolution / 2);		// 3 and 4 for the first time to separate more
			if(fig -> tre -> right != NULL) export_tree_eps(fig -> tre -> right,"cont.txt",4,x,y,fig -> resolution / 2);

			fp = fopen("cont.txt","r");
			fseek(fp,0,SEEK_SET);
			char *copy = (char*)malloc(sizeof(char));
			int i = 0;
			while(!feof(fp)){					// copy back from temporary file
				copy = (char *)realloc(copy,(i + 1) * sizeof(char));
				copy[i] = fgetc(fp);
				i++;
			}
			copy[i - 1] = '\0';
			fclose(fp);
			fp = fopen(file_name,"w");

			fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
			maxx = (maxx + fig -> resolution / 2 + fig -> thickness / 2);
			minx = (minx - fig -> resolution / 2 - fig -> thickness / 2);
			double avex = minx + (maxx - minx) / 2;
			maxy = (maxy + fig -> resolution / 2 + fig -> thickness / 2);
			miny = (miny - fig -> resolution / 2 - fig -> thickness / 2);
			double avey = miny + (maxy - miny) / 2;
			fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n",(-1) * (maxx - minx)/2,(-1) * (maxy - miny)/2,(maxx - minx)/2,(maxy - miny)/2);
			fprintf(fp,"%lf %lf translate\n",(-1) * avex,(-1) * avey);
			fprintf(fp,"%s",copy);
			fclose(fp);
		}
}


void export_tree_eps(Tree *tre,char *file_name,int type,int x,int y,double radius){					// in this function first (3 and 4) i diverge more than normal to block collision then (0 and 1) diverge depending to radius.Then call function back with other leaves
	FILE *fp = fopen(file_name,"a+");
	if(type == 0){		// means came from right
		fprintf(fp,"\nnewpath\n%lf %lf moveto %lf %lf lineto stroke\n",x - radius * sqrt(2)/2,y - radius * sqrt(2)/2,x - 2 * radius,y - 2 * radius);
		x -= 2 * radius;
		y -= 3 * radius;
		fprintf(fp,"%d %d %lf 0 360 arc stroke\n%lf %lf moveto (%d) show\n",x,y,radius,x- radius / 6,y - radius / 6,tre -> data);

		if(y > maxy) maxy = y;
		if(y < miny) miny = y;
		if(x > maxx) maxx = x;
		if(x < minx) minx = x;
	}
	else if(type == 1){
		fprintf(fp,"\nnewpath\n%lf %lf moveto %lf %lf lineto stroke\n",x + radius * sqrt(2)/2,y - radius * sqrt(2)/2,x + 2 * radius,y - 2 * radius);
		x += 2 * radius;
		y -= 3 * radius;
		fprintf(fp,"%d %d %lf 0 360 arc stroke\n%lf %lf moveto (%d) show\n",x,y,radius,x- radius / 6,y - radius / 6,tre -> data);

		if(y > maxy) maxy = y;
		if(y < miny) miny = y;
		if(x > maxx) maxx = x;
		if(x < minx) minx = x;

	}
	else if(type == 3){
		fprintf(fp,"\nnewpath\n%lf %lf moveto %lf %lf lineto stroke\n",x - radius * sqrt(2)/2,y - radius * sqrt(2)/2,x - 6 * radius,y - 2 * radius);
		x -= 6 * radius;
		y -= 3 * radius;
		fprintf(fp,"%d %d %lf 0 360 arc stroke\n%lf %lf moveto (%d) show\n",x,y,radius,x - radius / 6,y - radius / 6,tre -> data);

		if(y > maxy) maxy = y;
		if(y < miny) miny = y;
		if(x > maxx) maxx = x;
		if(x < minx) minx = x;
	}
	else if(type == 4){
		fprintf(fp,"\nnewpath\n%lf %lf moveto %lf %lf lineto stroke\n",x + radius * sqrt(2)/2,y - radius * sqrt(2)/2,x + 6 * radius,y - 2 * radius);
		x += 6 * radius;
		y -= 3 * radius;
		fprintf(fp,"%d %d %lf 0 360 arc stroke\n%lf %lf moveto (%d) show\n",x,y,radius,x-radius/6,y-radius/6,tre -> data);

		if(y > maxy) maxy = y;
		if(y < miny) miny = y;
		if(x > maxx) maxx = x;
		if(x < minx) minx = x;
	}
	if(tre -> left != NULL)export_tree_eps(tre -> left,file_name,0,x,y,radius);
	if(tre -> right != NULL)export_tree_eps(tre -> right,file_name,1,x,y,radius);
	fclose(fp);
}



