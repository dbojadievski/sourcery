#pragma once
#include <assert.h>
#include "basic_types.h"
#include "memory_routines.h"

#define AX 1
#define BX 2
#define CX 3
#define DX 4

typedef struct registers
{
	/* General-purose registers. */
	word ax;
	word bx;
	word cx;
	word dx;

	byte * ah;
	byte * al;

	byte * bh;
	byte * bl;

	byte * ch;
	byte * cl;

	byte * dh;
	byte * dl;

	/* Special-purpose registers. */
	word ip;
	word bp;
	word sp;
	word flags;
} registers;

void
registers_mov_reg ( registers * p_regs, word reg_dest, word reg_source );


void
registers_mov_value ( registers * p_regs, word reg, word val );

void registers_add_value ( registers * p_regs, word reg, word value );

void
registers_add_reg ( registers * p_regs, word reg_dest, word reg_source );

void
registers_initialize ( registers * p_registers );