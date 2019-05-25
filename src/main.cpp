#include "../../dashboard_shield/src/dashboard_shield.h"
#include "../../aemnet_utils/src/aemnet_utils.h"
#include "rpm.h"

void setup();
int write_shifting_lights(dashboard_shield::dashboard_t*, int, aemnet_utils::fixed_point_t);

rpm_limits rpm_lim;

int main(void){
  
  dashboard_shield::dashboard_t dash;
  aemnet_utils::fixed_point_t value;

  while(1){
	value = aemnet_utils::rpm(); // Get rpm
	write_shifting_lights(&dash, 0, value);
  }
  return 0;
}

void setup(){
  aemnet_utils::begin();
  dashboard_shield::begin();

  /* Compute rpm limits*/
  compute_rpm_limits(&rpm_lim);
}

int write_shifting_lights(dashboard_shield::dashboard_t* dash, int ch, aemnet_utils::fixed_point_t value){
  value >>= 16; // Remove decimal

  /* Turn all shifting lights off  */
  for(int i=0; i < RPM_LIGHTS; ++i){
	dash->pixel_channels[ch].pixels[i].red = 0;
	dash->pixel_channels[ch].pixels[i].grn = 0;
	dash->pixel_channels[ch].pixels[i].blu = 0;
	dash->pixel_channels[ch].pixels[i].wht = 0;
  }

  
  /* Turn all blue */
  if(value >= RPM_T4 /*&& value < RPM_T5*/){
	for(int i=0; i < RPM_LIGHTS; ++i){
	  dash->pixel_channels[ch].pixels[i].red = 0;
	  dash->pixel_channels[ch].pixels[i].grn = 0;
	  dash->pixel_channels[ch].pixels[i].blu = 255;
	  dash->pixel_channels[ch].pixels[i].wht = 0;
	}
	return 0;
  }

  /* Flashing blue or red */
  if(value >= RPM_T5){
	shifting_light_flash_toggle = !shifting_light_flash_toggle;
	for(int i=0; i < RPM_LIGHTS; ++i){
	  if(value < RPM_MAX)
		dash->pixel_channels[ch].pixels[i].blu = 255 * shifting_light_flash_toggle;
	  else
		dash->pixel_channels[ch].pixels[i].red = 255 * shifting_light_flash_toggle;
	}
	return 0;
  }

  /* Turn outermost lights green */
  if(value >= RPM_T1 /*&& value < RPM_T2*/){
	for(int i=rpm_lim.t1_start; i < rpm_lim.t1_end; i++){
	  dash->pixel_channels[ch].pixels[i].grn = 255;
	  dash->pixel_channels[ch].pixels[DS_PIXELS_PER_CHANNEL-i-1].grn = 255;
	}
  }

  /* Turn outer-mid lights yellow */
  if(value >= RPM_T2 /*&& value < RPM_T3*/){
    for(int i=rpm_lim.t1_end; i < rpm_lim.t2_end; i++){
      dash->pixel_channels[ch].pixels[i].red = 255;
	  dash->pixel_channels[ch].pixels[i].grn = 255;
	  dash->pixel_channels[ch].pixels[DS_PIXELS_PER_CHANNEL-i-1].red = 255;
      dash->pixel_channels[ch].pixels[DS_PIXELS_PER_CHANNEL-i-1].grn = 255;
    }
  }

  /* Turn mid lights red */
  if(value >= RPM_T3 /*&& value < RPM_T4*/){
    for(int i=rpm_lim.t2_end; i < rpm_lim.t3_end; i++){
      dash->pixel_channels[ch].pixels[i].red = 255;
    }
  }
  
  return 0;
}