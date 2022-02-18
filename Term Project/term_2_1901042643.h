#ifndef gay
#define gay
#include "term1901042643.h"

void read_file(Figure *fig,char *file_name);
void set_defaults(Figure *fig,char *defaults_file_name);
void export_islamic_eps(Figure *fig,char *file_name);
void append_square(Figure *fig,double x,double y,char *file_name,int for_grid);
void append_hexagon(Figure *fig,double x,double y,char *file_name,int for_grid);
#endif