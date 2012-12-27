#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

#include <vector>
#include <GL/gl.h>
#include "Box2.hpp"

#include "gl/RenderLayer.hpp"
#include "gl/Physical.hpp"
#include "gl/Projection.hpp"
#include "gl/util.hpp"

namespace nt {
namespace gl {

class Viewport
{
    typedef std::vector<const RenderLayer*> RenderLayerList;

    RenderLayerList _renderLayers;

    Physical<double> _camera;

    const Projection* _projection;

public:
    Viewport();

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
