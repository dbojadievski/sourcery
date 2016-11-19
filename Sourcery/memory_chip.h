#pragma once
#include "basic_types.h"
#include "core_err_code.h"

typedef dword mem_refresh_rate;

#define MEM_CHIP_REFRESH_RATE 10000
#define MEM_CHIP_BLOCK_SIZE 4
#define MEM_CHIP_BLOCK_COUNT 256
#define MEM_CHIP_CAPACITY ( MEM_CHIP_BLOCK_SIZE * MEM_CHIP_BLOCK_COUNT )

typedef struct
/* Used for both DRAM and SRAM. */
{
	mem_refresh_rate refresh_rate; // RAM expiry time.
	byte block_size;
	dword block_count;

	byte * p_storage;
} memory_chip;

CORE_ERR_CODE memory_chip_initialize ( memory_chip * p_chip, mem_refresh_rate refesh_rate, byte block_size, dword block_count );
bool memory_chip_is_sram ( memory_chip * p_chip );






