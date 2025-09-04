#include "tile.h"
#include "binary.h"

void tile_init(tile_t *tile) {
	unsigned char x, y;
	
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			tile->data[y][x] = 0x00;
		}
	}
	return;
}

unsigned char tile_toBinary(
	tile_t tile,
	unsigned char colorLayer,
	unsigned char y
) {
	unsigned char x;
	
	int ret = 0;
	
	for (x = 0; x < 8; x++) {
		switch (tile.data[y][x]) {
			case 1:
				if (colorLayer == 0) {
					ret += binary_table[x];
				}
				break;
			case 2:
				if (colorLayer == 1) {
					ret += binary_table[x];
				}
				break;
			case 3:
				ret += binary_table[x];
				break;
			default:
				break;
		}
	}
	return ret;
}