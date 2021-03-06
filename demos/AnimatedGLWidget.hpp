#ifndef ANIMATEDGLWIDGET_H
#define ANIMATEDGLWIDGET_H

#include <QTime>
#include <QTimer>
#include "GLWidget.hpp"
#include "MeasuredTimer.hpp"

QT_BEGIN_NAMESPACE
class QShowEvent;
class QHideEvent;
QT_END_NAMESPACE

class AnimatedGLWidget : public GLWidget
{
	Q_OBJECT

	nt::MeasuredTimer timer;
public:
	AnimatedGLWidget(QWidget* const parent = 0);
protected slots:
	virtual void tick(const double& elapsed)=0;
};

#endif // ANIMATEDGLWIDGET_H
