/**
 * @file: recover.c
 * @author: Billy.Ljm
 * @date: 22 June 2015
 * @brief: recover deleted .jpg from .raw file
 *
 * >> ./recover card.raw
 *
 * .raw must be zeroed (i.e. no garbage value in slack space)
 * Also assumes jpgs are stored contiguously
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief: checks if FAT block likely contains a jpg
 * @param block: FAT block
 * @return: true if jpg likely contained, false otherwise
 */
inline bool checkjpg(uint8_t block[512]){
	return (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
		(block[3] == 0xe0 || block[3] == 0xe1));
}

int main(int argc, char* argv[])
{
	uint8_t block[512]; // FAT block
	char* filename; // .raw file name
	FILE* rawfile; // .raw file
	FILE* picfile; // file to put found picture into
	int picnum = 0; // number of current picture found
	char picname[8]; // name of output jpg file
	picname[7] = '\0';

	// open file
	if(argc > 1)
		filename = argv[1];
	else
		filename = "card.raw";
	rawfile = fopen(filename, "r");

	// find start block
	while(picnum == 0 && fread(&block, sizeof(block), 1, rawfile) == 1){
		if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
			(block[3] == 0xe0 || block[3] == 0xe1)){
			picfile = fopen("000.jpg", "w");
			picnum++;
			fwrite(&block, sizeof(block), 1, picfile);
		}
	}

	// copy rest of blocks
	while(fread(&block, sizeof(block), 1, rawfile) == 1){
		// seperate different jpg
		if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
			(block[3] == 0xe0 || block[3] == 0xe1)){
			fclose(picfile);
			sprintf(picname, "%.3d.jpg", picnum);
			picfile = fopen(picname, "w");
			picnum++;
		}
		fwrite(&block, sizeof(block), 1, picfile);
	}

	// end
	fclose(rawfile);
	return 0;
}
