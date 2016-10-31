#include "basic_types.h"
#include <assert.h>
#include <stdio.h>

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