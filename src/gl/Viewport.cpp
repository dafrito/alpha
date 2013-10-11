#include "gl/Viewport.hpp"

#include <algorithm>

namespace nt {
namespace gl {

Viewport::Viewport() :
    _renderLayers(),
    _camera(),
    _projection(0)
{}

void Viewport::render(const Box2<int>& viewArea) const
{
    if (!_projection) {
        return;
    }
    _projection->apply(viewArea);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glReverseTransform(_camera);

    for (auto layer : _renderLayers) {
        layer->render(_camera, *_projection);
    }
}

void Viewport::addRenderLayer(RenderLayer* const layer)
{
    _renderLayers.push_back(layer);
}

void Viewport::removeRenderLayer(RenderLayer* const layer)
{
    _renderLayers.erase(
        std::remove(begin(_renderLayers), end(_renderLayers), layer),
        _renderLayers.end()
    );
}

const Physical<double>& Viewport::getCamera() const
{
    return _camera;
}

Physical<double>& Viewport::getCamera()
{
    return _camera;
}

const Projection* Viewport::getProjection() const
{
    return _projection;
}

void Viewport::setProjection(const Projection* const projection)
{
    _projection = projection;
}

} // namespace gl
} // namespace nt
