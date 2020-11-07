/**
 * @file: resize.c
 * @author: Billy.Ljm
 * @date: 22 June 2015
 * @brief: Rescale a 24-bit uncompressed BMP 4.0
 *
 * >> ./resize 4.0 small.bmp large.bmp
 *
 * Scales up & down by positive floats.
 * No anti-aliasing or interpolation.
 * Scales up pixel by pixel & scale down square of pixels by square of pixels.
 * As such, actual scaling factor may differ from factor provided.
 * Sides of picture may also be deleted when scaling down.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	float inscale; // scale factor user provided
	int scale; // scale factor optimised & stored as integer (for resizing down, actual scale is 1/scale)
	bool scaleup; // indicates if image is being resized up or down
	char* infile; // in file name
	char* outfile; // out file name
	FILE* inptr; // in file stream pointer
	FILE* outptr; // out file stream pointer
	int inpad; // in file padding (includes pixels to ignore)
	int outpad; // out file padding
	int ignoredpix; // number of pixels ignored when scaling down
	BITMAPFILEHEADER inbf; // in file headers
	BITMAPINFOHEADER inbi;
	BITMAPFILEHEADER outbf; // out file headers
	BITMAPINFOHEADER outbi;
	RGBTRIPLE inpix; // to read in file RGB pixels
	RGBTRIPLE outpix; // to create out file RGB pixels

	// ensure proper usage
	if (argc != 4){
		printf("Usage: ./copy scale_factor infile outfile\n");
		return 1;
	}

	// remember file names
	infile = argv[2];
	outfile = argv[3];

	// optimise scale
	inscale = atof(argv[1]);
	if(inscale <= 0){
		printf("Please provide a non-negative scale factor\n");
		return 1;
	}
	else if(inscale > 1){ // to nearest whole number
		scale = (int)round(inscale);
		scaleup = true;
	}
	else{ // to nearest 1/integer
		scale = (int)round(1/inscale);
		scaleup = false;
	}

	// open files
	inptr = fopen(infile, "r");
	if (inptr == NULL){
		printf("Could not open %s.\n", infile);
		return 2;
	}
	outptr = fopen(outfile, "w");
	if (outptr == NULL){
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}

	// read infile's headers
	fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);
	fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 ||
		inbi.biBitCount != 24 || inbi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}

	// write out file's headers
	outbf = inbf;
	outbi = inbi;
	inpad = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	if(scaleup){
		outbi.biWidth = inbi.biWidth * scale;
		outbi.biHeight = inbi.biHeight * scale;
		ignoredpix = 0;
	}else{
		outbi.biWidth = (int)(inbi.biWidth / scale);
		outbi.biHeight = (int)(inbi.biHeight / scale);
		ignoredpix = (inbi.biWidth % scale);
	}
	outpad = (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	outbi.biSizeImage = (outbi.biWidth * sizeof(RGBTRIPLE) + outpad) * abs(outbi.biHeight);
	outbf.bfSize = inbf.bfSize + outbi.biSizeImage - inbi.biSizeImage;
	fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

	// scale pixels up
	if(scaleup){
		for(int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++){
			for(int j = 0; j < scale; j++){
				// scale line laterally
				for(int k = 0; k < inbi.biWidth; k++){
					fread(&outpix, sizeof(RGBTRIPLE), 1, inptr);
					for(int l = 0; l < scale; l++)
						fwrite(&outpix, sizeof(RGBTRIPLE), 1, outptr);
				}

				// insert padding
				for(int k = 0; k < outpad; k++)
					fputc(0x00, outptr);

				// back to start, to scale vertically
				if(j < scale - 1)
					fseek(inptr, -inbi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
			}

			// move on to in file's next line
			fseek(inptr, inpad, SEEK_CUR);
		}
	}

	// scale pixel down
	else{
		int totred, totgreen, totblue; // total colour values of pixel square
		for(int i = 0, biHeight = abs(outbi.biHeight); i < biHeight; i++){
			for(int j = 0; j < outbi.biWidth; j++){
				// sum color values in pixel square (from top-left to bottom-right)
				totred = 0; totgreen = 0; totblue = 0;
				for(int k = 0; k < scale; k++){
					// sum row in pixel square
					for(int l = 0; l < scale; l++){
						fread(&inpix, sizeof(RGBTRIPLE), 1, inptr);
						totred += inpix.rgbtRed;
						totgreen += inpix.rgbtGreen;
						totblue += inpix.rgbtBlue;
					}

					// move to next line in pixel square
					if(k != scale - 1)
						fseek(inptr, (inbi.biWidth - scale) * sizeof(RGBTRIPLE) + inpad , SEEK_CUR);
				}

				// write out file pixel
				outpix.rgbtRed = totred / (scale * scale);
				outpix.rgbtGreen = totgreen / (scale * scale);
				outpix.rgbtBlue = totblue / (scale * scale);
				fwrite(&outpix, sizeof(RGBTRIPLE), 1, outptr);

				// move in file pointer to top-left of next pixel square
				if(j != outbi.biWidth - 1)
					fseek(inptr, -(scale - 1) * (inbi.biWidth * sizeof(RGBTRIPLE) + inpad), SEEK_CUR);
			}

			// manage padding
			for(int j = 0; j < outpad; j++)
				fputc(0x00, outptr);
			fseek(inptr, ignoredpix * sizeof(RGBTRIPLE) + inpad, SEEK_CUR);
		}
	}

	// end
	fclose(inptr);
	fclose(outptr);
	return 0;
}
