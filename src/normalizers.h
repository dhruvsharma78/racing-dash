#ifndef NORMALIZERS_H
#define NORMALIZERS_H

#include "constants.h"
#include "../aemnet_utils/src/aemnet_utils.h"

typedef uint8_t (*normalizing_function)(aemnet_utils::fixed_point_t);

/**
 * Add all required normalizing functions below
 * Ensure all values are normalized within STRIP_LIGHTS and RING_LIGHTS
 * Example:
 *     uint8_t rpm_to_strip(aemnet_utils::fixed_point_t value){
 *          return value*2;
 *     }
 * Min and max values required for normalizing can be found in constants.h
 * Return negative value if out of bounds
 */

#endif
