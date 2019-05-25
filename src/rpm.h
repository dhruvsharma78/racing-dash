#ifndef RPM_H
#define RPM_H

#include "constants.h"

struct rpm_limits{
  uint8_t t1_start;
  uint8_t t1_end;
  uint8_t t2_end;
  uint8_t t3_end;
};

#define RPM_T1  8000  // Outer x lights in green
#define RPM_T2  8750  // Outer 2x lights in yellow
#define RPM_T3  9500  // All lights on. Middle in red
#define RPM_T4  10000 // All blue - shift point soon
#define RPM_T5  10800 // All blue flash - shift point now

static void compute_rpm_limits(rpm_limits* rpm_lim){
  rpm_lim->t1_start = 0;
  rpm_lim->t1_end   = ((STRIP_LIGHTS/2 - STRIP_LIGHTS/8)) / 2;
  rpm_lim->t2_end   = (STRIP_LIGHTS/2 - STRIP_LIGHTS/8);
  rpm_lim->t3_end   = (STRIP_LIGHTS - (2 * (STRIP_LIGHTS/2 - STRIP_LIGHTS/8))) + rpm_lim->t2_end;
}

uint8_t shifting_light_flash_toggle = 0;

#endif
