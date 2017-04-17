#pragma once
#include "basic_types.h"

typedef struct instruction_header
{
    byte size;
    byte parameters;
    byte is_simd;
    byte type; 
} instruction_header;
