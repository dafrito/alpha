#include "gl/ScreenGLWidget.hpp"

#include <GL/gl.h>

namespace nt {
namespace gl {

void ScreenGLWidget::paintGL()
{
    if (getScreen()) {
        getScreen()->render(_screenArea);
    }
}

void ScreenGLWidget::initializeGL()
{
    // Do nothing, at least for now. This may eventually
    // call a method on Screen to perform initialization.
}

void ScreenGLWidget::resizeGL(int width, int height)
{
    _screenArea.setLeft(0);
    _screenArea.setRight(width);
    _screenArea.setTop(0);
    _screenArea.setBottom(height);
}

void ScreenGLWidget::setScreen(const Screen* const screen)
{
    _screen = screen;
}

const Screen* ScreenGLWidget::getScreen() const
{
    return _screen;
}

} // namespace gl
} // namespace nt
