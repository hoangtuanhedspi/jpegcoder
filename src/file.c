#include <stdlib.h>
#include <stdio.h>
#include <openjpeg.h>
#include <libgen.h>
#include <string.h>
#include "util.h"
#include "file.h"

char* open_img_source(char* file_path,long* length){
    FILE *reader;
    unsigned char *src;
    reader = fopen(file_path, "rb");
    if(!reader){
        printf("Can't open file\n");
    }else{
        printf("File [%s] opened!\n",file_path);
    }

    fseek(reader, 0, SEEK_END);
	*length = ftell(reader);
	fseek(reader, 0, SEEK_SET);
	src = (unsigned char*) malloc(*length);
    printf("\nlen:%u\n",*length);
	fread(src, 1, *length, reader);
	fclose(reader);
    return src;
}

int get_file_format(char *filename) {
	unsigned int i;
	static const char *extension[] = {
    "pgx", "pnm", "pgm", "ppm", "bmp", "tif", "raw", "tga", "j2k", "jp2", "j2c"
    };
	static const int format[] = {
    PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT, TIF_DFMT, RAW_DFMT, TGA_DFMT, J2K_CFMT, JP2_CFMT, J2K_CFMT
    };
	char * ext = strrchr(filename, '.');
	if (ext == NULL)
		return -1;
	ext++;
	for(i = 0; i < sizeof(format)/sizeof(*format); i++) {
		if(strncasecmp(ext, extension[i], 3) == 0) {
			return format[i];
		}
	}
	return -1;
}

char * get_file_name(char *name){
	return basename(name);
}