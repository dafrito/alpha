#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget() {}

	QSize minimumSizeHint() const
	{
		return QSize(50, 50);
	}

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	virtual void render()=0;
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);

	void paintGL();
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
};

#endif // GLWIDGET_H
