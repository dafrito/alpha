#ifndef ALPHA_RENDERABLE_HEADER
#define ALPHA_RENDERABLE_HEADER

#include "gl/Physical.hpp"

namespace nt {
namespace gl {

/**
 * Represents something that can be rendered. Specifically,
 * it requires a physical location, as well as a renderer
 * that can draw the geometry at that location.
 */
template <typename Scalar, typename Renderer>
struct Renderable
{
    Physical<Scalar>* const physical;
    Renderer* const renderer;

    Renderable(
        Physical<Scalar>* const physical,
        Renderer* const renderer) :
        physical(physical),
        renderer(renderer)
    {}
};

} // namespace gl
} // namespace nt

#endif // ALPHA_RENDERABLE_HEADER
