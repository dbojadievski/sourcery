#include "basic_types.h"
#include "basic_types.h"
#include "core_err_code.h"
#include <stddef.h>

/*NOTE(Dino): The result array needs be cleared to zeroes. */
CORE_ERR_CODE 
arithmetic_binary_add ( byte * p_addend_a, byte * p_addend_b, byte * p_result, size_t size );

CORE_ERR_CODE
arithmetic_binary_subtract ( byte * p_minuend, byte * p_subtrahend, byte * p_result, size_t size );

CORE_ERR_CODE
logic_binary_invert ( byte * p_to_invert, byte * p_result, size_t size );

CORE_ERR_CODE
logic_binary_twos_complement ( byte * p_param, byte * p_result, size_t size );