#include "gl/GLOperation.hpp"

#include <GL/gl.h>

namespace nt {
namespace gl {

GLOperation& GLOperation::pushMatrix()
{
    glPushMatrix();
    operations.push_back(OP_popMatrix);

    return *this;
}

GLOperation& GLOperation::beginQuads()
{
    glBegin(GL_QUADS);
    operations.push_back(OP_end);

    return *this;
}

GLOperation& GLOperation::pop()
{
    while (operations.size() > 0) {
        glOperation op = operations.back();
        switch (op) {
            case OP_popMatrix:
                glPopMatrix();
                break;
            case OP_end:
                glEnd();
                break;
        }
        operations.pop_back();
    }

    return *this;
}

GLOperation::~GLOperation()
{
    pop();
}

} // namespace gl
} // namespace nt
