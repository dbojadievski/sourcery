#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>

#include "basic_types.h"
#include "basic_types.h"
#include "core_err_code.h"
#include "memory_routines.h"
#include "alu.h"

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