#include <stdlib.h>
#include <stdio.h>
#include <openjpeg.h>
#include <string.h>
#include "getopt.h"
#include "util.h"
#include "file.h"

void help_display() {
	fprintf(stdout,"HELP\n----\n\n");
	fprintf(stdout,"- the -h option displays this help information on screen\n\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"REMARKS:\n");
	fprintf(stdout,"---------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
	fprintf(stdout,"COD and QCD never appear in the tile_header.\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"By default:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout," * Lossless\n");
	fprintf(stdout," * 1 tile\n");
	fprintf(stdout," * Size of precinct : 2^15 x 2^15 (means 1 precinct)\n");
	fprintf(stdout," * Size of code-block : 64 x 64\n");
	fprintf(stdout," * Number of resolutions: 6\n");
	fprintf(stdout," * No SOP marker in the codestream\n");
	fprintf(stdout," * No EPH marker in the codestream\n");
	fprintf(stdout," * No sub-sampling in x or y direction\n");
	fprintf(stdout," * No mode switch activated\n");
	fprintf(stdout," * Progression order: LRCP\n");
	fprintf(stdout," * No index file\n");
	fprintf(stdout," * No ROI upshifted\n");
	fprintf(stdout," * No offset of the origin of the image\n");
	fprintf(stdout," * No offset of the origin of the tiles\n");
	fprintf(stdout," * Reversible DWT 5-3\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Parameters:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Required Parameters (except with -h):\n");
	fprintf(stdout,"Options -i must be used\n");
	fprintf(stdout,"-i           : source file  (-i source.pnm also *.pgm, *.ppm, *.bmp, *.tif, *.raw, *.tga) \n");
	fprintf(stdout,"    When using this option -o must be used\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-o           : destination file (-o dest.j2k or .jp2) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Optional Parameters:\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-h           : display the help information \n ");
	fprintf(stdout,"\n");
	fprintf(stdout,"-r           : different compression ratios for successive layers (-r 20,10,5)\n ");
	fprintf(stdout,"	         - The rate specified for each quality level is the desired \n");
	fprintf(stdout,"	           compression factor.\n");
	fprintf(stdout,"		        Example: -r 20,10,1 means quality 1: compress 20x, \n");
	fprintf(stdout,"		                quality 2: compress 10x and quality 3: compress lossless\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");
	fprintf(stdout,"\n");
	fprintf(stdout,"-q           : different psnr for successive layers (-q 30,40,50) \n ");
	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");
	fprintf(stdout,"\n");
	fprintf(stdout,"-n           : number of resolutions (-n 3) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-b           : size of code block (-b 32,32) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-c           : size of precinct (-c 128,128) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-t           : size of tile (-t 512,512) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-p           : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-s           : subsampling factor (-s 2,2) [-s X,Y] \n");
	fprintf(stdout,"	           Remark: subsampling bigger than 2 can produce error\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-POC         : Progression order change (-POC T1=0,0,1,5,3,CPRL/T1=5,0,1,6,3,CPRL) \n");
	fprintf(stdout,"               Example: T1=0,0,1,5,3,CPRL \n");
	fprintf(stdout,"			 : Ttilenumber=Resolution num start,Component num start,Layer num end,Resolution num end,Component num end,Progression order\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-SOP         : write SOP marker before each packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-EPH         : write EPH marker after each header packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-M           : mode switch (-M 3) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
	fprintf(stdout,"                 8=VSC 16=ERTERM(SEGTERM) 32=SEGMARK(SEGSYM)] \n");
	fprintf(stdout,"                 Indicate multiple modes by adding their values. \n");
	fprintf(stdout,"                 ex: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
	fprintf(stdout,"-ROI         : c=%%d,U=%%d : quantization indices upshifted \n");
	fprintf(stdout,"               for component c=%%d [%%d = 0,1,2]\n");
	fprintf(stdout,"               with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI c=0,U=25) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-d           : offset of the origin of the image (-d 150,300) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-T           : offset of the origin of the tiles (-T 100,75) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-I           : use the irreversible DWT 9-7 (-I) \n");
	fprintf(stdout,"\n");
}

void decode_help_display() {
	fprintf(stdout,"HELP\n----\n\n");
	fprintf(stdout,"- the -h option displays this help information on screen\n\n");
	fprintf(stdout,"List of parameters for the JPEG 2000 decoder:\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"  -i <compressed file>\n");
	fprintf(stdout,"    REQUIRED only if an Input image directory not specified\n");
	fprintf(stdout,"    Currently accepts J2K-files, JP2-files and JPT-files. The file type\n");
	fprintf(stdout,"    is identified based on its suffix.\n");
	fprintf(stdout,"  -o <decompressed file>\n");
	fprintf(stdout,"    REQUIRED\n");
	fprintf(stdout,"    Currently accepts PGM, PPM, PNM, PGX, BMP, TIF, RAW and TGA files\n");
	fprintf(stdout,"    Binary data is written to the file (not ascii). If a PGX\n");
	fprintf(stdout,"    filename is given, there will be as many output files as there are\n");
	fprintf(stdout,"    components: an indice starting from 0 will then be appended to the\n");
	fprintf(stdout,"    output filename, just before the \"pgx\" extension. If a PGM filename\n");
	fprintf(stdout,"    is given and there are more than one component, only the first component\n");
	fprintf(stdout,"    will be written to the file.\n");
	fprintf(stdout,"  -r <reduce factor>\n");
	fprintf(stdout,"    Set the number of highest resolution levels to be discarded. The\n");
	fprintf(stdout,"    image resolution is effectively divided by 2 to the power of the\n");
	fprintf(stdout,"    number of discarded levels. The reduce factor is limited by the\n");
	fprintf(stdout,"    smallest total number of decomposition levels among tiles.\n");
	fprintf(stdout,"  -l <number of quality layers to decode>\n");
	fprintf(stdout,"    Set the maximum number of quality layers to decode. If there are\n");
	fprintf(stdout,"    less quality layers than the specified number, all the quality layers\n");
	fprintf(stdout,"    are decoded.\n");
	fprintf(stdout,"\n");
}

OPJ_PROG_ORDER give_progression(char progression[4]) {
	if(strncmp(progression, "LRCP", 4) == 0) {
		return LRCP;
	}
	if(strncmp(progression, "RLCP", 4) == 0) {
		return RLCP;
	}
	if(strncmp(progression, "RPCL", 4) == 0) {
		return RPCL;
	}
	if(strncmp(progression, "PCRL", 4) == 0) {
		return PCRL;
	}
	if(strncmp(progression, "CPRL", 4) == 0) {
		return CPRL;
	}

	return PROG_UNKNOWN;
}

int parse_cmdline_coder(int argc, char **argv, opj_cparameters_t *parameters,raw_cparameters_t *raw_cp, 
													char *indexfilename) {
	int i, j,totlen;
	option_t long_option[]={
		{"TP",REQ_ARG, NULL ,'v'},
		{"SOP",NO_ARG, NULL ,'S'},
		{"EPH",NO_ARG, NULL ,'E'},
		{"POC",REQ_ARG, NULL ,'P'},
		{"ROI",REQ_ARG, NULL ,'R'},
	};

	/* parse the command line */
	const char optlist[] = "i:o:hr:q:n:b:c:t:p:s:SEM:x:R:d:T:If:P:C:F:";

	totlen=sizeof(long_option);
	raw_cp->rawWidth = 0;

	while (1) {
    int c = getopt_long(argc, argv, optlist,long_option,totlen);
		if (c == -1)
			break;
		switch (c) {
			case 'i':			/* input file */
			{
				char *infile = optarg;
				parameters->decod_format = get_file_format(infile);
				switch(parameters->decod_format) {
					case PGX_DFMT:
					case PXM_DFMT:
					case BMP_DFMT:
					case TIF_DFMT:
					case RAW_DFMT:
					case TGA_DFMT:
						break;
					default:
						fprintf(stderr,
							"!! Unrecognized format for infile : %s "
              "[accept only *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.tif, *.raw or *.tga] !!\n\n", 
							infile);
						return 1;
				}
				strncpy(parameters->infile, infile, sizeof(parameters->infile)-1);
			}
			break;

				/* ----------------------------------------------------- */

			case 'o':			/* output file */
			{
				char *outfile = optarg;
				parameters->cod_format = get_file_format(outfile);
				switch(parameters->cod_format) {
					case J2K_CFMT:
					case JP2_CFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.j2k, *.j2c or *.jp2]!! \n", outfile);
						return 1;
				}
				strncpy(parameters->outfile, outfile, sizeof(parameters->outfile)-1);
			}
			break;

				/* ----------------------------------------------------- */
			case 'O':			/* output format */
				{
					char outformat[50];
					char *of = optarg;
					sprintf(outformat,".%s",of);
					parameters->cod_format = get_file_format(outformat);
					switch(parameters->cod_format) {
						case J2K_CFMT:
						case JP2_CFMT:
							break;
						default:
							fprintf(stderr, "Unknown output format image [only j2k, j2c, jp2]!! \n");
							return 1;
					}
				}
				break;


				/* ----------------------------------------------------- */


			case 'r':			/* rates rates/distorsion */
			{
				char *s = optarg;
				while (sscanf(s, "%f", &parameters->tcp_rates[parameters->tcp_numlayers]) == 1) {
					parameters->tcp_numlayers++;
					while (*s && *s != ',') {
						s++;
					}
					if (!*s)
						break;
					s++;
				}
				parameters->cp_disto_alloc = 1;
			}
			break;

				/* ----------------------------------------------------- */

			
			case 'F':			/* Raw image format parameters */
			{
				char signo;
				char *s = optarg;
				if (sscanf(s, "%d,%d,%d,%d,%c", &raw_cp->rawWidth, &raw_cp->rawHeight, &raw_cp->rawComp, &raw_cp->rawBitDepth, &signo) == 5) {
					if (signo == 's') {
						raw_cp->rawSigned = true;
						fprintf(stdout,"\nRaw file parameters: %d,%d,%d,%d Signed\n", raw_cp->rawWidth, raw_cp->rawHeight, raw_cp->rawComp, raw_cp->rawBitDepth);
					}
					else if (signo == 'u') {
						raw_cp->rawSigned = false;
						fprintf(stdout,"\nRaw file parameters: %d,%d,%d,%d Unsigned\n", raw_cp->rawWidth, raw_cp->rawHeight, raw_cp->rawComp, raw_cp->rawBitDepth);
					}
					else {
						fprintf(stderr,"\nError: invalid raw image parameters: Unknown sign of raw file\n");
						fprintf(stderr,"Please use the Format option -F:\n");
						fprintf(stderr,"-F rawWidth,rawHeight,rawComp,rawBitDepth,s/u (Signed/Unsigned)\n");
						fprintf(stderr,"Example: -i lena.raw -o lena.j2k -F 512,512,3,8,u\n");
						fprintf(stderr,"Aborting\n");
					}					
				}
				else {
					fprintf(stderr,"\nError: invalid raw image parameters\n");
					fprintf(stderr,"Please use the Format option -F:\n");
					fprintf(stderr,"-F rawWidth,rawHeight,rawComp,rawBitDepth,s/u (Signed/Unsigned)\n");
						fprintf(stderr,"Example: -i lena.raw -o lena.j2k -F 512,512,3,8,u\n");
					fprintf(stderr,"Aborting\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 'q':			/* add fixed_quality */
			{
				char *s = optarg;
				while (sscanf(s, "%f", &parameters->tcp_distoratio[parameters->tcp_numlayers]) == 1) {
					parameters->tcp_numlayers++;
					while (*s && *s != ',') {
						s++;
					}
					if (!*s)
						break;
					s++;
				}
				parameters->cp_fixed_quality = 1;
			}
			break;

				/* dda */
				/* ----------------------------------------------------- */

			case 'f':			/* mod fixed_quality (before : -q) */
			{
				int *row = NULL, *col = NULL;
				int numlayers = 0, numresolution = 0, matrix_width = 0;

				char *s = optarg;
				sscanf(s, "%d", &numlayers);
				s++;
				if (numlayers > 9)
					s++;

				parameters->tcp_numlayers = numlayers;
				numresolution = parameters->numresolution;
				matrix_width = numresolution * 3;
				parameters->cp_matrice = (int *) malloc(numlayers * matrix_width * sizeof(int));
				s = s + 2;

				for (i = 0; i < numlayers; i++) {
					row = &parameters->cp_matrice[i * matrix_width];
					col = row;
					parameters->tcp_rates[i] = 1;
					sscanf(s, "%d,", &col[0]);
					s += 2;
					if (col[0] > 9)
						s++;
					col[1] = 0;
					col[2] = 0;
					for (j = 1; j < numresolution; j++) {
						col += 3;
						sscanf(s, "%d,%d,%d", &col[0], &col[1], &col[2]);
						s += 6;
						if (col[0] > 9)
							s++;
						if (col[1] > 9)
							s++;
						if (col[2] > 9)
							s++;
					}
					if (i < numlayers - 1)
						s++;
				}
				parameters->cp_fixed_alloc = 1;
			}
			break;

				/* ----------------------------------------------------- */

			case 't':			/* tiles */
			{
				sscanf(optarg, "%d,%d", &parameters->cp_tdx, &parameters->cp_tdy);
				parameters->tile_size_on = true;
			}
			break;

				/* ----------------------------------------------------- */

			case 'n':			/* resolution */
			{
				sscanf(optarg, "%d", &parameters->numresolution);
			}
			break;

				/* ----------------------------------------------------- */
			case 'c':			/* precinct dimension */
			{
				char sep;
				int res_spec = 0;

				char *s = optarg;
				do {
					sep = 0;
					sscanf(s, "[%d,%d]%c", &parameters->prcw_init[res_spec],
                                 &parameters->prch_init[res_spec], &sep);
					parameters->csty |= 0x01;
					res_spec++;
					s = strpbrk(s, "]") + 2;
				}
				while (sep == ',');
				parameters->res_spec = res_spec;
			}
			break;

				/* ----------------------------------------------------- */

			case 'b':			/* code-block dimension */
			{
				int cblockw_init = 0, cblockh_init = 0;
				sscanf(optarg, "%d,%d", &cblockw_init, &cblockh_init);
				if (cblockw_init * cblockh_init > 4096 || cblockw_init > 1024
					|| cblockw_init < 4 || cblockh_init > 1024 || cblockh_init < 4) {
					fprintf(stderr,
						"!! Size of code_block error (option -b) !!\n\nRestriction :\n"
            "    * width*height<=4096\n    * 4<=width,height<= 1024\n\n");
					return 1;
				}
				parameters->cblockw_init = cblockw_init;
				parameters->cblockh_init = cblockh_init;
			}
			break;

				/* ----------------------------------------------------- */

			case 'x':			/* creation of index file */
			{
				char *index = optarg;
				strncpy(indexfilename, index, OPJ_PATH_LEN);
			}
			break;

				/* ----------------------------------------------------- */

			case 'p':			/* progression order */
			{
				char progression[4];

				strncpy(progression, optarg, 4);
				parameters->prog_order = give_progression(progression);
				if (parameters->prog_order == -1) {
					fprintf(stderr, "Unrecognized progression order "
            "[LRCP, RLCP, RPCL, PCRL, CPRL] !!\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 's':			/* subsampling factor */
			{
				if (sscanf(optarg, "%d,%d", &parameters->subsampling_dx,
                                    &parameters->subsampling_dy) != 2) {
					fprintf(stderr,	"'-s' sub-sampling argument error !  [-s dx,dy]\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 'd':			/* coordonnate of the reference grid */
			{
				if (sscanf(optarg, "%d,%d", &parameters->image_offset_x0,
                                    &parameters->image_offset_y0) != 2) {
					fprintf(stderr,	"-d 'coordonnate of the reference grid' argument "
            "error !! [-d x0,y0]\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 'h':			/* display an help description */
				help_display();
				return 1;

				/* ----------------------------------------------------- */

			case 'P':			/* POC */
			{
				int numpocs = 0;		/* number of progression order change (POC) default 0 */
				opj_poc_t *POC = NULL;	/* POC : used in case of Progression order change */

				char *s = optarg;
				POC = parameters->POC;

				while (sscanf(s, "T%d=%d,%d,%d,%d,%d,%4s", &POC[numpocs].tile,
					&POC[numpocs].resno0, &POC[numpocs].compno0,
					&POC[numpocs].layno1, &POC[numpocs].resno1,
					&POC[numpocs].compno1, &POC[numpocs].progorder) == 7) {
					POC[numpocs].prg1 = give_progression(POC[numpocs].progorder);
					numpocs++;
					while (*s && *s != '/') {
						s++;
					}
					if (!*s) {
						break;
					}
					s++;
				}
				parameters->numpocs = numpocs;
			}
			break;

				/* ------------------------------------------------------ */

			case 'S':			/* SOP marker */
			{
				parameters->csty |= 0x02;
			}
			break;

				/* ------------------------------------------------------ */

			case 'E':			/* EPH marker */
			{
				parameters->csty |= 0x04;
			}
			break;

				/* ------------------------------------------------------ */

			case 'M':			/* Mode switch pas tous au point !! */
			{
				int value = 0;
				if (sscanf(optarg, "%d", &value) == 1) {
					for (i = 0; i <= 5; i++) {
						int cache = value & (1 << i);
						if (cache)
							parameters->mode |= (1 << i);
					}
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'R':			/* ROI */
			{
				if (sscanf(optarg, "c=%d,U=%d", &parameters->roi_compno,
                                           &parameters->roi_shift) != 2) {
					fprintf(stderr, "ROI error !! [-ROI c='compno',U='shift']\n");
					return 1;
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'T':			/* Tile offset */
			{
				if (sscanf(optarg, "%d,%d", &parameters->cp_tx0, &parameters->cp_ty0) != 2) {
					fprintf(stderr, "-T 'tile offset' argument error !! [-T X0,Y0]");
					return 1;
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'C':			/* add a comment */
			{
				parameters->cp_comment = (char*)malloc(strlen(optarg) + 1);
				if(parameters->cp_comment) {
					strcpy(parameters->cp_comment, optarg);
				}
			}
			break;


				/* ------------------------------------------------------ */

			case 'I':			/* reversible or not */
			{
				parameters->irreversible = 1;
			}
			break;

			/* ------------------------------------------------------ */
			
			case 'v':			/* Tile part generation*/
			{
				parameters->tp_flag = optarg[0];
				parameters->tp_on = 1;
			}
			break;	
			default:
				fprintf(stderr, "ERROR -> Command line not valid\n");
				return 1;
		}
	}

    if((parameters->infile[0] == 0) || (parameters->outfile[0] == 0)) {
        fprintf(stderr, "Error: One of the options; -i or -ImgDir must be specified\n");
        fprintf(stderr, "Error: When using -i; -o must be used\n");
        fprintf(stderr, "usage: image_to_j2k -i image-file -o j2k/jp2-file (+ options)\n");
        return 1;
    }

	if (parameters->decod_format == RAW_DFMT && raw_cp->rawWidth == 0) {
			fprintf(stderr,"\nError: invalid raw image parameters\n");
			fprintf(stderr,"Please use the Format option -F:\n");
			fprintf(stderr,"-F rawWidth,rawHeight,rawComp,rawBitDepth,s/u (Signed/Unsigned)\n");
						fprintf(stderr,"Example: -i lena.raw -o lena.j2k -F 512,512,3,8,u\n");
			fprintf(stderr,"Aborting\n");
			return 1;
	}

	if ((parameters->cp_disto_alloc || parameters->cp_fixed_alloc || parameters->cp_fixed_quality)
		&& (!(parameters->cp_disto_alloc ^ parameters->cp_fixed_alloc ^ parameters->cp_fixed_quality))) {
		fprintf(stderr, "Error: options -r -q and -f cannot be used together !!\n");
		return 1;
	}				/* mod fixed_quality */

	/* if no rate entered, lossless by default */
	if (parameters->tcp_numlayers == 0) {
		parameters->tcp_rates[0] = 0;	/* MOD antonin : losslessbug */
		parameters->tcp_numlayers++;
		parameters->cp_disto_alloc = 1;
	}

	if((parameters->cp_tx0 > parameters->image_offset_x0) || (parameters->cp_ty0 > parameters->image_offset_y0)) {
		fprintf(stderr,
			"Error: Tile offset dimension is unnappropriate --> TX0(%d)<=IMG_X0(%d) TYO(%d)<=IMG_Y0(%d) \n",
			parameters->cp_tx0, parameters->image_offset_x0, parameters->cp_ty0, parameters->image_offset_y0);
		return 1;
	}

	for (i = 0; i < parameters->numpocs; i++) {
		if (parameters->POC[i].prg == -1) {
			fprintf(stderr,
				"Unrecognized progression order in option -P (POC n %d) [LRCP, RLCP, RPCL, PCRL, CPRL] !!\n",
				i + 1);
		}
	}

	return 0;
}

int parse_cmdline_decoder(int argc, char **argv, opj_dparameters_t *parameters, char *indexfilename) {
	const char optlist[] = "i:o:r:l:hx:";
	while (1) {
		int c = getopt(argc, argv,optlist);
		if (c == -1)
			break;
		switch (c) {
			case 'i':			/* input file */
			{
				char *infile = optarg;
				parameters->decod_format = get_file_format(infile);
				switch(parameters->decod_format) {
					case J2K_CFMT:
					case JP2_CFMT:
					case JPT_CFMT:
						break;
					default:
						fprintf(stderr, 
							"!! Unrecognized format for infile : %s [accept only *.j2k, *.jp2, *.jpc or *.jpt] !!\n\n", 
							infile);
						return 1;
				}
				strncpy(parameters->infile, infile, sizeof(parameters->infile)-1);
			}
			break;
				
				/* ----------------------------------------------------- */

			case 'o':			/* output file */
			{
				char *outfile = optarg;
				parameters->cod_format = get_file_format(outfile);
				switch(parameters->cod_format) {
					case PGX_DFMT:
					case PXM_DFMT:
					case BMP_DFMT:
					case TIF_DFMT:
					case RAW_DFMT:
					case TGA_DFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.raw or *.tga]!! \n", outfile);
						return 1;
				}
				strncpy(parameters->outfile, outfile, sizeof(parameters->outfile)-1);
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'O':			/* output format */
			{
				char outformat[50];
				char *of = optarg;
				sprintf(outformat,".%s",of);
				parameters->cod_format = get_file_format(outformat);
				switch(parameters->cod_format) {
					case PGX_DFMT:
					case PXM_DFMT:
					case BMP_DFMT:
					case TIF_DFMT:
					case RAW_DFMT:
					case TGA_DFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.raw or *.tga]!! \n", outformat);
						return 1;
						break;
				}
			}
			break;

				/* ----------------------------------------------------- */


			case 'r':		/* reduce option */
			{
				sscanf(optarg, "%d", &parameters->cp_reduce);
			}
			break;
			
				/* ----------------------------------------------------- */
      

			case 'l':		/* layering option */
			{
				sscanf(optarg, "%d", &parameters->cp_layer);
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'h': 			/* display an help description */
				decode_help_display();
				return 1;
				/* ----------------------------------------------------- */
			default:
				fprintf(stderr,"WARNING -> this option is not valid \"-%c %s\"\n",c, optarg);
				break;
		}
	}

	if((parameters->infile[0] == 0) || (parameters->outfile[0] == 0)) {
		fprintf(stderr, "Error: One of the options -i or -ImgDir must be specified\n");
		fprintf(stderr, "Error: When using -i, -o must be used\n");
		fprintf(stderr, "usage: image_to_j2k -i *.j2k/jp2/j2c -o *.pgm/ppm/pnm/pgx/bmp/tif/raw/tga(+ options)\n");
		return 1;
	}

	return 0;
}