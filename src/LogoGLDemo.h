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
    LogoGLDemo(QWidget* const parent = 0);

private:
    QSlider *createSlider() const;

    LogoGLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif // LOGOGLDEMO_H

// vim: set ts=4 sw=4 et! :
