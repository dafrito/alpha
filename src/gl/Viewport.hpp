#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

#include <vector>
#include "gl/RenderLayer.hpp"
#include "gl/Camera.hpp"

namespace nt {
namespace gl {

class ProjectionPerspective
{
public:
    void updatePerspective(const int width, const int height) const;
};

template <typename Scalar, typename Perspective = ProjectionPerspective>
class Viewport : public Perspective
{
    typedef std::vector<RenderLayer<Scalar>*> RenderLayerList;

    Camera _camera;
    RenderLayerList _renderLayers;

    Vector3<Scalar> _cameraPos;
public:

    void render() const
    {
        for (typename RenderLayerList::const_iterator layer = _renderLayers.begin(); layer != _renderLayers.end(); ++layer) {
            (*layer)->render(_cameraPos);
        }
    }

    void addRenderLayer(const RenderLayer<Scalar>* const layer)
    {
        _renderLayers.push_back(layer);
    }

    void removeRenderLayer(const RenderLayer<Scalar>* const layer)
    {
        typename RenderLayerList::iterator newEnd =
            std::remove(_renderLayers.begin(), _renderLayers.end(), layer);
        _renderLayers.erase(newEnd, _renderLayers.end());
    }
};


} // namespace gl
} // namespace nt

#endif // ALPHA_VIEWPORT_HEADER
