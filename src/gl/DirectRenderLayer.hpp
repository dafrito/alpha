#ifndef ALPHA_DIRECTRENDERLAYER_HEADER
#define ALPHA_DIRECTRENDERLAYER_HEADER

#include "gl/RenderLayer.hpp"
#include "gl/util.hpp"
#include "gl/Projection.hpp"

#include "Physical.hpp"

#include <GL/gl.h>

#include <vector>
#include <algorithm>
#include <functional>

namespace nt {
namespace gl {

template <typename Scalar>
struct Renderable;

/**
 * A layer that contains a list of renderable objects. This is called a
 * "direct" render layer because the objects that are rendered directly:
 * their physical location is used without modification to translate the
 * object in space, and the renderer function is wholly responsible for
 * drawing the object. This is in contrast with other layers that do not have
 * a one-to-one representation of rendered geometery to objects.
 */
template <typename Scalar>
class DirectRenderLayer : public RenderLayer
{
    typedef Renderable<Scalar> RenderableType;
    typedef std::vector<RenderableType> RenderableList;
    RenderableList renderables;

public:
    void add(Physical<Scalar>* const physical, const std::function<void()> renderer)
    {
        renderables.push_back(RenderableType(physical, renderer));
    }

    void render(const Physical<double>&, const Projection& projection) const
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        for (typename RenderableList::const_iterator i = renderables.begin(); i != renderables.end(); ++i) {
            const RenderableType& renderable(*i);
            glTranslate(renderable.physical->getPosition());
            glRotateRadians(renderable.physical->getRotation());
            renderable.renderer();
        }

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

    int numRenderables() const
    {
        return renderables.size();
    }

    void remove(Physical<Scalar>* const physical)
    {
        typename RenderableList::iterator pos =
            std::remove_if(renderables.begin(), renderables.end(),
                [&](const Renderable<Scalar>& renderable){ return renderable.physical == physical; });
        renderables.erase(pos, renderables.end());
    }
};

/**
 * Represents something that can be rendered. Specifically,
 * it requires a physical location, as well as a renderer
 * that can draw the geometry at that location.
 */
template <typename Scalar>
struct Renderable
{
    Physical<Scalar>* physical;
    std::function<void()> renderer;

    Renderable(Physical<Scalar>* const physical, const std::function<void()>& renderer) :
        physical(physical),
        renderer(renderer)
    {}
};

} // namespace gl
} // namespace nt

#endif // ALPHA_DIRECTRENDERLAYER_HEADER
