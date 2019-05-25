#ifndef RPM_H
#define RPM_H

struct rpm_limits{
  uint8_t t1_start;
  uint8_t t1_end;
  uint8_t t2_end;
  uint8_t t3_end;
};

#define RPM_NORMALIZING_VAL 461.5384615385

#define RPM_LIGHTS 16

#define RPM_T1  8000  // Outer x lights in green
#define RPM_T2  8750  // Outer 2x lights in yellow
#define RPM_T3  9500  // All lights on. Middle in red
#define RPM_T4  10000 // All blue - shift point soon
#define RPM_T5  10800 // All blue flash - shift point now
#define RPM_MAX 11500 // All red flash - final warning

static void compute_rpm_limits(rpm_limits* rpm_lim){
  rpm_lim->t1_start = 0;
  rpm_lim->t1_end   = ((RPM_LIGHTS/2 - RPM_LIGHTS/8)) / 2;
  rpm_lim->t2_end   = (RPM_LIGHTS/2 - RPM_LIGHTS/8);
  rpm_lim->t3_end   = (RPM_LIGHTS - (2 * (RPM_LIGHTS/2 - RPM_LIGHTS/8))) + rpm_lim->t2_end;
}

uint8_t shifting_light_flash_toggle = 0;

#endif
