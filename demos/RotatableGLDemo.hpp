#ifndef ROTATABLEGLDEMO_H
#define ROTATABLEGLDEMO_H

#include <QWidget>
#include <QSlider>

class GLWidget;

class RotatableGLDemo : public QWidget
{
    Q_OBJECT

public:
    RotatableGLDemo(GLWidget* const widget, QWidget* const parent = 0);

private:
    QSlider *createSlider() const;

    GLWidget* const glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif // ROTATABLEGLDEMO_H

// vim: set ts=4 sw=4 et! :
