#pragma once

#include <stdint.h>
#include "list.h"

struct rs_control {
	int 		mm;
	int 		nn;
	uint16_t	*alpha_to;
	uint16_t	*index_of;
	uint16_t	*genpoly;
	int 		nroots;
	int 		fcr;
	int 		prim;
	int 		iprim;
	int		gfpoly;
	int		(*gffunc)(int);
	int		users;
	struct list_head list;
};


int encode_rs8(struct rs_control *rs, uint8_t *data, int len, uint16_t *par,
	uint16_t invmsk);
int decode_rs8(struct rs_control *rs, uint8_t *data, uint16_t *par, int len,
		uint16_t *s, int no_eras, int *eras_pos, uint16_t invmsk,
uint16_t *corr);
int encode_rs16(struct rs_control *rs, uint16_t *data, int len, uint16_t *par,
	uint16_t invmsk);
int decode_rs16(struct rs_control *rs, uint16_t *data, uint16_t *par, int len,
		uint16_t *s, int no_eras, int *eras_pos, uint16_t invmsk,
uint16_t *corr);

struct rs_control *init_rs(int symsize, int gfpoly, int fcr, int prim,
	int nroots);
struct rs_control *init_rs_non_canonical(int symsize, int (*func)(int),
int fcr, int prim, int nroots);

void free_rs(struct rs_control *rs);

static inline int rs_modnn(struct rs_control *rs, int x)
{
	while (x >= rs->nn) {
		x -= rs->nn;
		x = (x >> rs->mm) + (x & rs->nn);
	}
	return x;
}