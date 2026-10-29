
#pragma once

#include <stdint.h>

typedef struct
{

} ant_env_page0_data_t;

void ant_env_page_0_encode(uint8_t * p_page_buffer, 
			   ant_env_page0_data_t const * p_page_data);

void ant_env_page_0_decode(uint8_t const * p_page_buffer, 
			   ant_env_page0_data_t * p_page_data);
