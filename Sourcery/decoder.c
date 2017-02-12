#include "basic_types.h"
#include "instruction.h"
#include "memory_routines.h"
#include "core_err_code.h"

#include <assert.h>

void
/* 
 * @Author: Dino
 * @Param p_instruction: A pointer to the raw instruction byte array. Must be 2 bytes long or more, 
 * as per the specification of the instruction format.
 * @Param p_dest: A pointer to the instruction header to set. Shall be cleared to zero beforehand. Must be a valid pointer.
 * The parse begins at bit (0), e.g the instruction is assumed to have end with two cleared bits.
 * NOTE(Dino):
 * The instruction header format is as specified: 
 * LLLLLLLL PPP S TТ *
 * L-bits determine the length of the total instruction, in bytes.
 * P-bits determine the number of parameters for the instruction, including the destination parameter.
 * T-bits determine the type of the parameters. Valid types include: byte, word, and double word.
 * The S-bit determines whether the instruction is a SIMD variant or not.
 */ 
decode_to_header ( byte * p_instruction, instruction_header * p_dest, size_t instruction_size )
{
	assert ( p_instruction );
	assert ( p_dest );
	memory_zero ( p_dest, ( sizeof ( instruction_header ) ));
}
