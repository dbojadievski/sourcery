#pragma once
#include <assert.h>
#include "basic_types.h"
#include "memory_routines.h"

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


#define AX 1
#define BX 2
#define CX 3
#define DX 4

void
registers_mov_reg ( registers * p_regs, word reg_dest, word reg_source );


void
registers_mov_value ( registers * p_regs, word reg, word val );

void registers_add_value ( registers * p_regs, word reg, word value );

void
registers_add_reg ( registers * p_regs, word reg_dest, word reg_source )
{
	/* Adds registers together. */
	assert ( p_regs );
	switch ( reg_dest )
	{
	case AX:
		if ( reg_source == AX )
			p_regs->ax += p_regs->ax;
		else if ( reg_source == BX )
			p_regs->ax += p_regs->bx;
		else if ( reg_source == CX )
			p_regs->ax += p_regs->cx;
		else if ( reg_source == DX )
			p_regs->ax += p_regs->dx;
		else
			assert ( 0 );
		break;
	case BX:
		if ( reg_source == AX )
			p_regs->bx += p_regs->ax;
		else if ( reg_source == BX )
			p_regs->bx += p_regs->bx;
		else if ( reg_source == CX )
			p_regs->bx += p_regs->cx;
		else if ( reg_source == DX )
			p_regs->bx += p_regs->dx;
		else
			assert ( 0 );
		break;
	case CX:
		if ( reg_source == AX )
			p_regs->cx += p_regs->ax;
		else if ( reg_source == BX )
			p_regs->cx += p_regs->bx;
		else if ( reg_source == CX )
			p_regs->cx += p_regs->cx;
		else if ( reg_source == DX )
			p_regs->cx += p_regs->dx;
		else
			assert ( 0 );
		break;
	case DX:
		if ( reg_source == AX )
			p_regs->dx += p_regs->ax;
		else if ( reg_source == BX )
			p_regs->dx += p_regs->bx;
		else if ( reg_source == CX )
			p_regs->dx += p_regs->cx;
		else if ( reg_source == DX )
			p_regs->dx += p_regs->dx;
		else
			assert ( 0 );
		break;
	default:
		assert ( 0 );

	}
}

void
registers_initialize ( registers * p_registers )
{
	assert ( p_registers );
	size_t size = sizeof ( *p_registers );
	memory_zero ( p_registers, size );

	p_registers->ah			= least_significant_byte ( &( p_registers->ax ) );
	p_registers->al			= most_significant_byte ( &( p_registers->ax ), sizeof ( p_registers->ax ) );
	assert ( ( p_registers->al - p_registers->ah ) == 1 );

	p_registers->bh			= least_significant_byte ( &( p_registers->bx ) );
	p_registers->bl			= most_significant_byte ( &( p_registers->bx ), sizeof ( p_registers->bx ) );
	assert ( ( p_registers->bl - p_registers->bh ) == 1 );

	p_registers->ch			= least_significant_byte ( &( p_registers->cx ) );
	p_registers->cl			= most_significant_byte ( &( p_registers->cx ), sizeof ( p_registers->cx ) );
	assert ( ( p_registers->cl - p_registers->ch ) == 1 );

	p_registers->dh			= least_significant_byte ( &( p_registers->dx ) );
	p_registers->dl			= most_significant_byte ( &( p_registers->dx ), sizeof ( p_registers->dx ) );
	assert ( ( p_registers->dl - p_registers->dh ) == 1 );


}