#include <assert.h>
#include <stdlib.h>

#include "basic_types.h"
#include "core_err_code.h"
#include "memory_chip.h"

CORE_ERR_CODE 
memory_chip_initialize ( memory_chip * p_chip, mem_refresh_rate refesh_rate, byte block_size, dword block_count )
{
	assert ( p_chip );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	p_chip->refresh_rate				= 0;
	p_chip->block_count					= block_count;
	p_chip->block_count					= block_size;

	p_chip->p_storage					= ( byte * ) malloc ( sizeof ( byte ) * ( block_count * block_size ) );
	assert ( p_chip->p_storage );
	
	if ( !p_chip->p_storage )
		err_code						=  ( err_code | CORE_ERR_OUT_OF_MEMORY );
	
	return err_code;
}

bool
memory_chip_is_sram ( memory_chip * p_chip )
{
	assert ( p_chip );
	assert ( p_chip->p_storage );

	return ( p_chip->refresh_rate == 0 );
}