#ifndef SCALING_H
#define SCALING_H

#include "constants.h"
#include "../aemnet_utils/src/aemnet_utils.h"

typedef uint8_t (*scaling_function)(aemnet_utils::fixed_point_t);

/**
 * Add all required normalizing functions below
 * Ensure all values are scaled within STRIP_LIGHTS and RING_LIGHTS
 * Example:
 *     uint8_t rpm_to_strip(aemnet_utils::fixed_point_t value){
 *          return value / 10000;
 *     }
 * Min and max values required for scaling can be found in constants.h
 * Return negative value if out of bounds
 * 
 * Return the number of lights needed to be turned on
 */

#endif
