#ifndef ALPHA_MATH_HEADER
#define ALPHA_MATH_HEADER

namespace nt {

template <typename T>
void normalizeRadians(T& angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
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
