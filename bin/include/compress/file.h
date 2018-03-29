#ifndef __IFILE_H_
#define __IFILE_H_


char* open_img_source(char* file_path,long* length);
int get_file_format(char *filename);
char * get_file_name(char *name);
#endif