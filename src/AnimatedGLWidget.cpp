#include "AnimatedGLWidget.h"

AnimatedGLWidget::AnimatedGLWidget(QWidget* const parent) :
	GLWidget(parent)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void AnimatedGLWidget::showEvent(QShowEvent* const)
{
	if(!timer.isActive()) {
		timer.start(1000 / 60);
	}
}

void AnimatedGLWidget::tick()
{
	updateGL();
}

void AnimatedGLWidget::hideEvent(QHideEvent* const)
{
	if(timer.isActive()) {
		timer.stop();
	}
}

