#include "Viewport.hpp"

#include <GL/gl.h>
#include "gl/util.hpp"

namespace nt {
namespace gl {

void ProjectionPerspective::updatePerspective(const int width, const int height) const
{
    // XXX These should eventually be pulled into the Viewport
    static const double FOV = 65;
    static const double VIEW_DISTANCE = 800;

    glViewport(0, 0, width, height);

    GLint oldMatrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gl::setGLFrustum(
        FOV,
        (float)(width / height),
        1,
        VIEW_DISTANCE
    );

    // Reset the old mode
    glMatrixMode(oldMatrixMode);
}

} // namespace gl
} // namespace nt
