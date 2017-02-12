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
registers_initialize ( registers * p_regs );

byte
get_carry_flag ( registers *p_regs );

#define registers_flags_carry_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 0))
#define registers_flags_parity_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 2))
#define registers_flags_af_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 4))
#define registers_flags_zero_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 6))
#define registers_flags_sign_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 7))
#define registers_flags_single_step_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 8))
#define registers_flags_interrupt_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 9))
#define registers_flags_direction_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 10))
#define registers_flags_overflow_retrieve(p_regs) (flags_retrieve_word(p_regs->flags, 11))

void
registers_flags_carry_set ( registers * p_regs );

void
registers_flags_parity_set ( registers * p_regs );

void
registers_flags_af_set ( registers * p_regs );

void
registers_flags_zero_set ( registers * p_regs );

void
registers_flags_sign_set ( registers * p_regs );

void
registers_flags_single_step_set ( registers * p_regs );

void
registers_flags_interrupt_set ( registers * p_regs );

void
registers_flags_direction_set ( registers * p_regs );

void
registers_flags_overflow_set ( registers * p_regs );
