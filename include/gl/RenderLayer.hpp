#ifndef ALPHA_RENDERLAYER_HEADER
#define ALPHA_RENDERLAYER_HEADER

#include "../Physical.hpp"
#include "Projection.hpp"

namespace nt {
namespace gl {

/**
 * Represents a method for rendering objects.
 *
 * The method of rendering is left intentionally vague. This allows for different objects to
 * be rendered using a strategy tailored to them. For example, some render layers may render
 * from a list of objects, while others may render directly using a grid.
 *
 * @see DirectRenderLayer
 * @see VoxmapRenderLayer
 */
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
