#include "registers.h"
#include <stdlib.h>
#include "memory_routines.h"

/* Welcome to sourcery!*/
void
main ( void )
{
	registers * p_regs					= ( registers * ) malloc ( sizeof ( *p_regs ) );
	registers_initialize ( p_regs );
	word val_to_add						= 1;
	registers_add_value ( p_regs, AX, val_to_add );
	assert ( p_regs->ax == 1 );
	byte * p_most_significant			= least_significant_byte ( &( p_regs->ax ) );
	byte * p_least_significant			= most_significant_byte ( &( p_regs->ax ), sizeof (p_regs->ax ) );
	assert ( p_least_significant		= p_most_significant - 1 );
}