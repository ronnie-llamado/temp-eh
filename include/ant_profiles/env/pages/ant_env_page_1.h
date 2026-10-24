#pragma once

#include <stdint.h>

typedef struct
{
	int16_t low_temp;
	int16_t high_temp;
	int16_t curr_temp;
} ant_env_page1_data_t;

void ant_env_page_1_encode(uint8_t * p_page_buffer, 
			   ant_env_page1_data_t const * p_page_data);

void ant_env_page_1_decode(uint8_t const * p_page_buffer, 
			   ant_env_page1_data_t * p_page_data);
