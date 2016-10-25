#include "registers.h"
#include <stdlib.h>

void
main ( void )
{
	registers * p_regs					= ( registers * ) malloc ( sizeof ( registers ) );
	registers_initialize ( p_regs );
	registers_add_value ( p_regs, AX, 1 );
	assert ( p_regs->ax == 1 );	
}