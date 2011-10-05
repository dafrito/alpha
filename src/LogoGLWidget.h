#ifndef LOGOGLWIDGET_H
#define LOGOWGLIDGET_H

#include "GLWidget.h"

class Logo;

class LogoGLWidget : public GLWidget
{
    Q_OBJECT

public:
    LogoGLWidget(QWidget* const parent = 0);
    ~LogoGLWidget();

protected:
    void initializeGL();
    void render();
    void resizeGL(const int width, const int height);

private:
    Logo* logo;
    const QColor qtGreen;
    const QColor qtOrange;
};

#endif // LOGOGLWIDGET_H
