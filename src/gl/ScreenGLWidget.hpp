#ifndef ALPHA_SCREENGLWIDGET_HEADER
#define ALPHA_SCREENGLWIDGET_HEADER

#include <QGLWidget>
#include "Box2.hpp"
#include "gl/Screen.hpp"

namespace nt {
namespace gl {

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
    void setScreen(const Screen* const screen);
    const Screen* getScreen() const;
};

} // namespace gl
} // namespace nt

#endif // ALPHA_SCREENGLWIDGET_HEADER
