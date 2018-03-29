#ifndef __IUTIL_H_
#define __IUTIL_H_

#include "convert.h"
#define ENCODE 1111
#define DECODE 2222
#define NOPE 	0
/* ----------------------------------------------------------------------- */

#define J2K_CFMT 0
#define JP2_CFMT 1
#define JPT_CFMT 2

#define PXM_DFMT 10
#define PGX_DFMT 11
#define BMP_DFMT 12
#define YUV_DFMT 13
#define TIF_DFMT 14
#define RAW_DFMT 15
#define TGA_DFMT 16

void help_display();
int parse_cmdline_coder(int argc, char **argv, opj_cparameters_t *parameters,raw_cparameters_t *raw_cp, 
													char *indexfilename);
int parse_cmdline_decoder(int argc, char **argv, opj_dparameters_t *parameters, char *indexfilename); 
#endif