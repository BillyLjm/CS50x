/**
 * @file: whodunit.c
 * @author: Billy.Ljm
 * @date: 22 June 2015
 * @brief: Decipher red reveal messages
 *
 * Instead of the traditional red plastic which makes
 * everything red, I decided to make all the reds white.
 * This is because a white background is more pleasing
 * to the eyes.
 *
 * >> ./whodunit clue.bmp verdict.bmp
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 3){
		printf("Usage: ./copy infile outfile\n");
		return 1;
	}

	// remember filenames
	char* infile = argv[1];
	char* outfile = argv[2];

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
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}

	// write outfile's header
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // determine padding
	RGBTRIPLE triple; // to store RGB pixels
	printf("%d\n", padding);

	// iterate over pixels
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
		// change bits to red
		for (int j = 0; j < bi.biWidth; j++){
			fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
			triple.rgbtBlue = 0xff;
			triple.rgbtGreen = 0xff;
			fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		}
		// copy padding over
		if(padding != 0){
			fseek(inptr, padding, SEEK_CUR);
			for (int k = 0; k < padding; k++)
				fputc(0x00, outptr);
		}
	}

	// end
	fclose(inptr);
	fclose(outptr);
	return 0;
}
