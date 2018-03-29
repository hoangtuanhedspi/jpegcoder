#include <openjpeg.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <compress/util.h>
#include <compress/file.h>
#include <compress/convert.h>

int main(int argc,char* argv[]){
	bool bSuccess;
	opj_dparameters_t parameters;
	opj_image_t *image = NULL;
	opj_codestream_info_t cstr_info;
    opj_dinfo_t* dinfo = NULL;
	opj_cio_t *cio = NULL;
    FILE *fsrc = NULL;
	unsigned char *src = NULL;
	int file_length;


    char input_file_name[OPJ_PATH_LEN];
    opj_set_default_decoder_parameters(&parameters);
	*input_file_name = 0;

    if(parse_cmdline_decoder(argc, argv, &parameters,input_file_name) == 1) {
		return 1;
	}


    fsrc = fopen(parameters.infile, "rb");
    if (!fsrc) {
        fprintf(stderr, "ERROR -> failed to open %s for reading\n", parameters.infile);
        return 1;
    }

    fseek(fsrc, 0, SEEK_END);
    file_length = ftell(fsrc);
    fseek(fsrc, 0, SEEK_SET);
    src = (unsigned char *) malloc(file_length);
    fread(src, 1, file_length, fsrc);
    fclose(fsrc);
    switch(parameters.decod_format) {
        case J2K_CFMT:
        {
            dinfo = opj_create_decompress(CODEC_J2K);
            opj_setup_decoder(dinfo, &parameters);
            cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

            
            if (*input_file_name)				
                image = opj_decode_with_info(dinfo, cio, &cstr_info);
            else
                image = opj_decode(dinfo, cio);
            if(!image) {
                fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
                opj_destroy_decompress(dinfo);
                opj_cio_close(cio);
                return 1;
            }

            opj_cio_close(cio);

        }
        break;

        case JP2_CFMT:
        {
            
            dinfo = opj_create_decompress(CODEC_JP2);
            opj_setup_decoder(dinfo, &parameters);

            cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

            if (*input_file_name)
                image = opj_decode_with_info(dinfo, cio, &cstr_info);
            else
                image = opj_decode(dinfo, cio);			
            if(!image) {
                fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
                opj_destroy_decompress(dinfo);
                opj_cio_close(cio);
                return 1;
            }

            opj_cio_close(cio);
        }
        break;

        case JPT_CFMT:
        {

            dinfo = opj_create_decompress(CODEC_JPT);


            opj_setup_decoder(dinfo, &parameters);

            cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

            if (*input_file_name)				
                image = opj_decode_with_info(dinfo, cio, &cstr_info);
            else
                image = opj_decode(dinfo, cio);
            if(!image) {
                fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
                opj_destroy_decompress(dinfo);
                opj_cio_close(cio);
                return 1;
            }

            opj_cio_close(cio);

        }
        break;

        default:
            fprintf(stderr, "skipping file..\n");
    }

    free(src);
    src = NULL;
    switch (parameters.cod_format) {
        case PXM_DFMT:			/* PNM PGM PPM */
            if (imagetopnm(image, parameters.outfile)) {
                fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
            }
            else {
                fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
            }
            break;

        case PGX_DFMT:			/* PGX */
            if(imagetopgx(image, parameters.outfile)){
                fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
            }
            else {
                fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
            }
            break;

        case BMP_DFMT:			/* BMP */
            if(imagetobmp(image, parameters.outfile)){
                fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
            }
            else {
                fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
            }
            break;

        case RAW_DFMT:			/* RAW */
            if(imagetoraw(image, parameters.outfile)){
                fprintf(stdout,"Error generating raw file. Outfile %s not generated\n",parameters.outfile);
            }
            else {
                fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
            }
            break;

        case TGA_DFMT:			/* TGA */
            if(imagetotga(image, parameters.outfile)){
                fprintf(stdout,"Error generating tga file. Outfile %s not generated\n",parameters.outfile);
            }
            else {
                fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
            }
            break;
    }

    if(dinfo) {
        opj_destroy_decompress(dinfo);
    }

    if (*input_file_name)	
        opj_destroy_cstr_info(&cstr_info);
    opj_image_destroy(image);
	return 0;
}