#pragma once
#include "basic_types.h"
#include "memory_stick.h"
#include "core_err_code.h"

CORE_ERR_CODE bios_memory_read ( memory_stick * p_mem_stick, dword addr, dword * p_mem_value );
CORE_ERR_CODE bios_memory_write ( memory_stick * p_mem_stick, dword addr, dword to_write );