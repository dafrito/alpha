#ifndef ALPHA_RENDERLAYER_HEADER
#define ALPHA_RENDERLAYER_HEADER

#include "gl/Physical.hpp"
#include "gl/Projection.hpp"

namespace nt {
namespace gl {

class RenderLayer
{
public:
    /**
     * Render this layer at the specified position. The position is provided
     * to allow for optimization for geometry that is either entirely occluded at
     * that position, or for geometry that is too distant to be rendered.
     * <p>
     * The position given is in the render layer's local coordinates. For instance, a
     * "world" render layer would have its position relative to the world origin.
     */
    virtual void render(const Physical<double>& position, const Projection& projection) const=0;
    virtual ~RenderLayer() {}
};

} // namespace gl
} // namespace nt

#endif // ALPHA_RENDERLAYER_HEADER
