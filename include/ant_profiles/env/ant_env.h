
#include <ant_parameters.h>
#include <ant_channel_config.h>
#include <ant_profiles/env/pages/ant_env_pages.h>
#include <ant_host_init.h>

#define ENV_DEVICE_TYPE		0x00u
#define ENV_ANTPLUS_RF_FREQ	0x00u

typedef enum
{
	ANT_ENV_PAGE_0,
	ANT_ENV_PAGE_1,
} ant_env_page_t;

typedef enum
{
	ANT_ENV_PAGE_0_UPDATED = ANT_ENV_PAGE_0,
	ANT_ENV_PAGE_1_UPDATED = ANT_ENV_PAGE_1,
} ant_env_evt_t;

typedef struct ant_env_profile_s ant_env_profile_t;

typedef void (* ant_env_evt_handler_t) (ant_env_profile_t *, ant_env_evt_t);

typedef struct
{
} ant_env_sens_config_t;

struct ant_env_profile_s
{
	ant_env_page0_data_t page_0;
	ant_env_page1_data_t page_1;
};

int ant_env_sens_init(ant_env_profile_t * p_profile, 
		      ant_channel_config_t const * p_channel_config, 
		      ant_env_sens_config_t const p_sens_config);

int ant_env_sens_open();

int ant_env_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context);
