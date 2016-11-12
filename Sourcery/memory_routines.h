#pragma once
#include "basic_types.h"
#include <stdio.h>

byte *
least_significant_byte ( void * p_memory );

byte *
most_significant_byte ( void * p_memory, size_t size );

void
memory_set ( void * p_memory, byte value, size_t size );

void
memory_set_buffer ( void * p_memory, void * p_set_to, size_t size );

byte
flags_retrieve_byte ( byte flag, byte pos );

byte
flags_retrieve_word ( word p_flags, byte pos );

void
flags_set_byte ( byte * p_flag, byte pos );

void
flags_set_word ( word * p_flag, byte pos );


#define memory_zero(p_memory,size) (memory_set(p_memory,0,size))
