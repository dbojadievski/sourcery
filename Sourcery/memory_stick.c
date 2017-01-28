#include <stdlib.h>
#include <assert.h>

#include "core_err_code.h"
#include "basic_types.h"
#include "memory_chip.h"
#include "memory_stick.h"

CORE_ERR_CODE 
memory_stick_initialize ( memory_stick * p_mem_stick, byte num_chips )
{
	assert ( p_mem_stick );
	CORE_ERR_CODE err_code			= CORE_ERR_SUCCESS;
	
	p_mem_stick->p_chips			= ( memory_chip ** ) malloc ( sizeof ( memory_chip ) * num_chips );
	p_mem_stick->num_chips			= num_chips;
	for ( byte curr_chip_idx		= 0; curr_chip_idx < num_chips; curr_chip_idx++ )
	{

		memory_chip * p_curr_chip	= malloc ( sizeof ( memory_chip ) );
		if ( p_curr_chip )
		{
			if ( memory_chip_initialize ( p_curr_chip, MEM_CHIP_REFRESH_RATE, MEM_CHIP_BLOCK_SIZE, MEM_CHIP_BLOCK_COUNT ) )
			{
				err_code			= ( err_code | CORE_ERR_OUT_OF_MEMORY );
				break;
			}
			else
			{
				/* Success path.*/
				p_mem_stick->p_chips [ curr_chip_idx ] = p_curr_chip;
			}
		}
		else
		{
			err_code				= ( err_code | CORE_ERR_OUT_OF_MEMORY );
			break;
		}
	}

	return err_code;
}

void
memory_stick_free ( memory_stick * p_mem_stick )
{
	assert ( p_mem_stick );
	for ( dword curr_chip_idx		= 0; curr_chip_idx < p_mem_stick->num_chips; p_mem_stick++ )
		free ( p_mem_stick->p_chips [ curr_chip_idx ] );
}