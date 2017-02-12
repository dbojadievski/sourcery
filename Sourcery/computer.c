#include "registers.h"
#include "memory_stick.h"
#include "computer.h"
#include <stdlib.h>
#include <assert.h>

void
computer_initialize ( computer * p_computer, registers * p_reg_file, memory_stick * p_memory_stick )
{
	assert ( p_computer );
	assert ( p_reg_file );
	assert ( p_memory_stick );

	p_computer->p_register_file						= p_reg_file;
	p_computer->p_memory_stick						= p_memory_stick;
}

void
computer_free ( computer * p_computer )
{
	assert ( p_computer );
	free ( p_computer->p_register_file );
	memory_stick_free ( p_computer->p_memory_stick );
}
