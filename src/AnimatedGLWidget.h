#ifndef ANIMATEDGLWIDGET_H
#define ANIMATEDGLWIDGET_H

#include <QTime>
#include <QTimer>
#include "GLWidget.h"
#include "MeasuredTimer.h"

QT_BEGIN_NAMESPACE
class QShowEvent;
class QHideEvent;
QT_END_NAMESPACE

class AnimatedGLWidget : public GLWidget
{
	Q_OBJECT

	MeasuredTimer timer;
public:
	AnimatedGLWidget(QWidget* const parent = 0);
protected slots:
	virtual void tick(const float& elapsed)=0;
};

#endif // ANIMATEDGLWIDGET_H
