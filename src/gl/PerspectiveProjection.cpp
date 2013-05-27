#include "gl/PerspectiveProjection.hpp"

#include <GL/gl.h>
#include "gl/util.hpp"

namespace nt {
namespace gl {

void PerspectiveProjection::apply(const Box2<int>& viewArea) const
{
    glViewport(viewArea);

    GLint oldMatrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gl::setGLFrustum(
        _fov,
        static_cast<float>(viewArea.width()) /
        static_cast<float>(viewArea.height()),
        1,
        _viewDistance
    );

    // Reset the old mode
    glMatrixMode(oldMatrixMode);
}

void PerspectiveProjection::setFOV(const double& fov)
{
    _fov = fov;
}

const double& PerspectiveProjection::getFOV() const
{
    return _fov;
}

void PerspectiveProjection::setViewDistance(const double& viewDistance)
{
    _viewDistance = viewDistance;
}

const double& PerspectiveProjection::getViewDistance() const
{
    return _viewDistance;
}

} // namespace gl
} // namespace nt
