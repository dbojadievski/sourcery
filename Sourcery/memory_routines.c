#include "basic_types.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
byte *
least_significant_byte ( void * p_memory )
{
	assert ( p_memory );

	byte * p_least_significant = NULL;
	p_least_significant = ( byte * ) p_memory;
	return p_least_significant;
}

byte *
most_significant_byte ( void * p_memory, size_t size )
{
	assert ( p_memory );
	assert ( size );

	byte * p_most_significant = NULL;
	p_most_significant = ( byte * ) p_memory;
	p_most_significant = p_most_significant + ( size - 1 );

	return p_most_significant;
}

byte
flags_retrieve_byte ( byte p_flag, byte pos )
{
	assert ( pos >= 0 && pos <= 7);
	byte value		= 0;

	byte to_or		= ( 0b00000000 | pos );

	value			= ( ( p_flag & to_or ) != 0 );
	return value;
}

byte
flags_retrieve_word ( word p_flags, byte pos )
{
	assert ( pos >= 0 && pos <= 15 );
	byte value		= 0;

	byte to_or		= ( 0b0000000000000000 | pos );
	value			= ( ( p_flags | to_or ) != 0 );
	return value;
}

void
flags_set_byte ( byte * p_flag, byte pos )
{
	assert ( pos >= 0 && pos <= 7 );
	byte to_mul		= pow ( 2, pos );
	*p_flag			= ( *p_flag | to_mul );
}

void
flags_set_word ( word * p_flag, byte pos )
{
	assert ( pos >= 0 && pos <= 15 );
	word to_mul			= pow ( 2, pos );
	*p_flag = ( *p_flag | to_mul );
}

void
memory_set ( void * p_memory, byte value, size_t size )
{
	assert ( p_memory );
	assert ( size );

	byte * p_curr = ( byte * ) ( p_memory );
	byte * p_last = most_significant_byte ( p_memory, size );
	assert ( p_curr == p_memory );

	while ( p_curr <= p_last )
	{
		*p_curr = value;
		p_curr = p_curr + sizeof ( byte );
	}
}

void
memory_set_buffer ( void * p_memory, void * p_set_to, size_t size )
{
	assert ( p_memory );
	assert ( p_set_to );
	assert ( size );

	byte * p_buff_to_set				= ( byte * ) p_memory;
	byte * p_buff_set_to				= ( byte * ) p_set_to;

	for ( size_t curr_byte_idx			= 0; curr_byte_idx < size; curr_byte_idx++ )
	{
		p_buff_to_set [ curr_byte_idx ] = p_buff_set_to [ curr_byte_idx ];
	}
}