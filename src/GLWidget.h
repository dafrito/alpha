#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget* const parent = 0);
	~GLWidget() {}

	QSize minimumSizeHint() const
	{
		return QSize(50, 50);
	}

public slots:
	void setXRotation(int angle)
	{
		setScaledXRotation(angle * GLWidget::ROTATION_SCALE);
	}

	void setYRotation(int angle)
	{
		setScaledYRotation(angle * GLWidget::ROTATION_SCALE);
	}

	void setZRotation(int angle)
	{
		setScaledZRotation(angle * GLWidget::ROTATION_SCALE);
	}

	void setScaledXRotation(int angle);
	void setScaledYRotation(int angle);
	void setScaledZRotation(int angle);
signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	virtual void render()=0;
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);

	void paintGL();
	void applyRotation() const;
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	// We scale rotation such that 1 unit of xRot, yRot, or zRot is
	// equal to 1/ROTATION_SCALE degrees. Therefore, when you want to
	// set rotation, you need to multiply by this scale to get expected
	// results:
	//
	// xRot = 45 * ROTATION_SCALE; // xRot is now 45 degrees
	static const int ROTATION_SCALE = 16;

	void qNormalizeAngle(int &angle) const
	{
		while (angle < 0)
			angle += 360 * GLWidget::ROTATION_SCALE;
		while (angle > 360 * GLWidget::ROTATION_SCALE)
			angle -= 360 * GLWidget::ROTATION_SCALE;
	}

private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
};

#endif // GLWIDGET_H
