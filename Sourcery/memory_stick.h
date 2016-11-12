#pragma once
#include "basic_types.h"
#include "memory_chip.h"
#include "core_err_code.h"

typedef struct
{
	byte num_chips;
	memory_chip ** p_chips;
} memory_stick;

CORE_ERR_CODE memory_stick_initialize ( memory_stick * p_mem_stick, byte num_chips );
void memory_stick_free ( memory_stick * p_mem_stick );