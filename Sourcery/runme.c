#include "basic_types.h"
#include "memory_routines.h"
#include "registers.h"
#include <stdlib.h>

void main ( void )
{
	byte * p_buffer = ( byte * ) malloc ( 512 );
	memory_zero ( p_buffer, 512 );

	registers register_file;
	registers_initialize ( &register_file );
	registers_add_value ( &register_file, AX, 1 );
	assert ( register_file.ax == 1 );
}