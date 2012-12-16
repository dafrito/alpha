#ifndef ALPHA_RENDERLAYER_HEADER
#define ALPHA_RENDERLAYER_HEADER

#include "Vector3.h"

template <typename Scalar>
class RenderLayer
{
public:
    /**
     * Render this layer at the specified position. The position is provided
     * to allow for optimization for geometry that is either entirely occluded at
     * that position, or for geometry that is too distant to be rendered.
     * <p>
     * Only the camera transformation and perspective matrix has been set at this
     * point.
     */
    virtual void render(const Vector3<Scalar>& position)=0;
};

#endif // ALPHA_RENDERLAYER_HEADER
