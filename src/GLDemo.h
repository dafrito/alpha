#ifndef GLDEMO_H
#define GLDEMO_H

#include <QGLWidget>

class GLDemo : public QGLWidget
{
    Q_OBJECT

public:
    GLDemo(QWidget *parent = 0);
    ~GLDemo() {}

    QSize minimumSizeHint() const
    {
        return QSize(50, 50);
    }

    QSize sizeHint() const
    {
        return QSize(400, 400);
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
};

#endif // GLDEMO_H
