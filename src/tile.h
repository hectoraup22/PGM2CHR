#ifndef __TILE__
#define __TILE__

typedef struct {
	unsigned char data[8][8];
} tile_t;

void tile_init(tile_t *tile);

unsigned char tile_toBinary(
	tile_t tile,
	unsigned char colorLayer,
	unsigned char y
);

#endif