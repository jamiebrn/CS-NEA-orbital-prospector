//
// Misc.hpp
// 
// Contains miscellaneous functions that have a wide variety of applications
//

#ifndef MISC_FUNCTIONS_HPP
#define MISC_FUNCTIONS_HPP

#include <cmath>
#include <algorithm>

namespace Misc {

// Linearly interpolates value from start to destination, with specified weight 0-1.
inline float lerp(float start, float dest, float weight) {
    return start + weight * (dest - start);
}

// Similar to lerp, but contains extra steps to work correctly with angles in degrees
inline float lerpAngle(float start, float dest, float weight) {
    float dt = std::clamp(dest - start - std::floor((dest - start) / 360) * 360, 0.0f, 360.0f);
    if (dt > 180) {
        dt -= 360;
    }
    return lerp(start, start + dt, weight);
}

}

#endif