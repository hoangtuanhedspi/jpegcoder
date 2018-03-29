#include <openjpeg.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <compress/util.h>
#include <compress/file.h>
#include <compress/convert.h>

int main(int argc,char* argv[]){
	bool bSuccess;
	opj_cparameters_t cparameters;
	opj_image_t *image = NULL;
	raw_cparameters_t raw_cp;
	opj_codestream_info_t cstr_info;

    char input_file_name[OPJ_PATH_LEN];
    opj_set_default_encoder_parameters(&cparameters);
	/* Initialize input_file_name and img_fol */
	*input_file_name = 0;

    if(parse_cmdline_coder(argc, argv, &cparameters,&raw_cp, input_file_name) == 1) {
		return 1;
	}
    

    if(cparameters.cp_comment == NULL) {
        const char comment[] = "Created by ICompress version ";
            const size_t clen = strlen(comment);
        const char *version = opj_version();
        cparameters.cp_comment = (char*)malloc(clen+strlen(version)+1);
        sprintf(cparameters.cp_comment,"%s%s", comment, version);
	}

    switch(cparameters.decod_format) {
        case PGX_DFMT:
            break;
        case PXM_DFMT:
            break;
        case BMP_DFMT:
            break;
        case TIF_DFMT:
            break;
        case RAW_DFMT:
            break;
        case TGA_DFMT:
            break;
        default:
            fprintf(stderr,"skipping file...\n");
        goto end;		
	}

    switch (cparameters.decod_format) {
            case PGX_DFMT:
                image = pgxtoimage(cparameters.infile, &cparameters);
                if (!image) {
                    fprintf(stderr, "Unable to load pgx file\n");
                    return 1; 
                }
                break;

            case PXM_DFMT:
                image = pnmtoimage(cparameters.infile, &cparameters);
                if (!image) {
                    fprintf(stderr, "Unable to load pnm file\n");
                    return 1;
                }
                break;

            case BMP_DFMT:
                image = bmptoimage(cparameters.infile, &cparameters);
                if (!image) {
                    fprintf(stderr, "Unable to load bmp file\n");
                    return 1;
                }
                break;
        
            case RAW_DFMT:
                image = rawtoimage(cparameters.infile, &cparameters, &raw_cp);
                if (!image) {
                    fprintf(stderr, "Unable to load raw file\n");
                    return 1;
                }
            break;

            case TGA_DFMT:
                image = tgatoimage(cparameters.infile, &cparameters);
                if (!image) {
                    fprintf(stderr, "Unable to load tga file\n");
                    return 1;
                }
            break;
	}

    cparameters.tcp_mct = image->numcomps == 3 ? 1 : 0;
    if (cparameters.cod_format == J2K_CFMT) {	/* J2K format output */
        int codestream_length;
        opj_cio_t *cio = NULL;
        FILE *f = NULL;

        /* get a J2K compressor handle */
        opj_cinfo_t* cinfo = opj_create_compress(CODEC_J2K);

        /* setup the encoder parameters using the current image and user parameters */
        opj_setup_encoder(cinfo, &cparameters, image);

        /* open a byte stream for writing */
        /* allocate memory for all tiles */
        cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

        /* encode the image */
        if (*input_file_name)					// If need to extract codestream information
            bSuccess = opj_encode_with_info(cinfo, cio, image, &cstr_info);
        else
            bSuccess = opj_encode(cinfo, cio, image, NULL);
        if (!bSuccess) {
            opj_cio_close(cio);
            fprintf(stderr, "failed to encode image\n");
            return 1;
        }
        codestream_length = cio_tell(cio);

        /* write the buffer to disk */
        f = fopen(cparameters.outfile, "wb");
        if (!f) {
            fprintf(stderr, "failed to open %s for writing\n", cparameters.outfile);
            return 1;
        }
        fwrite(cio->buffer, 1, codestream_length, f);
        fclose(f);

        fprintf(stderr,"Generated outfile %s\n",cparameters.outfile);
        /* close and free the byte stream */
        opj_cio_close(cio);

        /* Write the index to disk */
        // if (*input_file_name) {
        // 	bSuccess = write_index_file(&cstr_info, input_file_name);
        // 	if (bSuccess) {
        // 		fprintf(stderr, "Failed to output index file into [%s]\n", input_file_name);
        // 	}
        // }

        /* free remaining compression structures */
        opj_destroy_compress(cinfo);
        if (*input_file_name)
            opj_destroy_cstr_info(&cstr_info);
    } else {			/* JP2 format output */
        int codestream_length;
        opj_cio_t *cio = NULL;
        FILE *f = NULL;

        /* get a JP2 compressor handle */
        opj_cinfo_t* cinfo = opj_create_compress(CODEC_JP2);
        /* setup the encoder parameters using the current image and using user parameters */
        opj_setup_encoder(cinfo, &cparameters, image);

        /* open a byte stream for writing */
        /* allocate memory for all tiles */
        cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

        /* encode the image */
        if (*input_file_name)					// If need to extract codestream information
            bSuccess = opj_encode_with_info(cinfo, cio, image, &cstr_info);
        else
            bSuccess = opj_encode(cinfo, cio, image, NULL);
        if (!bSuccess) {
            opj_cio_close(cio);
            fprintf(stderr, "failed to encode image\n");
            return 1;
        }
        codestream_length = cio_tell(cio);

        /* write the buffer to disk */
        f = fopen(cparameters.outfile, "wb");
        if (!f) {
            fprintf(stderr, "failed to open %s for writing\n", cparameters.outfile);
            return 1;
        }
        fwrite(cio->buffer, 1, codestream_length, f);
        fclose(f);
        fprintf(stderr,"Generated outfile %s\n",cparameters.outfile);
        /* close and free the byte stream */
        opj_cio_close(cio);
        
        /* Write the index to disk */
        // if (*input_file_name) {
        // 	bSuccess = write_index_file(&cstr_info, input_file_name);
        // 	if (bSuccess) {
        // 		fprintf(stderr, "Failed to output index file\n");
        // 	}
        // }

        /* free remaining compression structures */
        opj_destroy_compress(cinfo);
        if (*input_file_name)
            opj_destroy_cstr_info(&cstr_info);
    }

    /* free image data */
    opj_image_destroy(image);

    end:
    printf("Finish parsed");

    if(cparameters.cp_comment) free(cparameters.cp_comment);
	if(cparameters.cp_matrice) free(cparameters.cp_matrice);

	return 0;
}