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
		time.start();
	}
}

void AnimatedGLWidget::tick()
{
	updateGL();
	tick((float)time.restart() / 1000);
}

void AnimatedGLWidget::hideEvent(QHideEvent* const)
{
	if(timer.isActive()) {
		timer.stop();
	}
}

