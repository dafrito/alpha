#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

#include <vector>
#include <GL/gl.h>
#include "../Box2.hpp"
#include "../Physical.hpp"

#include "RenderLayer.hpp"
#include "Projection.hpp"
#include "util.hpp"

namespace nt {
namespace gl {

/**
 * A view into a scene of rendered objects.
 *
 * A Viewport is roughly a combination of a camera and rendered objects,
 * organized by their render layer.
 *
 * @see Screen
 * @see RenderLayer
 */
class Viewport
{
    std::vector<const RenderLayer*> _renderLayers;
    typedef decltype(_renderLayers) RenderLayerList;

    Physical<double> _camera;

    const Projection* _projection;

public:
    Viewport();

    /**
     * Render the scene into the specified screen coordinates.
     */
    void render(const Box2<int>& viewArea) const;

    const Projection* getProjection() const;
    void setProjection(const Projection* const projection);

    const Physical<double>& getCamera() const;
    Physical<double>& getCamera();

    void addRenderLayer(const RenderLayer* const layer);
    void removeRenderLayer(const RenderLayer* const layer);
};


} // namespace gl
} // namespace nt

#endif // ALPHA_VIEWPORT_HEADER
