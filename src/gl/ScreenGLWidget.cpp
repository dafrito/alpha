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
    if (getScreen()) {
        getScreen()->initialize();
    }
}

void ScreenGLWidget::resizeGL(int width, int height)
{
    _screenArea.setLeft(0);
    _screenArea.setRight(width);
    _screenArea.setTop(0);
    _screenArea.setBottom(height);
}

void ScreenGLWidget::setScreen(Screen* const screen)
{
    _screen = screen;
}

} // namespace gl
} // namespace nt
