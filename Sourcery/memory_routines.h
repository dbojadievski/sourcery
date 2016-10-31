#pragma once
#include "basic_types.h"
#include <stdio.h>

byte *
least_significant_byte ( void * p_memory );

byte *
most_significant_byte ( void * p_memory, size_t size );

void
memory_set ( void * p_memory, byte value, size_t size );

#define memory_zero(p_memory,size) (memory_set(p_memory,0,size))
