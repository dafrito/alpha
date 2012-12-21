#ifndef ALPHA_DIRECTRENDERLAYER_HEADER
#define ALPHA_DIRECTRENDERLAYER_HEADER

#include "gl/RenderLayer.hpp"
#include "gl/Renderable.hpp"
#include "gl/util.h"

#include <vector>
#include <algorithm>

namespace nt {
namespace gl {

struct GLTransform
{
    template <class Scalar>
    static void transform(const Physical<Scalar>& physical)
    {
        glTranslate(physical.getPosition());
        glRotateRadians(physical.getRotation());
    }
};

/**
 * A layer that contains a list of renderable objects. This is called a
 * "direct" render layer because the objects that are rendered directly:
 * their physical location is used without modification to translate the
 * object in space, and the renderer function is wholly responsible for
 * drawing the object. This is in contrast with other layers that do not have
 * a one-to-one representation of rendered geometery to objects.
 */
template <typename Scalar, typename Renderer, typename Transformer = GLTransform>
class DirectRenderLayer : public RenderLayer<Scalar>, private Transformer
{
public:
    typedef Renderable<Scalar, Renderer> RenderableType;
    typedef std::vector<RenderableType*> RenderableList;

protected:
    RenderableList renderables;

public:
    void add(Renderable<Scalar, Renderer>& renderable)
    {
        renderables.push_back(&renderable);
    }

    void remove(Renderable<Scalar, Renderer>& renderable)
    {
        typename RenderableList::iterator pos =
            std::remove(renderables.begin(), renderables.end(), &renderable);
        renderables.erase(pos, renderables.end());
    }

    int numRenderables() const
    {
        return renderables.size();
    }

    void render(const Vector3<Scalar>& position)
    {
        for (typename RenderableList::const_iterator i = renderables.begin(); i != renderables.end(); ++i) {
            const RenderableType* const renderable = *i;
            this->transform(*renderable->physical);
            renderable->renderer();
        }
    }
};

} // namespace gl
} // namespace nt

#endif // ALPHA_DIRECTRENDERLAYER_HEADER
