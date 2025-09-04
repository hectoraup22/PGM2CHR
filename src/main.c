#include <stdio.h>
#include <string.h>

#include "progInfo.h"
#include "chr.h"

static char inputFilename[LENGTH_FILENAME];
static char outputFilename[LENGTH_FILENAME];

static chr_t chr;

int main(int argc, char *argv[]) {
	printf(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	
	if (argc > 1) {
		if (argc > 2) {
			strncpy(
				outputFilename,
				argv[2],
				LENGTH_FILENAME
			);
		} else {
			strncpy(
				outputFilename,
				DEFAULT_OUTPUTFILE,
				LENGTH_FILENAME
			);
		}
		
		strncpy(
			inputFilename,
			argv[1],
			LENGTH_FILENAME
		);
		
		printf("- Input: \"%s\"\n", inputFilename);
		printf("- Output: \"%s\"\n", outputFilename);
	} else {
		if (argc > 0) {
			printf("Usage: %s <input PGM filename> [output CHR filename]\n", argv[0]);
		}
		printf("- Missing input image\n");
		return 1;
	}
	
	printf("- Converting PGM file to CHR tile set\n");
	
	if (chr_pgmToCHR(&chr, inputFilename)) {
		printf("ERROR: Conversion failed\n");
		return 1;
	}
	
	printf("- Conversion complete\n");
	
	printf("- Creating CHR file\n");
	
	if (chr_toFile(chr, outputFilename)) {
		printf("ERROR: Failed to create CHR file\n");
		return 1;
	}
	
	printf("- Created CHR file\n");
	return 0;
}