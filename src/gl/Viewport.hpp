#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

#include <vector>
#include "gl/RenderLayer.hpp"
#include <GL/gl.h>
#include "gl/util.hpp"
#include "Box2.hpp"
#include "gl/Physical.hpp"
#include "gl/Projection.hpp"

namespace nt {
namespace gl {

class Viewport
{
    typedef std::vector<const RenderLayer*> RenderLayerList;

    RenderLayerList _renderLayers;

    const Physical<double>* _camera;

    const Projection* _projection;

public:
    Viewport();

    void render(const Box2<int>& viewArea) const;

    const Projection* getProjection() const;
    void setProjection(const Projection* const projection);

    const Physical<double>* getCamera() const;
    void setCamera(const Physical<double>* const camera);

    void addRenderLayer(const RenderLayer* const layer);
    void removeRenderLayer(const RenderLayer* const layer);
};


} // namespace gl
} // namespace nt

#endif // ALPHA_VIEWPORT_HEADER
