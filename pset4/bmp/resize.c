/**
 * @file: resize.c
 * @author: Billy.Ljm
 * @date: 22 June 2015
 * @brief: Rescale a 24-bit uncompressed BMP 4.0
 *
 * >> ./resize 4 small.bmp large.bmp
 *
 * Only scales up by positive integers
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 4){
		printf("Usage: ./copy scale_factor infile outfile\n");
		return 1;
	}

	// remember filenames
	uint scale = atoi(argv[1]);
	char* infile = argv[2];
	char* outfile = argv[3];

	// open files
	FILE* inptr = fopen(infile, "r");
	if (inptr == NULL){
		printf("Could not open %s.\n", infile);
		return 2;
	}
	FILE* outptr = fopen(outfile, "w");
	if (outptr == NULL){
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}

	// read infile's headers
	BITMAPFILEHEADER inbf;
	fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);
	BITMAPINFOHEADER inbi;
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

	// calculate padding
	int inpad = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // infile padding
	int outpad = (4 - (inbi.biWidth * scale * sizeof(RGBTRIPLE)) % 4) % 4; // outfile padding

	// write outfile's header
	BITMAPFILEHEADER outbf = inbf;
	BITMAPINFOHEADER outbi = inbi;
	outbi.biWidth = inbi.biWidth * scale;
	outbi.biHeight = inbi.biHeight * scale;
	outbi.biSizeImage = (outbi.biWidth * sizeof(RGBTRIPLE) + outpad) * abs(outbi.biHeight);
	outbf.bfSize = inbf.bfSize + outbi.biSizeImage - inbi.biSizeImage;
	fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

	RGBTRIPLE triple; // to store RGB pixels

	// scale pixels
	for(int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++){
		for(int j = 0; j < scale; j++){
			// scale line laterally
			for(int k = 0; k < inbi.biWidth; k++){
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
				for(int l = 0; l < scale; l++)
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
			}

			// insert padding
			for(int k = 0; k < outpad; k++)
				fputc(0x00, outptr);

			// back to start, to scale vertically
			if(j < scale - 1)
				fseek(inptr, -inbi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
		}

		// move on to infile's next line
		fseek(inptr, inpad, SEEK_CUR);
	}

	// end
	fclose(inptr);
	fclose(outptr);
	return 0;
}
