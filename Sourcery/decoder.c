#include "basic_types.h"
#include "instruction.h"
#include "memory_routines.h"
#include "core_err_code.h"

#include <assert.h>

void
decode_to_header ( byte * p_instruction, instruction_header * p_dest, size_t instruction_size )
/* 
 * @Author: Dino
 * @Param p_instruction: A pointer to the raw instruction byte array. Must be 2 bytes long or more, 
 * as per the specification of the instruction format.
 * @Param p_dest: A pointer to the instruction header to set. Shall be cleared to zero beforehand.
 * The parse begins at bit (0), e.g the instruction is assumed to have end with two cleared bits.
 * NOTE(Dino):
 * The instruction header format is as specified: 
 * LLLLLLLL PPP S TТ *
 * L-bits determine the length of the total instruction, in bytes.
 * P-bits determine the number of parameters for the instruction, including the destination parameter.
 * T-bits determine the type of the parameters. Valid types include: byte, word, and double word.
 * The S-bit determines whether the instruction is a SIMD variant or not.
 */ 
{
	assert ( p_instruction );
	assert ( p_dest );
	memory_zero ( p_dest, ( sizeof ( instruction_header ) ));
	assert ( instruction_size >= 2 );

	/* The first byte of the instruction is just the size byte; we can copy it over as-is. */
	p_dest->size						= *p_instruction;
	byte * p_desc_byte					= ( p_instruction + 1 );
	
	/* Next up: the three P-bits. */
	bool is_p1_set						= memory_get_bit_from_byte ( *p_desc_byte, 0 );
	bool is_p2_set						= memory_get_bit_from_byte ( *p_desc_byte, 1 );
	bool is_p3_set						= memory_get_bit_from_byte ( *p_desc_byte, 2 );
	byte parameters						= 0;
	if ( is_p1_set )
		parameters						+= 1;
	if ( is_p2_set )
		parameters						+= 2;
	if ( is_p2_set )
		parameters						+= 4;
	p_dest->parameters					= parameters;
	
	/* Then we fetch the S-bit. */
	p_dest->is_simd						= memory_get_bit_from_byte ( *p_desc_byte, 3 );
	
	/* Finally, we fetch the T-bits. */
	bool is_t1_set						= memory_get_bit_from_byte ( *p_desc_byte, 4 );
	bool is_t2_set						= memory_get_bit_from_byte ( *p_desc_byte, 5 );
	byte t = 0;
	if ( is_t1_set )
		t += 1;
	if ( is_t2_set )
		t += 2;
	p_dest->type						= t;
}
