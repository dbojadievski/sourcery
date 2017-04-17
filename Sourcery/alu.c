#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#include "basic_types.h"
#include "basic_types.h"
#include "core_err_code.h"
#include "memory_routines.h"
#include "alu.h"

#define CORE_TRESHOLD_MALLOC 512

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
    
    byte * p_temp                       = ( size < CORE_TRESHOLD_MALLOC ) ?  ( ( byte * ) alloca ( size ) ) : ( ( byte * ) malloc ( size ) );
    err_code                            = ( p_temp != 0 ? CORE_ERR_SUCCESS : CORE_ERR_OUT_OF_MEMORY );
    if ( err_code != CORE_ERR_SUCCESS )
        goto end;

    memory_set ( p_temp, 0, size );
    p_temp[ ( size - 1 ) ]              = 1;
    err_code                            = arithmetic_binary_add ( p_result, p_temp, p_result, size );

    end:
    return err_code;
}