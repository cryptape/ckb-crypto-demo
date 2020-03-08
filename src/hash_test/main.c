#include "nist5.h"
#include "x11hash.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
int main() {

	const char in[80] = { 0 };
	memcpy(in, "11111111111111111112111111111111111111121111111111111111111211111111111111111112", 80);
	uint8_t out_nist5[32] = { 0 };
	uint8_t out_x11[32] = { 0 };
	x11_hash(in, out_nist5);
	nist5_hash(in, out_x11);
	for (int i = 0; i < 32; ++i)
		printf("%02x", out_nist5[i]);
	printf("\n\n");
	for (int j = 0; j < 32; ++j)
		printf("%02x", out_x11[j]);

	return 0;
}