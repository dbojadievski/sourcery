#include "basic_types.h"
#include "memory_routines.h"
#include "registers.h"
#include "memory_stick.h"
#include <stdlib.h>
void main ( void )
{

	/* 
	 * Welcome to Sourcery!
	 * The show where we teach you...
	 * code sorcery.
	 */
	byte * p_buffer = ( byte * ) malloc ( 512 );
	memory_zero ( p_buffer, 512 );

	registers register_file;
	registers_initialize ( &register_file );
	registers_add_value ( &register_file, AX, 1 );
	assert ( register_file.ax == 1 );

	byte val_true = 1;
	byte val_false = 0;

	byte flag	= 5;
	byte is_set = flags_retrieve_byte ( flag, 1 );
	assert ( is_set );

	flag		= 0;
	flags_set_byte ( &flag, 0 );
	assert ( flag == 1 );

	registers_flags_carry_set( &register_file );
	is_set		= flags_retrieve_word ( register_file.flags, 0 );
	assert ( is_set );

	memory_stick main_stick;
	memory_stick_initialize ( &main_stick, 4 );
	assert ( main_stick.p_chips );
}