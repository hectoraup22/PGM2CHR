#ifndef __CHR__
#define __CHR__

/* Macros */
#include "tile.h"

#define CHR_TILES 512
#define CHR_LENGTH_DATA CHR_TILES * (8 * 8)

/* Structs */
typedef struct {
	tile_t tiles[CHR_TILES];
	unsigned char data[CHR_LENGTH_DATA];
} chr_t;

/* Functions */
int chr_pgmToCHR(
	chr_t *chr,
	const char *filename
);

int chr_toFile(
	chr_t chr,
	const char *filename
);

#endif