#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chr.h"
#include "progInfo.h"

#define POSITION(_x, _y, _width) (_y * _width) + _x
#define STARTSWITH(_a, _b) strncmp(_a, _b, strlen(_b)) == 0

#define PGM_SIGNATURE "P5"

int chr_pgmToCHR(
	chr_t *chr,
	const char *filename
) {
	unsigned char x, y;
	unsigned char buffer[LENGTH_BUFFER];
	unsigned char color;
	
	unsigned short i, j = 0;
	unsigned short size[2];
	
	FILE *file = fopen(filename, "rb");
	
	if (chr == NULL) {
		fprintf(stderr, "ERROR: Output CHR is NULL");
		return 1;
	}
	
	if (file == NULL) {
		perror("ERROR: Failed to open PGM file (rb Mode)");
		return 1;
	}
	
	if (!fgets((char *)buffer, LENGTH_BUFFER, file)) {
		perror("ERROR: Failed to read PGM file");
		return 1;
	}
	
	if (!STARTSWITH((char *)buffer, PGM_SIGNATURE)) {
		fprintf(stderr, "ERROR: File signature isn't \"" PGM_SIGNATURE "\"\n");
		return 1;
	}
	
	for (i = 0; i < CHR_TILES; i++) {
		tile_init(&chr->tiles[i]);
	}
	
	do {
		fgets((char *)buffer, LENGTH_BUFFER, file);
		
		if (buffer[0] != '#') {
			if (sscanf(
				(char *)buffer,
				"%hu %hu",
				&size[0], &size[1]
			) != 2) {
				fprintf(stderr, "ERROR: Failed to get image size\n");
				fclose(file);
				return 1;
			}
			
			if (
				(size[0] != CHR_TILES / 4) ||
				(size[1] != CHR_TILES / 4)
			) {
				fprintf(
					stderr,
					"ERROR: Input image size isn't %ux%u\n",
					CHR_TILES / 4,
					CHR_TILES / 4
				);
				return 1;
			}
		}
	} while (buffer[0] == '#');
	
	fseek(file, 0L, SEEK_END);
	
	fseek(
		file,
		-(size[0] * size[1]),
		SEEK_CUR
	);
	
	for (i = 0; i < CHR_LENGTH_DATA; i++) {
		if (fread(
			buffer,
			sizeof(unsigned char),
			1,
			file
		) <= 0) {
			break;
		}
		
		chr->data[i] = buffer[0];
	}
	
	for (i = 0; i < CHR_TILES; i++) {
		if (!(i % (size[0] / 8)) && i > 0) {
			j += 7;
		}
		
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++) {
				color = chr->data[
					((y + j) * (size[0])) +
					(x + (i * 8))
				];
				
				if (color == 0xFF) {
					chr->tiles[i].data[y][x] = 3;
				} else if (color >= 0xC0) {
					chr->tiles[i].data[y][x] = 2;
				} else if (color >= 0x80) {
					chr->tiles[i].data[y][x] = 1;
				} else {
					if (color != 0x00) {
						printf("WARNING: Unknown Color: %02X\n", color);
					}
				}
			}
		}
	}
	
	fclose(file);
	return 0;
}

int chr_toFile(
	chr_t chr,
	const char *filename
) {
	unsigned char j, k;
	unsigned char binaryValue = 0;
	
	unsigned short i;
	
	FILE *file = fopen(filename, "wb");
	
	if (file == NULL) {
		perror("ERROR: Failed to open CHR file (wb Mode)");
		return 1;
	}
	
	for (i = 0; i < CHR_TILES; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 8; k++) {
				binaryValue = tile_toBinary(chr.tiles[i], j, k);
				fwrite(
					&binaryValue,
					sizeof(unsigned char),
					1,
					file
				);
			}
		}
	}
	
	fclose(file);
	return 0;
}