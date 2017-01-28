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

	memory_chip * p_chip				= p_mem_stick->p_chips [ 0 ];
	assert ( p_chip );
	dword storage_per_chip				= ( p_chip->block_count * p_chip->block_size );
	dword chip_idx						= ( addr / storage_per_chip );
	dword start_idx						= ( addr - ( chip_idx * storage_per_chip ) );

	if ( chip_idx >= p_mem_stick->num_chips )  
		err_code						= CORE_ERR_INVALID_PARAM;
	else if ( ( start_idx + sizeof ( dword ) ) >= storage_per_chip )
		/* Note(Dino): Edge case, reading across 2 chips. */
	{
		if ( chip_idx + 1 >= p_mem_stick->num_chips ) // What if there is no chip we can spill the data to?
			goto end;
		
		dword size_to_read_total			= sizeof ( *p_mem_value );
		byte * p_read_buffer				= ( byte * ) p_mem_value;
		
		/* Note(Dino): read the first chip. */
		dword bytes_on_first_chip			= ( storage_per_chip - start_idx );
		byte * p_buffer						= ( byte * ) ( p_chip->p_storage + start_idx );
		for ( byte curr_byte_idx = 0; curr_byte_idx < bytes_on_first_chip; curr_byte_idx++ )
			p_read_buffer [ curr_byte_idx ]	= p_buffer [ curr_byte_idx ];

		/* Note(Dino): read the second chip. */
		p_buffer							= p_mem_stick->p_chips [ chip_idx + 1 ]->p_storage;
		for ( byte curr_byte_idx			= bytes_on_first_chip; curr_byte_idx < sizeof ( *p_mem_value ); curr_byte_idx++ )
			p_read_buffer [ curr_byte_idx ]	= p_buffer [ curr_byte_idx - bytes_on_first_chip ];
	}
	else
		/* Note(Dino): Standard case, reading on one chip only. */
	{

		p_chip							= p_mem_stick->p_chips [ chip_idx ];
		assert ( p_chip );
		assert ( p_chip->p_storage );

		dword * p_buffer				= ( dword * ) ( p_chip->p_storage + start_idx );
		*p_mem_value					= *p_buffer;
	}

	end:
	return err_code;
}

CORE_ERR_CODE
bios_memory_write ( memory_stick * p_mem_stick, dword addr, dword to_write )
{
	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;
	assert ( p_mem_stick );
	assert ( p_mem_stick->num_chips );
	assert ( p_mem_stick->p_chips );

	memory_chip * p_chip				= p_mem_stick->p_chips [ 0 ];
	assert ( p_chip );
	dword storage_per_chip				= ( p_chip->block_count * p_chip->block_size );
	dword chip_idx						= ( addr / storage_per_chip );

	dword start_idx						= ( addr - ( chip_idx * storage_per_chip ) );
	if ( chip_idx >= p_mem_stick->num_chips )
		err_code						= CORE_ERR_INVALID_PARAM;
	else if ( ( start_idx + sizeof ( to_write ) ) >= storage_per_chip )
	/*Note(Dino): Edge-case, writing across 2 chips. */
	{
		if ( chip_idx + 1 >= p_mem_stick->num_chips ) // What if there is no chip we can spill the data to? We need at least the current one and a next one to be available.
			goto end;

		/* Note(Dino): Write to the first chip. */
		dword bytes_on_first_chip		= ( storage_per_chip - start_idx );

		p_chip							= p_mem_stick->p_chips [ chip_idx ];
		assert ( p_chip );
		assert ( p_chip->p_storage );
		byte * p_buffer					= (byte * )( p_chip->p_storage + start_idx );
		byte * p_to_write				= ( byte * ) ( &to_write );
		for ( dword idx = 0; idx < bytes_on_first_chip; idx++ )
			p_buffer [ idx ]			= p_to_write [ idx ];
		
		/* Note(Dino): Write to the second chip. */
		dword bytes_on_second_chip		= ( sizeof ( to_write ) - bytes_on_first_chip );
		assert ( bytes_on_first_chip + bytes_on_second_chip == sizeof ( to_write ) );
		p_chip							= p_mem_stick->p_chips [ chip_idx + 1 ];
		assert ( p_chip );
		assert ( p_chip->p_storage );
		p_buffer						= p_chip->p_storage;
		for ( dword currByteIdx			= bytes_on_first_chip; currByteIdx < sizeof ( to_write ); currByteIdx++ )
			p_chip->p_storage [ currByteIdx - bytes_on_first_chip ] = p_to_write [ currByteIdx ];
	}
	else
		/* Note(Dino): Standard case, writing on one chip only. */
	{
		p_chip							= p_mem_stick->p_chips [ chip_idx ];
		assert ( p_chip );
		assert ( p_chip->p_storage );

		dword * p_buffer				= ( dword * ) ( p_chip->p_storage + start_idx );
		dword * p_to_write				= &to_write;
		memory_set_buffer ( p_buffer, p_to_write, sizeof ( dword ) );
	}

	end:
	return err_code;
}