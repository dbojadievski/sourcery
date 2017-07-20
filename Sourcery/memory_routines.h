#pragma once
#include "basic_types.h"
#include <stdio.h>

#define CORE_TRESHOLD_MALLOC 512

byte
memory_get_byte ( void * p_memory, dword idx );

void
memory_set_byte ( void * p_memory, dword idx, byte val );

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

bool
memory_get_bit_from_byte ( byte value, byte pos );

bool
memory_get_bit_from_byte ( byte value, byte pos );

bool
memory_get_bit_from_word ( word value, byte pos );

bool
memory_get_bit_from_dword ( dword value, byte pos );

bool
memory_compare ( void * p_comparand_a, void * p_comparand_b, size_t size );

void
memory_print ( void * p_memory, size_t size );

byte * 
memory_allocate ( size_t size );

#define memory_zero(p_memory,size) (memory_set(p_memory,0,size))
#define memory_is_bit_set(byte,num) (((1 << byte) & num) != 0)


