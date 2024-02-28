// Helper.hpp
// 
// Contains "helper" functions that have a wide variety of applications

#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

// Helper namespace, where "helper" functions are defined
namespace Helper {

// Linearly interpolates value from start to destination, with specified weight 0-1.
inline float lerp(float start, float dest, float weight)
{
    return start + weight * (dest - start);
}

// Similar to lerp, but contains extra steps to work correctly with angles in degrees
inline sf::Angle lerpAngle(sf::Angle startAngle, sf::Angle destAngle, float weight)
{
    float start = startAngle.asDegrees();
    float dest = destAngle.asDegrees();

    float dt = std::clamp(dest - start - std::floor((dest - start) / 360) * 360, 0.0f, 360.0f);
    if (dt > 180)
        dt -= 360;

    float lerpedAngle = lerp(start, start + dt, weight);

    return sf::degrees(lerpedAngle);
}

// Calculates multiplier to convert a depth-modified position back to standard depth
inline float unprojectDepthMultiplier(float initDepth, float destDepth)
{
    float diff = destDepth - initDepth;
    float mult = destDepth * initDepth;
    float multiplier = diff / mult;

    return multiplier;
}

}

#endif