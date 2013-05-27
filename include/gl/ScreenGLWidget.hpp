#ifndef ALPHA_SCREENGLWIDGET_HEADER
#define ALPHA_SCREENGLWIDGET_HEADER

#include <QGLWidget>
#include "../Box2.hpp"
#include "Screen.hpp"

namespace nt {
namespace gl {

/**
 * A Qt-specific wrapper of a Screen.
 *
 * ScreenGLWidget takes care of the Qt-specific setup and behavior
 * necessary to render an OpenGL scene. As such, it is a relatively
 * light class. Most of the heavyweight behavior is contained within
 * the screen and the render layers themselves.
 *
 * @see Screen
 * @see RenderLayer
 */
class ScreenGLWidget : public QGLWidget
{
    Q_OBJECT

    const Screen* _screen;
    Box2<int> _screenArea;

protected:
    void paintGL();
    void initializeGL();
    void resizeGL(int width, int height);

public:
    ScreenGLWidget(const QGLFormat& format, QWidget* const parent = 0) :
        QGLWidget(format, parent),
        _screen(nullptr)
    {
    }

    ScreenGLWidget(QWidget* const parent = 0) :
        QGLWidget(parent),
        _screen(nullptr)
    {
    }

    void setScreen(const Screen* const screen);
    const Screen* getScreen() const;
};

} // namespace gl
} // namespace nt

#endif // ALPHA_SCREENGLWIDGET_HEADER
