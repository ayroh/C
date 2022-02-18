#ifndef term1901042643
#define term1901042643

typedef struct Point2D{
	double x,y;
	struct Point2D *next;
}Point2D;

typedef struct Color{
	double red,green,blue;
}Color;

typedef struct Tree{
	int data;
	struct Tree *left;
	struct Tree *right;
}Tree;

typedef struct Figure{
	double width;		// x
	double height;		// y
	double thickness,gridthickness;	// setlinewidth
	double resolution;	// minimum length
	double angle,offset;
	int type,show_grid;
	Color colour,backcolour,gridcolour;
	Point2D *pt;
	Tree *tre;
}Figure;


Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure * fig, double thickness, double resolution);
void set_color(Figure * fig, Color c);
void draw_fx(Figure * fig, double f(double x),double start_x, double end_x,double step_size);
void draw_polyline(Point2D * poly_line, int n,double resolution,int is_it_test);
void draw_polygon(Point2D * poly_line,double resolution,int is_it_test);
void draw_ellipse(Point2D * center, Point2D * width_height,int is_it_test);
void draw_binary_tree(Tree * root);
void scale_figure(double scale_x, double scale_y,char *file_name);
void resize_figure(Point2D *start_roi, Point2D *end_roi,char *file_name);
/*void append_figures(Figure * fig1, Figure * fig2);*/
void export_eps(Figure * fig, char * file_name);
void export_tree_eps(Tree *tre,char *file_name,int type,int	x,int y,double radius);
#endif
