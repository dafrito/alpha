#ifndef ANIMATEDGLWIDGET_H
#define ANIMATEDGLWIDGET_H

#include <QTimer>
#include "GLWidget.h"

class AnimatedGLWidget : public GLWidget
{
	Q_OBJECT

	QTimer timer;
public:
	AnimatedGLWidget(QWidget* const parent = 0);
protected:
	void showEvent(QShowEvent* const);
	void hideEvent(QHideEvent* const);
protected slots:
	virtual void tick();
};

#endif // ANIMATEDGLWIDGET_H
