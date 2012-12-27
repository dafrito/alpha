#include "gl/Viewport.hpp"

#include <algorithm>

namespace nt {
namespace gl {

Viewport::Viewport() :
    _renderLayers(),
    _camera(0),
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

    if (_camera) {
        glTransform(*_camera);
    }

    for (RenderLayerList::const_iterator layer = _renderLayers.begin(); layer != _renderLayers.end(); ++layer) {
        (*layer)->render(_camera->getPosition());
    }
}

void Viewport::addRenderLayer(const RenderLayer* const layer)
{
    _renderLayers.push_back(layer);
}

void Viewport::removeRenderLayer(const RenderLayer* const layer)
{
    RenderLayerList::iterator newEnd =
        std::remove(_renderLayers.begin(), _renderLayers.end(), layer);
    _renderLayers.erase(newEnd, _renderLayers.end());
}

const Physical<double>* Viewport::getCamera() const
{
    return _camera;
}

void Viewport::setCamera(const Physical<double>* const camera)
{
    _camera = camera;
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
