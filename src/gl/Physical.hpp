#ifndef ALPHA_PHYSICAL_HEADER
#define ALPHA_PHYSICAL_HEADER

#include "Vector3.hpp"

namespace nt {
namespace gl {

/**
 * Represents a position and orientation in Euclidean space.
 */
template <typename Scalar>
class Physical
{
public:
    typedef Vector3<Scalar> Position;
    typedef Vector3<Scalar> Rotation;

    Position _position;
    Rotation _rotation;
public:

    const Position& getPosition() const
    {
        return _position;
    }

    const Rotation& getRotation() const
    {
        return _rotation;
    }
};

} // namespace gl
} // namespace nt

#endif // ALPHA_PHYSICAL_HEADER
