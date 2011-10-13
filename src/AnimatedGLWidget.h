#ifndef ANIMATEDGLWIDGET_H
#define ANIMATEDGLWIDGET_H

#include <QTime>
#include <QTimer>
#include "GLWidget.h"

class AnimatedGLWidget : public GLWidget
{
	Q_OBJECT

	QTime time;
	QTimer timer;
public:
	AnimatedGLWidget(QWidget* const parent = 0);
signals:
	void timeout(const float& elapsed);
protected:
	void showEvent(QShowEvent* const);
	void hideEvent(QHideEvent* const);
protected slots:
	virtual void tick(const float& elapsed)=0;
private slots:
	void dispatchTick();
};

#endif // ANIMATEDGLWIDGET_H
