#pragma once
#include "registers.h"
#include "memory_stick.h"

typedef struct
{
	registers * p_register_file;
	memory_stick * p_memory_stick;
} computer;

void 
computer_initialize ( computer * p_computer, registers * p_reg_file, memory_stick * p_memory_stick );
