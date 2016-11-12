#include "basic_types.h"
#include "core_err_code.h"
#include "memory_stick.h"
#include "memory_chip.h"
#include "memory_routines.h"
#include "BIOS.h"

#include <assert.h>


CORE_ERR_CODE  
bios_memory_read ( memory_stick * p_mem_stick, dword addr, dword * p_mem_value )
{
	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;
	assert ( p_mem_stick );
	assert ( p_mem_stick->num_chips );
	assert ( p_mem_stick->p_chips );
	dword mem_content					= 0xDEADC0DE; // Just for debugging; it's effectively a watch.
	
	memory_chip * p_chip				= p_mem_stick->p_chips [ 0 ];
	assert ( p_chip );
	dword storage_per_chip				= ( p_chip->block_count * p_chip->block_size );
	dword chip_idx						= ( addr / storage_per_chip );
	dword start_idx						= ( addr - ( chip_idx * storage_per_chip ) - 1 );
	
	if ( chip_idx >= p_mem_stick->num_chips || start_idx >= storage_per_chip )
		err_code						= CORE_ERR_INVALID_PARAM;
	else
	{

		p_chip							= p_mem_stick->p_chips[ chip_idx ];
		assert ( p_chip );
		assert ( p_chip->p_storage );

		dword * p_buffer				= ( dword * ) ( p_chip->p_storage + start_idx );
		mem_content						= *p_buffer;
		p_mem_value						= p_buffer;
	}
	
	return err_code;
}

CORE_ERR_CODE
bios_memory_write ( memory_stick * p_mem_stick, dword addr, dword to_write )
{
	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;
	assert ( p_mem_stick );
	assert ( p_mem_stick->num_chips );
	assert ( p_mem_stick->p_chips );
	dword mem_content					= 0xDEADC0DE;

	memory_chip * p_chip				= p_mem_stick->p_chips [ 0 ];
	assert ( p_chip );
	dword storage_per_chip				= ( p_chip->block_count * p_chip->block_size );
	dword chip_idx						= ( addr / storage_per_chip );

	dword start_idx						= ( addr - ( chip_idx * storage_per_chip ) - 1 );

	p_chip								= p_mem_stick->p_chips [ chip_idx ];
	assert ( p_chip );
	assert ( p_chip->p_storage );

	dword * p_buffer					= ( dword * ) ( p_chip->p_storage + start_idx );
	dword * p_to_write					= &to_write;
	memory_set_buffer ( p_buffer, p_to_write, sizeof ( dword ) );
	mem_content							= *p_buffer;

	return mem_content;
}