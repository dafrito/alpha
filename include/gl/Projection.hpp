#ifndef ALPHA_PROJECTION_HEADER
#define ALPHA_PROJECTION_HEADER

#include "../Box2.hpp"

namespace nt {
namespace gl {

/**
 * Astrategy for setting up a projection matrix.
 *
 * This class currently does little more than provide a simple way to
 * apply a perspective or orthogonal projection. However, I anticipate
 * methods being added that will allow querying points to determine
 * if they're visible. This would let rendering strategies omit objects
 * that they can prove are not visible from the camera.
 *
 * @see PerspectiveProjection
 */
class Projection
{
public:

    /**
     * Apply this projection matrix, using the specified area
     * as the viewport.
     */
    virtual void apply(const Box2<int>& viewArea) const=0;
};

} // namespace gl
} // namespace nt

#endif // ALPHA_PROJECTION_HEADER
