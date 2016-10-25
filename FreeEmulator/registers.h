#pragma once
#include <assert.h>
#define byte unsigned char
#define word unsigned short
#define dword unsigned int

typedef struct registers
{
	/* General-purose registers. */
	word ax;
	word bx;
	word cx;
	word dx;

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
registers_mov_reg ( registers * p_regs, word reg_dest, word reg_source )
{
	assert ( p_regs );
	switch ( reg_dest )
	{
	case AX:
		if ( reg_source == AX )
			p_regs->ax = p_regs->ax;
		else if ( reg_source == BX )
			p_regs->ax = p_regs->bx;
		else if ( reg_source == CX )
			p_regs->ax = p_regs->cx;
		else if ( reg_source == DX )
			p_regs->ax = p_regs->dx;
		else
			assert ( 0 );
		break;
	case BX:
		if ( reg_source == AX )
			p_regs->bx = p_regs->ax;
		else if ( reg_source == BX )
			p_regs->bx = p_regs->bx;
		else if ( reg_source == CX )
			p_regs->bx = p_regs->cx;
		else if ( reg_source == DX )
			p_regs->bx = p_regs->dx;
		else
			assert ( 0 );
		break;
	case CX:
		if ( reg_source == AX )
			p_regs->cx = p_regs->ax;
		else if ( reg_source == BX )
			p_regs->cx = p_regs->bx;
		else if ( reg_source == CX )
			p_regs->cx = p_regs->cx;
		else if ( reg_source == DX )
			p_regs->cx = p_regs->dx;
		else
			assert ( 0 );
		break;
	case DX:
		if ( reg_source == AX )
			p_regs->dx = p_regs->ax;
		else if ( reg_source == BX )
			p_regs->dx = p_regs->bx;
		else if ( reg_source == CX )
			p_regs->dx = p_regs->cx;
		else if ( reg_source == DX )
			p_regs->dx = p_regs->dx;
		else
			assert ( 0 );
		break;
	default:
		assert ( 0 );

	}
}

void
registers_mov_value ( registers * p_regs, word reg, word val )
/* Instruction MOV, that moves a value to a register. */
{
	assert ( p_regs );

	switch ( reg )
	{
	case AX:
		p_regs->ax = val;
		break;
	case BX:
		p_regs->bx = val;
		break;
	case CX:
		p_regs->cx = val;
		break;
	case DX:
		p_regs->dx = val;
		break;
	default:
		assert ( 0 );
	}
}

void
registers_add_value ( registers * p_regs, word reg, word value )
{
	/* Adds a value, specified directly, to a register. */
	assert ( p_regs );
	switch ( reg )
	{
	case AX:
		p_regs->ax += value;
		break;
	case BX:
		p_regs->bx += value;
		break;
	case CX:
		p_regs->cx += value;
		break;
	case DX:
		p_regs->dx += value;
		break;
	default:
		assert ( 0 );
	}
}

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
	p_registers->ax			= 0;
	p_registers->bx			= 0;
	p_registers->cx			= 0;
	p_registers->dx			= 0;
	p_registers->flags		= 0;
	p_registers->ip			= 0;
	p_registers->bp			= 0;
	p_registers->sp			= 0;
}