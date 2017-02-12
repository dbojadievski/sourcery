#pragma once

#include "basic_types.h"
#include "instruction.h"

void decode_to_header ( byte * p_instruction, instruction_header * p_dest, size_t instruction_size );

