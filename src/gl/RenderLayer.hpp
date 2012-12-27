#ifndef ALPHA_RENDERLAYER_HEADER
#define ALPHA_RENDERLAYER_HEADER

#include "Vector3.hpp"

namespace nt {
namespace gl {

template <typename Scalar>
class RenderLayer
{
public:
    /**
     * Render this layer at the specified position. The position is provided
     * to allow for optimization for geometry that is either entirely occluded at
     * that position, or for geometry that is too distant to be rendered.
     * <p>
     * The position given is in the render layer's local coordinates. For instance, a
     * "world" render layer would have its position relative to the world coordinates.
     */
    virtual void render(const Vector3<Scalar>& position)=0;
    virtual ~RenderLayer() {}
};

} // namespace gl
} // namespace nt

#endif // ALPHA_RENDERLAYER_HEADER