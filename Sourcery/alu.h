#include "basic_types.h"
#include "core_err_code.h"
#include <stddef.h>

/* * * * * * * * * * * * * * * * D E C I M A L * * * * * * * * * * * * * * * * * * */
CORE_ERR_CODE
arithmetic_decimal_add ( word a, word b, word * p_result );

CORE_ERR_CODE
arithmetic_decimal_subtract ( word a, word b, word * p_result );

CORE_ERR_CODE
arithmetic_decimal_multiply ( word multiplier, word multiplicand, word * p_result );

CORE_ERR_CODE
logic_decimal_shift_left ( word to_shift, size_t shift_by, word * p_result );

CORE_ERR_CODE
logic_decimal_shift_right ( word to_shift, size_t shift_by, word * p_result );

CORE_ERR_CODE
logic_decimal_is_zero ( word to_compare, bool * p_result );

CORE_ERR_CODE
logic_decimal_is_positive ( word to_compare, bool * p_result );

CORE_ERR_CODE
logic_decimal_is_negative ( word to_compare, bool * p_result );
/* * * * * * * * * * * * * * * * D E C I M A L * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * B Y T E  * * * * * * * * * * * * * * * * * * * * */
CORE_ERR_CODE
arithmetic_byte_add ( byte a, byte b, byte * p_result );

CORE_ERR_CODE
arithmetic_byte_subtract ( byte a, byte b, byte * p_result );

CORE_ERR_CODE
arithmetic_byte_multiply ( byte multiplier, byte multiplicand, byte * p_result );

CORE_ERR_CODE
logic_byte_shift_left ( byte to_shift, size_t shift_by, byte * p_result );

CORE_ERR_CODE
logic_byte_shift_right ( byte to_shift, size_t shift_by, byte * p_result );

CORE_ERR_CODE
logic_byte_is_zero ( byte to_compare, bool * p_result );

CORE_ERR_CODE
logic_byte_is_positive ( byte to_compare, bool * p_result );

CORE_ERR_CODE
logic_byte_is_negative ( byte to_compare, bool * p_result );
/* * * * * * * * * * * * * * * * B Y T E  * * * * * * * * * * * * * * * * * * * * */
