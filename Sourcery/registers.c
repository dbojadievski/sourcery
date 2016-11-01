#pragma once

#include "registers.h"
#include "memory_routines.h"

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

	assert ( p_registers );

	size_t size												= sizeof ( *p_registers );

	memory_zero ( p_registers, size );



	p_registers->ah											= most_significant_byte ( &( p_registers->ax ), sizeof ( p_registers->ax ) );

	p_registers->al											= least_significant_byte ( &( p_registers->ax ) );

	assert ( ( p_registers->al - p_registers->ah ) == -1 );



	p_registers->bh											= most_significant_byte ( &( p_registers->bx ), sizeof ( p_registers->bx ) );

	p_registers->bl											= least_significant_byte ( &( p_registers->bx ) );

	assert ( ( p_registers->bl - p_registers->bh ) == -1 );



	p_registers->ch											= most_significant_byte ( &( p_registers->cx ), sizeof ( p_registers->cx ) );

	p_registers->cl											= least_significant_byte ( &( p_registers->cx ) );

	assert ( ( p_registers->cl - p_registers->ch ) == -1 );

	p_registers->dh											= most_significant_byte ( &( p_registers->dx ), sizeof ( p_registers->dx ) );

	p_registers->dl											= least_significant_byte ( &( p_registers->dx ) );

	assert ( ( p_registers->dl - p_registers->dh ) == -1 );





}

void
registers_flags_carry_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 0 );
}

void
registers_flags_parity_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 2 );
}

void
registers_flags_af_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 4 );
}

void
registers_flags_zero_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 6 );
}

void
registers_flags_sign_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 7 );
}

void
registers_flags_single_step_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 8 );
}

void
registers_flags_interrupt_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 9 );
}

void
registers_flags_direction_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 10 );
}

void
registers_flags_overflow_set ( registers * p_regs )
{
	assert ( p_regs );
	flags_set_word ( &(p_regs->flags), 11 );
}






