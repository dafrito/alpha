#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

#include <vector>
#include "gl/RenderLayer.hpp"
#include "gl/Camera.hpp"
#include <GL/gl.h>
#include "gl/util.hpp"
#include "Box2.hpp"

namespace nt {
namespace gl {

class ProjectionPerspective
{
    double _fov;

    double _viewDistance;

protected:

    ProjectionPerspective() :
        _fov(65),
        _viewDistance(800)
    {}

    void updatePerspective(const Box2<int>& viewArea) const
    {
        glViewport(viewArea);

        GLint oldMatrixMode;
        glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gl::setGLFrustum(
            _fov,
            (float)(viewArea.width() / viewArea.height()),
            1,
            _viewDistance
        );

        // Reset the old mode
        glMatrixMode(oldMatrixMode);
    }

public:

    const double& getFOV() const;
    void setFOV(const double& fov);

    const double& getViewDistance() const;
    void setViewDistance(const double& viewDistance);
};

template <typename Scalar, typename Perspective = ProjectionPerspective>
class Viewport : public Perspective
{
    typedef std::vector<RenderLayer<Scalar>*> RenderLayerList;

    Camera _camera;
    RenderLayerList _renderLayers;

    Vector3<Scalar> _cameraPos;

protected:
    void updatePerspective(const Box2<int>& viewArea) const;

public:
    void render(const Box2<int>& viewArea) const
    {
        updatePerspective(viewArea);
        glMatrixMode(GL_MODELVIEW);

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
