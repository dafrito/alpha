#ifndef LOGOGLDEMO_H
#define LOGOGLDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE
class LogoGLWidget;

class LogoGLDemo : public QWidget
{
    Q_OBJECT

public:
    LogoGLDemo();

private:
    QSlider *createSlider();

    LogoGLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif // LOGOGLDEMO_H
