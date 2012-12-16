#ifndef ALPHA_PHYSICAL_HEADER
#define ALPHA_PHYSICAL_HEADER

#include "Vector3.h"

/**
 * Represents a position and orientation in Euclidean space.
 */
template <typename Scalar>
class Physical
{
public:
    typedef Vector3<Scalar> Position;
    typedef Vector3<Scalar> Rotation;

protected:
    Position position;
    Rotation rotation;

public:

    const Position& getPosition() const
    {
        return position;
    }

    const Rotation& getRotation() const
    {
        return rotation;
    }
};

#endif // ALPHA_PHYSICAL_HEADER
