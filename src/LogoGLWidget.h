#ifndef LOGOGLWIDGET_H
#define LOGOWGLIDGET_H

#include "GLWidget.h"

class Logo;

class LogoGLWidget : public GLWidget
{
    Q_OBJECT

public:
    LogoGLWidget();
    ~LogoGLWidget();

protected:
    void initializeGL();
    void render();
    void resizeGL(int width, int height);

private:
    Logo *logo;
    QColor qtGreen;
    QColor qtOrange;
};

#endif // LOGOGLWIDGET_H
