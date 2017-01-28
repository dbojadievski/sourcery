#include "basic_types.h"
#include "memory_routines.h"
#include "registers.h"
#include "memory_stick.h"
#include "BIOS.h"
#include <stdlib.h>

void test_bios_memory ( void );
void test_register_file_initialization ( void );

void 
main ( void )
{

	/* 
	 * Welcome to Sourcery!
	 * The show where we teach you...
	 * code sorcery.
	 */
	test_bios_memory ( );
	test_register_file_initialization ( );

}

void 
test_register_file_initialization ( )
{
	byte * p_buffer						= ( byte * ) malloc ( 512 );
	memory_zero ( p_buffer, 512 );

	registers register_file;
	registers_initialize ( &register_file );
	registers_add_value ( &register_file, AX, 1 );
	assert ( register_file.ax == 1 );

	byte val_true						= 1;
	byte val_false						= 0;

	byte flag							= 5;
	byte is_set							= flags_retrieve_byte ( flag, 1 );
	assert ( is_set );

	flag								= 0;
	flags_set_byte ( &flag, 0 );
	assert ( flag == 1 );

	registers_flags_carry_set ( &register_file );
	is_set								= flags_retrieve_word ( register_file.flags, 0 );
	assert ( is_set );
}

void 
test_bios_memory ( void )
{
	memory_stick main_stick;
	memory_stick_initialize ( &main_stick, 4 );
	assert ( main_stick.p_chips );

	bios_memory_write ( &main_stick, 0, 1 );

	CORE_ERR_CODE err;
	dword mem_buff						= 0xDEADC0DE;
	err									= bios_memory_read ( &main_stick, 0, &mem_buff );
	assert ( !err );
	assert ( mem_buff == 1 );

	dword mem_buff_2					= 0xDEADC0DE;
	err									= bios_memory_write ( &main_stick, 16, 1 );
	assert ( !err );
	err									= bios_memory_read ( &main_stick, 16, &mem_buff_2 );
	assert ( !err );
	assert ( mem_buff_2 == 1 );

	dword mem_buff_3					= 0;
	dword addr_to_read					= ( MEM_CHIP_CAPACITY + 1 );
	err									= bios_memory_write ( &main_stick, addr_to_read, 0xDEADC0DE );
	assert ( !err );
	err									= bios_memory_read ( &main_stick, addr_to_read, &mem_buff_3 );
	assert ( !err );
	assert ( mem_buff_3 == 0xDEADC0DE );

	/* This one is across chips. It writes 2 bytes to the first chip, and 2 bytes to the second one. */
	dword mem_buff_4					= 0;
	dword last_addr_at_first_chip		= ( MEM_CHIP_CAPACITY - 2 );
	err									= bios_memory_write ( &main_stick, last_addr_at_first_chip, 0xDEADC0DE );
	assert ( !err );
	err									= bios_memory_read ( &main_stick, last_addr_at_first_chip, &mem_buff_4 );
	assert ( !err );
	assert ( mem_buff_4 == 0xDEADC0DE );
}