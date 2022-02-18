#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "term_2_1901042643.h"
#include "term1901042643.h"

#define PI 3.141592654

double length = 0,innerlength = 0,opposite = 0;

void read_file(Figure *fig,char *file_name){
	FILE *fp = fopen(file_name,"r");
	if(fp == NULL){
		printf("patates\n");
		return;
	}
	int i = 0,j = 0,k = 0,archetype = 0;
	char line[100],buffer[100],name[100];
while(1){	
	i++;
	archetype = 0;
	memset(name,0,100);
	set_defaults(fig,"defaults.txt");		//	set default for every figure

	while(1){
	memset(line,0,100);
	memset(buffer,0,100);
		j = k = 0;
		while(line[j - 1] != ':' && line[j - 1] != 10 && line[j - 1] != '/' && !feof(fp)){		// reading type of attribute
			line[j] = fgetc(fp);
			j++;
		}
		if(line[j- 1] == 10){
			continue;
		}
		if(line[j - 1] == '/'){
			while(line[j - 1] != 10) line[j - 1] = fgetc(fp);
			continue;
		}
		if(feof(fp)) break;

		j = 0;
		if(strstr(line,"background") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> backcolour . red = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> backcolour . green = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> backcolour . blue = atof(buffer) / 255;
		}
		else if(strstr(line,"foreground") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> colour . red = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> colour . green = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> colour . blue = atof(buffer) / 255;
		}
		else if(strstr(line,"grid_color") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> gridcolour . red = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> gridcolour . green = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> gridcolour . blue = atof(buffer) / 255;

		}
		else if(strstr(line,"offset") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> angle = atof(buffer);
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> offset = atof(buffer);
		}
		else if(strstr(line,"canvas") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> width = atof(buffer);
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> height = atof(buffer);
		}
		else if(strstr(line,"pattern_thickness") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',' );
			buffer[k - 1] = 0;
			fig -> thickness = atof(buffer);
		}
		else if(strstr(line,"grid_thickness") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != '/' && buffer[k - 1] != 10);
			if(buffer[k - 1] == 10) fgetc(fp);
			buffer[k - 1] = 0;
			fig -> gridthickness = atof(buffer);
		}
		else if(strstr(line,"tile_size") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> resolution = atof(buffer);
		}
		else if(strstr(line,"show_grid") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			if(strstr(buffer,"False") != NULL) fig -> show_grid = 0;
			else fig -> show_grid = 1;
		}
		else if(strstr(line,"archetype") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			if(strstr(buffer,"Square") != NULL){
				archetype = 1;
			}
			else if(strstr(buffer,"Hexagon") != NULL){
				archetype = 2;
			}
		}
		else if(strstr(line,"file_name") != NULL){
			do{
				name[k] = fgetc(fp);
				k++;
			}while(name[k - 1] != 10 && name[k-1] != '/');
				name[k - 1] = 0;
				break;
		}
	}
	if(archetype == 0 || name[0] == 0){	//		no type or name
		if(feof(fp)) break;
		printf("Line %d is not valid\n",i);
	}
	else if(archetype == 1){		//	 square
		fig -> type = 3;
	}
	else if(archetype == 2){		//   hexagon
		fig -> type = 4;
	}
	if(archetype != 0 && name[0] != 0){
		export_islamic_eps(fig,name);
		printf("Line %d successfully exported\n",i);
	}
	if(feof(fp)) break;
	}
	fclose(fp);
}





void export_islamic_eps(Figure *fig,char *file_name){
	FILE *fp = fopen(file_name,"w");
	if(fig -> type == 3){
		fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n",(-1) * fig -> width / 2,(-1) * fig -> height / 2,fig -> width / 2,fig -> height / 2);
		fprintf(fp,"%lf %lf %lf setrgbcolor clippath fill\n%lf %lf %lf setrgbcolor\n",fig -> backcolour.red,fig -> backcolour.green,fig -> backcolour.blue,fig->colour.red,fig->colour.green,fig->colour.blue);
		fprintf(fp,"%lf setlinewidth\n2 setlinejoin\n",fig -> thickness);
		fclose(fp);

		double startx,starty;
		startx = (-1) * fig -> width / 2;
		starty = fig -> height / 2;

		double xtimes,ytimes;
		xtimes = fig -> width / fig -> resolution;
		ytimes = fig -> height / fig -> resolution;

		int i,j;
		length = sqrt(((fig -> resolution / 2 + fig -> offset) * sqrt(2)) * ((fig -> resolution / 2 + fig -> offset)  * sqrt(2)) / (2 - 2 * cos((90 + fig -> angle * 2) * PI / 180)));		// cosinus theorem to find length of dots inside of square that we draw by angle
		double xbuf = startx,ybuf = starty;
		for(i = 0;i < ytimes;i++){
			xbuf = startx;
			for(j = 0;j < xtimes;j++){
				append_square(fig,xbuf,ybuf,file_name,0);			// printing same motif starting from top left
				xbuf += fig -> resolution;
			}
			ybuf -= fig -> resolution;
		}
		if(fig -> show_grid == 1){
			xbuf = startx,ybuf = starty;
			FILE *fp = fopen(file_name,"a");
			fprintf(fp,"%lf %lf %lf setrgbcolor\n",fig -> gridcolour.red,fig -> gridcolour.green,fig -> gridcolour.blue);
			fclose(fp);
			for(i = 0;i < ytimes;i++){
				xbuf = startx;
					for(j = 0;j < xtimes;j++){
						append_square(fig,xbuf,ybuf,file_name,1);			// printing only grid
						xbuf += fig -> resolution;
					}
				ybuf -= fig -> resolution;
			}

		}
		length = 0;
	}
	else if(fig -> type == 4){
		fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp,"%%%%BoundingBox: %lf %lf %lf %lf\n",(-1) * fig -> width / 2,(-1) * fig -> height / 2,fig -> width / 2,fig -> height / 2);
		fprintf(fp,"%lf %lf %lf setrgbcolor clippath fill\n%lf %lf %lf setrgbcolor\n",fig -> backcolour.red,fig -> backcolour.green,fig -> backcolour.blue,fig->colour.red,fig->colour.green,fig->colour.blue);
		fprintf(fp,"%lf setlinewidth\n2 setlinejoin\n",fig -> thickness);
		fclose(fp);
		double startx,starty;
		startx = (-1) * fig -> width / 2 + fig -> resolution * sqrt(3) / 2;
		starty = fig -> height / 2 + fig -> resolution / 2;

		double xtimes,ytimes;
		xtimes = fig -> width / (fig -> resolution * sqrt(3));
		ytimes = fig -> height / (fig -> resolution * 7 / 4);

		xtimes++;
		ytimes++;


		opposite = sqrt(2 * (fig -> resolution / 2 + fig -> offset) * (fig -> resolution / 2 + fig -> offset) * (1 - cos(120 * PI / 180))); 	// I send a photo for a little description for how i did hexagon
		length = sqrt((opposite * opposite) / (2 - 2 * cos((240 - 2 * fig -> angle) * PI / 180)));			// cosinus theorem to find length of line that dots inside of square that we draw by angle
		innerlength = ((fig -> resolution * 2 - 2 * (length * sin((fig -> angle - 30) * PI / 180) + (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180))) / 2);		// dots creates a hexagon inside.Innerlength is length of 1 edge

		int i,j;
		double xbuf = startx,ybuf = starty;
		for(i = 0;i < ytimes;i++){
			if(i%2 == 0){
				xbuf = startx;
			}
			else xbuf = (-1) * fig -> width / 2;
			for(j = 0;j < xtimes;j++){
				append_hexagon(fig,xbuf,ybuf,file_name,0);
				xbuf += (fig -> resolution * sqrt(3));
			}
			ybuf -= (fig -> resolution * 3 / 2);
		}

		if(fig -> show_grid == 1){
			xbuf = startx,ybuf = starty;
			FILE *fp = fopen(file_name,"a");
			fprintf(fp,"%lf %lf %lf setrgbcolor\n",fig -> gridcolour.red,fig -> gridcolour.green,fig -> gridcolour.blue);
			fclose(fp);
			for(i = 0;i < ytimes;i++){
				if(i%2 == 0){
					xbuf = startx;
				}
				else xbuf = (-1) * fig -> width / 2;
				for(j = 0;j < xtimes;j++){
					append_hexagon(fig,xbuf,ybuf,file_name,1);
					xbuf += (fig -> resolution * sqrt(3));
				}
				ybuf -= (fig -> resolution * 3 / 2);
			}
		}
	opposite = 0;
	length = 0;
	innerlength = 0;
	}
}

void append_square(Figure *fig,double x,double y,char *file_name,int for_grid){
	FILE *fp = fopen(file_name,"a");

	if(for_grid == 0){
		
		fprintf(fp,"%lf %lf moveto\n",x + fig -> resolution / 2 - fig -> offset,y);
		fprintf(fp,"%lf %lf lineto\n",x + fig -> resolution / 2 - fig -> offset + length * cos(fig -> angle * PI / 180),y - length * sin(fig -> angle * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n",x + fig -> resolution,y - fig -> resolution / 2 - fig -> offset);

		fprintf(fp,"%lf %lf moveto\n",x + fig -> resolution,y - fig -> resolution / 2 + fig -> offset);
		fprintf(fp,"%lf %lf lineto\n",x + fig -> resolution / 2 - fig -> offset + length * cos(fig -> angle * PI / 180),y - fig -> resolution + length * sin(fig -> angle * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n",x + fig -> resolution / 2 - fig -> offset,y - fig -> resolution);

		fprintf(fp,"%lf %lf moveto\n",x + fig -> resolution / 2 + fig -> offset,y - fig -> resolution);
		fprintf(fp,"%lf %lf lineto\n",x + fig -> resolution / 2 + fig -> offset - length * cos(fig -> angle * PI / 180),y - fig -> resolution + length * sin(fig -> angle * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n",x,y - fig -> resolution / 2 + fig -> offset);

		fprintf(fp,"%lf %lf moveto\n",x,y - fig -> resolution / 2 - fig -> offset);
		fprintf(fp,"%lf %lf lineto\n",x + length * sin(fig -> angle * PI / 180),y - length * sin(fig -> angle * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n\n",x + fig -> resolution / 2 + fig -> offset,y);
	}
	else {
			
			fprintf(fp,"%lf %lf moveto\n",x,y);		// grid
			fprintf(fp,"%lf %lf lineto\n",x + fig -> resolution,y);
			fprintf(fp,"%lf %lf lineto\n",x + fig -> resolution,y - fig -> resolution);
			fprintf(fp,"%lf %lf lineto\n",x,y - fig -> resolution);
			fprintf(fp,"%lf %lf lineto\n",x,y);
			fprintf(fp,"stroke\n\n");
	}	
	fclose(fp);
}

void append_hexagon(Figure *fig,double x,double y,char *file_name,int for_grid){
	FILE *fp = fopen(file_name,"a");

	if(for_grid == 0){

		fprintf(fp,"%lf %lf moveto\n",x - (fig -> offset + fig -> resolution / 2) * cos(30 * PI / 180),y - (fig -> offset + fig -> resolution / 2) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\n",x ,y - length * sin((fig -> angle - 30) * PI / 180) - (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n",x + (fig -> offset + fig -> resolution / 2) * cos(30 * PI / 180),y - (fig -> offset + fig -> resolution / 2) * sin(30 * PI / 180));

		fprintf(fp,"%lf %lf moveto\n",x + (fig -> resolution / 2 - fig ->offset) * cos(30 * PI / 180),y - (fig -> resolution / 2 - fig ->offset) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\n",x + innerlength / 2 * sqrt(3),y - length * sin((fig -> angle - 30) * PI / 180) - (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180) - innerlength / 2);
		fprintf(fp,"%lf %lf lineto\nstroke\n",x + fig -> resolution * sqrt(3) / 2,y - fig -> resolution - fig -> offset);

		fprintf(fp,"%lf %lf moveto\n",x + fig -> resolution * sqrt(3) / 2,y - fig -> resolution + fig -> offset);
		fprintf(fp,"%lf %lf lineto\n",x + innerlength / 2 * sqrt(3),y - length * sin((fig -> angle - 30) * PI / 180) - (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180) - innerlength * 3 / 2);
		fprintf(fp,"%lf %lf lineto\nstroke\n",x + (fig -> resolution / 2 - fig ->offset) * cos(30 * PI / 180),y - fig -> resolution * 2 + (fig -> resolution / 2 - fig ->offset) * sin(30 * PI / 180));

		fprintf(fp,"%lf %lf moveto\n",x + (fig -> offset + fig -> resolution / 2) * cos(30 * PI / 180),y - fig -> resolution * 2 + (fig -> offset + fig -> resolution / 2) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\n",x,y - fig -> resolution * 2 +length * sin((fig -> angle - 30) * PI / 180) + (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\nstroke\n",x - (fig -> offset + fig -> resolution / 2) * cos(30 * PI / 180),y - fig -> resolution * 2 + (fig -> offset + fig -> resolution / 2) * sin(30 * PI / 180));
		
		fprintf(fp,"%lf %lf moveto\n",x - (fig -> resolution / 2 - fig ->offset) * cos(30 * PI / 180),y - fig -> resolution  * 2+ (fig -> resolution / 2 - fig ->offset) * sin(30 * PI / 180));
		fprintf(fp,"%lf %lf lineto\n",x - innerlength / 2 * sqrt(3),y - length * sin((fig -> angle - 30) * PI / 180) - (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180) - innerlength * 3 / 2);
		fprintf(fp,"%lf %lf lineto\nstroke\n",x - fig -> resolution * sqrt(3) / 2,y - fig -> resolution + fig -> offset);
		
		fprintf(fp,"%lf %lf moveto\n",x - fig -> resolution * sqrt(3) / 2,y - fig -> resolution - fig -> offset);
		fprintf(fp,"%lf %lf lineto\n",x - innerlength / 2 * sqrt(3),y - length * sin((fig -> angle - 30) * PI / 180) - (fig -> resolution / 2 + fig -> offset) * sin(30 * PI / 180) - innerlength / 2);
		fprintf(fp,"%lf %lf lineto\nstroke\n\n",x - (fig -> resolution / 2 - fig ->offset) * cos(30 * PI / 180),y - (fig -> resolution / 2 - fig ->offset) * sin(30 * PI / 180));
	}
	else{
		
		fprintf(fp,"%lf %lf moveto\n",x,y);		//grid
		fprintf(fp,"%lf %lf lineto\n",x + (fig -> resolution * sqrt(3) / 2),y - fig -> resolution / 2);
		fprintf(fp,"%lf %lf lineto\n",x + (fig -> resolution * sqrt(3) / 2),y - (fig -> resolution * 3 / 2));
		fprintf(fp,"%lf %lf lineto\n",x,y - 2 * fig -> resolution);
		fprintf(fp,"%lf %lf lineto\n",x - (fig -> resolution * sqrt(3) / 2),y - (fig -> resolution * 3 / 2));
		fprintf(fp,"%lf %lf lineto\n",x - (fig -> resolution * sqrt(3) / 2),y - fig -> resolution / 2);
		fprintf(fp,"%lf %lf lineto\n",x,y);
		fprintf(fp,"stroke\n\n");
	}
	fclose(fp);
}



void set_defaults(Figure *fig,char *defaults_file_name){
	FILE *fp = fopen(defaults_file_name,"r");
	if(fp == NULL) return;
	int j = 0,k = 0;
	char line[100],buffer[100];
	while(1){
		memset(line,0,100);
		memset(buffer,0,100);
		j = k = 0;
		while(line[j - 1] != ':' && line[j - 1] != 10 && line[j - 1] != '/' && !feof(fp)){
				line[j] = fgetc(fp);
				j++;
			}
		if(line[j - 1] == '/'){
			while(line[j - 1] != 10) line[j - 1] = fgetc(fp);
			continue;
		}
		if(feof(fp)) break;
		if(strstr(line,"background") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> backcolour . red = atof(buffer) / 255;
			
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> backcolour . green = atof(buffer) / 255;

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> backcolour . blue = atof(buffer) / 255;

		}
		else if(strstr(line,"foreground") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> colour . red = atof(buffer) / 255;
	
			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> colour . green = atof(buffer) / 255;

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> colour . blue = atof(buffer) / 255;
		}
		else if(strstr(line,"grid_color") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> gridcolour . red = atof(buffer) / 255;

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> gridcolour . green = atof(buffer) / 255;

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> gridcolour . blue = atof(buffer) / 255;

		}
		else if(strstr(line,"offset") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> angle = atof(buffer);

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> offset = atof(buffer);
		}
		else if(strstr(line,"canvas") != NULL){
			fgetc(fp);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ',');
			buffer[k - 1] = 0;
			fig -> width = atof(buffer);

			k = 0;
			memset(buffer,0,100);
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != ')');
			buffer[k - 1] = 0;
			fig -> height = atof(buffer);
		}
		else if(strstr(line,"pattern_thickness") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != '/' );
			if(buffer[k - 1] == 10) fgetc(fp);
			buffer[k - 1] = 0;
			fig -> thickness = atof(buffer);
		}
		else if(strstr(line,"grid_thickness") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != '/' && buffer[k - 1] != 10);
			if(buffer[k - 1] == 10) fgetc(fp);
			buffer[k - 1] = 0;
			fig -> gridthickness = atof(buffer);

		}
		else if(strstr(line,"tile_size") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != '/' && buffer[k - 1] != 10);
			if(buffer[k - 1] == 10) fgetc(fp);
			buffer[k - 1] = 0;
			fig -> resolution = atof(buffer);
		}
		else if(strstr(line,"show_grid") != NULL){
			do{
				buffer[k] = fgetc(fp);
				k++;
			}while(buffer[k - 1] != '/');
			buffer[k - 1] = 0;
			if(strstr(buffer,"False") != NULL) fig -> show_grid = 0;
			else fig -> show_grid = 1;
		}

	}

	fclose(fp);
}
