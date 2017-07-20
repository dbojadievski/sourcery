#include "basic_types.h"
#include "memory_routines.h"
#include "registers.h"
#include "memory_stick.h"
#include "BIOS.h"
#include "alu.h"
#include "instruction.h"
#include "decoder.h"

#include <stdlib.h>
#include <time.h>

#define DEBUG
#ifdef DEBUG
void test_bios_memory ( void );
void test_register_file_initialization ( void );
void test_is_bit_set ( void );
void test_decoder ( void );
void test_alu ( void );
#endif

void 
main ( void )
{
   /* 
	* Welcome to Sourcery!
	* The show where we teach you...
	* code sorcery.
	*/

	clock_t start 						= clock ( );
	printf ( "Running Sourcery!\n" );
	#ifdef DEBUG
	test_bios_memory ( );
	test_register_file_initialization ( );
	test_is_bit_set ( );
	test_decoder ( );
	test_alu ( );
	#endif

	printf ("Ran Sourcery successfully until the end!\n");

	clock_t end 						= clock ( );
	double seconds 						= ( ( double ) ( end - start ) / CLOCKS_PER_SEC );
	printf ( "Running the program took all of %f seconds.\n", seconds );
}

#ifdef DEBUG
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

void test_is_bit_set ( void )
{
    /* First test - 8-bit behavour. */
	byte test_case 						= ( byte ) 0b10000010;
	
	byte is_bit_set 					= memory_get_bit_from_byte ( test_case, 0 );
	assert ( !is_bit_set );

	is_bit_set 							= memory_get_bit_from_byte ( test_case, 1 );
	assert ( is_bit_set );

	is_bit_set 							= memory_get_bit_from_byte ( test_case, 7 );
	assert ( is_bit_set );


	/* Second test - 16-bit behaviour. */
	word instruction 					= 0b1000000000000000;

	is_bit_set 							= memory_get_bit_from_word ( instruction, 0 );
	assert ( !is_bit_set );
	
	is_bit_set 							= memory_get_bit_from_word ( instruction, 15 );
	assert ( is_bit_set );
	
	/* Final test - 32-bit behavour. */
	dword instruction32 				= 0b10000000000000000000000000000001;
	
	is_bit_set 							= memory_get_bit_from_dword ( instruction32 , 0 );
	assert ( is_bit_set );

	is_bit_set 							= memory_get_bit_from_dword ( instruction32, 15 );
	assert ( !is_bit_set );

	is_bit_set 							= memory_get_bit_from_dword ( instruction32, 31 );
	assert ( is_bit_set );
}

void
test_decoder_instruction_set ( void )
{
	word instruction					= 0b0000000011111111;
	instruction_header header;
	decode_to_header ( ( byte * ) ( &instruction ), &header, sizeof ( word ) );
}


void
test_decoder_decode_to_header ( )
{
	/* NOTE(Dino): The following instruction is one byte long, and has 0 parameters.  */
	word instruction = 0b0000000011111111;
	instruction_header header;
	decode_to_header ( ( byte * ) ( &instruction ), &header, sizeof ( word ) );

	assert ( header.size == 255 );
	assert ( !header.is_simd );
	assert ( !header.parameters );
	assert ( !header.type );
}

void
test_decoder ( void )
{
	test_decoder_decode_to_header ( );
	test_decoder_instruction_set ( );
}


void
test_alu_add ( void )
{
	byte actual[ 8 ] 					= { 0 };   
	byte expected[ 8 ] 					= { 0, 0, 0, 0, 0, 0, 1, 1 };
	byte addend_a[ 8 ] 					= { 0, 0, 0, 0, 0, 0, 0, 1};
	byte addend_b[ 8 ] 					= { 0, 0, 0, 0, 0, 0, 1, 0 };

	CORE_ERR_CODE err 					= arithmetic_binary_add ( addend_a, addend_b, actual, 8 );
	assert ( err == CORE_ERR_SUCCESS );

	bool are_equal 						= memory_compare ( actual, expected, 8 );
	assert ( are_equal );
}

void test_alu_subtract ( void )
{
	byte actual[ 4 ] 					= { 0 };
	byte expected[ 4 ] 					= { 0, 1, 1, 0 };
	byte minuend[ 4 ] 					= { 0, 1, 1, 1 };
	byte subtrahend[ 4 ] 				= { 0, 0, 0, 1 };

	CORE_ERR_CODE err 					= arithmetic_binary_subtract ( minuend, subtrahend, actual, 4 );
	assert ( err == CORE_ERR_SUCCESS );

	bool are_equal 						= memory_compare ( actual, expected, 4 );
	assert ( are_equal );
}

void
test_alu_invert ( void )
{
	byte actual[ 8 ] 					= { 0 };
	byte expected[ 8 ] 					= { 0 };
	byte to_invert[ 8 ] 				= { 1, 1, 1, 1, 1, 1, 1, 1 };

	CORE_ERR_CODE err 					= logic_binary_invert ( to_invert, to_invert, 8 );
	assert ( err == CORE_ERR_SUCCESS );

	bool are_equal 						= memory_compare ( actual, expected, 8 );
	assert ( are_equal );
}

void
test_alu_twos_complement ( void )
{
	//TODO(Dino): Bug here. Fix.
	byte actual[ 8 ] 					= { 0 };
	byte expected[ 8 ] 					= { 0, 0, 0, 0, 0, 0, 0, 1 };
	byte param[ 8 ]						= { 1, 1, 1, 1, 1, 1, 1, 1 };

	CORE_ERR_CODE err 					= logic_binary_twos_complement ( param, actual, 8 );
	assert ( err == CORE_ERR_SUCCESS );

	bool are_equal 						= memory_compare ( actual, expected, 8 );
	assert ( are_equal );
}

void
test_alu ( void )
{
	test_alu_add ( );
	test_alu_invert ( );
	test_alu_twos_complement ( );
	test_alu_subtract ( );
}
#endif
