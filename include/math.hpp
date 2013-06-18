#ifndef ALPHA_MATH_HEADER
#define ALPHA_MATH_HEADER

#include <boost/math/constants/constants.hpp>

namespace nt {

template <typename T>
void normalizeRadians(T& angle)
{
    const T PI_2 = 2 * boost::math::constants::pi<T>();
    while (angle < 0)
        angle += PI_2;
    while (angle >= PI_2)
        angle -= PI_2;
}

template <typename T>
void normalizeDegrees(T& angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
}

} // namespace nt

#endif // ALPHA_MATH_HEADER
