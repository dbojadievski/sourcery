#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>

#include "basic_types.h"
#include "basic_types.h"
#include "core_err_code.h"
#include "memory_routines.h"
#include "alu.h"

/* * * * * * * * * * * * * * * * * * B I N A R Y * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CORE_ERR_CODE 
arithmetic_binary_add ( byte * p_addend_a, byte * p_addend_b, byte * p_result, size_t size )
{
    assert ( p_addend_a );
    assert ( p_addend_b );
    assert ( p_result );
    assert ( size > 0 );

    CORE_ERR_CODE err_code              = CORE_ERR_SUCCESS;
    if ( !p_addend_a || !p_addend_b || !p_result )
    {
        err_code                        = CORE_ERR_INVALID_PARAM;
        goto end;
    }

    byte bit_a, bit_b, bit_result;
    byte carry_in                       = 0;
    size_t curr_idx                     = 0;
    for ( ; curr_idx < size; ++curr_idx )
    {
        byte inv_idx                    = ( size - curr_idx - 1 );
        bit_a                           = p_addend_a[ inv_idx ];
        bit_b                           = p_addend_b[ inv_idx ];

        bit_result                      = ( ( bit_a ^ bit_b )  ^ carry_in );
        carry_in                        = ( ( bit_a && bit_b ) + ( carry_in * ( bit_a ^ bit_b ) ) );
        p_result[ inv_idx ]             = bit_result;
    }

    end:
    return err_code;
}

CORE_ERR_CODE
arithmetic_binary_subtract ( byte * p_minuend, byte * p_subtrahend, byte * p_result, size_t size )
{
    assert ( size );
    assert ( p_result );
    assert ( p_minuend );
    assert ( p_subtrahend );

    CORE_ERR_CODE err_code              = CORE_ERR_SUCCESS;
    
    err_code                            = logic_binary_twos_complement ( p_subtrahend, p_result, size );
    if ( err_code != CORE_ERR_SUCCESS )
        goto end;
     
    err_code                            = arithmetic_binary_add ( p_minuend, p_result, p_result, size );
    if ( err_code != CORE_ERR_SUCCESS )
        goto end;
    
    if ( p_result[ 0 ] != 0 )
        err_code                        = logic_binary_twos_complement ( p_result, p_result, size );

    end:
    return err_code;
}

CORE_ERR_CODE
arithmetic_binary_multiply ( byte * p_multiplier, byte * p_multiplicand, byte * p_result, size_t size )
/* NOTE(Dino): Unimplemented. */
/* NOTE(Dino): An intermediate array of size ( 2 * size ) will be used for the multiplication. */
{
	assert ( 0 ); 

	assert ( size );
	assert ( p_result );
	assert ( p_multiplicand );
	assert ( p_multiplier );
	
	CORE_ERR_CODE err_code 				= CORE_ERR_SUCCESS;

	if ( !p_multiplier || !p_multiplicand || !p_result || !size )
	{
		err_code						 = CORE_ERR_INVALID_PARAM;
		goto end;
	}

	byte * p_partial_sum				= memory_allocate ( ( 2 * size ) );
	err_code							= ( p_partial_sum  ? CORE_ERR_SUCCESS : CORE_ERR_OUT_OF_MEMORY );
	if ( err_code != CORE_ERR_SUCCESS )
		goto end;


	end:
	return err_code;
}

CORE_ERR_CODE
logic_binary_invert ( byte * p_to_invert, byte * p_result, size_t size )
{
    assert ( size );
    assert ( p_result );
    assert ( p_to_invert );

    CORE_ERR_CODE err_code              = CORE_ERR_SUCCESS;
    if ( !p_to_invert || ! p_result || !size )
    {
        err_code                        = CORE_ERR_INVALID_PARAM;
        goto end;
    }

    byte current;
    size_t curr_idx                     = 0;
    for ( ; curr_idx < size; ++curr_idx )
    {
        current                         = !p_to_invert[ curr_idx ];
        p_result[ curr_idx ]            = current; 
    }

    end:
    return err_code;
}

CORE_ERR_CODE
logic_binary_twos_complement ( byte * p_param, byte * p_result, size_t size )
{
    assert ( size );
    assert ( p_result );
    assert ( p_param );

    CORE_ERR_CODE err_code              = CORE_ERR_SUCCESS;
    if ( !p_param || ! p_result || !size )
    {
        err_code                        = CORE_ERR_INVALID_PARAM;
        goto end;
    }

    err_code                            = logic_binary_invert ( p_param, p_result, size );    
    if ( err_code != CORE_ERR_SUCCESS )
        goto end;
    
	byte * p_temp						= memory_allocate ( size );
    err_code                            = ( p_temp != 0 ? CORE_ERR_SUCCESS : CORE_ERR_OUT_OF_MEMORY );
    if ( err_code != CORE_ERR_SUCCESS )
        goto end;

    memory_set ( p_temp, 0, size );
    p_temp[ ( size - 1 ) ]              = 1;
    err_code                            = arithmetic_binary_add ( p_result, p_temp, p_result, size );

    end:
    return err_code;
}

CORE_ERR_CODE
logic_binary_is_zero ( byte * p_param, bool * p_result, size_t size )
{
	assert ( p_param );
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_param || !p_result || !size )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	size_t curr_bit						= 0;
	while ( curr_bit++ < size )
		if ( p_param [ curr_bit ] )
		{
			*p_result					= 0;
			break;
		}

	end:
	return err_code;
}

CORE_ERR_CODE
logic_binary_is_positive ( byte * p_param, bool * p_result, size_t size )
{
	assert ( p_param );
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_param || !p_result || !size )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= !*p_param;
	end:
	return err_code;
}

CORE_ERR_CODE
logic_binary_is_negative ( byte * p_param, bool * p_result, size_t size )
{
	assert ( p_param );
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_param || !p_result || !size )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= *p_param;
end:
	return err_code;
}

/* * * * * * * * * * * * * * * * * * B I N A R Y * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * D E C I M A L * * * * * * * * * * * * * * * * * * * * * * * * * * */

CORE_ERR_CODE
arithmetic_decimal_add ( word a, word b, word * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( a + b );	

	end:
	return err_code;
}

CORE_ERR_CODE
arithmetic_decimal_subtract ( word a, word b, word * p_result )
{
	assert ( p_result );
	
	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;
		
	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( a - b );
	
	end:
	return err_code;
}

CORE_ERR_CODE
arithmetic_decimal_multiply ( word multiplier, word multiplicand, word * p_result )
{
	assert ( p_result );
	
	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;
	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( multiplier * multiplicand );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_decimal_shift_left ( word to_shift, size_t shift_by, word * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( to_shift << shift_by );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_decimal_shift_right ( word to_shift, size_t shift_by, word * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code = CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( to_shift >> shift_by );
	
	end:
	return err_code;
}

CORE_ERR_CODE
logic_invert ( word a, word * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( -1 * a );

	end:
	return err_code;
}



CORE_ERR_CODE
logic_decimal_is_zero ( word to_compare, bool * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( to_compare == 0 );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_decimal_is_positive ( word to_compare, bool * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code				= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code						= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result							= ( to_compare > 0 );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_decimal_is_negative ( word to_compare, bool * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code			= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code					= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result						= ( to_compare < 0 );

	end:
	return err_code;
}
/* * * * * * * * * * * * * * * * * * D E C I M A L * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * B Y T E * * * * * * * * * * * * * * * * * * * * * * * * * * */
CORE_ERR_CODE
arithmetic_byte_add ( byte a, byte b, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result					= ( a + b );

	end:
	return err_code;
}

CORE_ERR_CODE
arithmetic_byte_subtract ( byte a, byte b, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result					= ( a - b );

	end:
	return err_code;
}

CORE_ERR_CODE
arithmetic_byte_multiply ( byte multiplier, byte multiplicand, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;
	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result					= ( multiplier * multiplicand );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_shift_left ( byte to_shift, size_t shift_by, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result					= ( to_shift << shift_by );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_shift_right ( byte to_shift, size_t shift_by, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result = ( to_shift >> shift_by );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_invert ( byte a, byte * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code		= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code				= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result					= ( -1 * a );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_is_zero ( byte to_compare, bool * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code	= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code			= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result				= ( to_compare == 0 );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_is_positive ( byte to_compare, bool * p_result )
{
	assert ( p_result );

	CORE_ERR_CODE err_code	= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code			= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result				= ( to_compare > 0 );

	end:
	return err_code;
}

CORE_ERR_CODE
logic_byte_is_negative ( byte to_compare, bool * p_result )
{
	assert ( p_result );
	CORE_ERR_CODE err_code	= CORE_ERR_SUCCESS;

	if ( !p_result )
	{
		err_code			= CORE_ERR_INVALID_PARAM;
		goto end;
	}

	*p_result				= ( to_compare < 0 );

	end:
	return err_code;
}
/* * * * * * * * * * * * * * * * * * B Y T E * * * * * * * * * * * * * * * * * * * * * * * * * * */