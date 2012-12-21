#include "AnimatedGLWidget.hpp"

AnimatedGLWidget::AnimatedGLWidget(QWidget* const parent) :
	GLWidget(parent),
	timer(this)
{
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	timer.startOnShow(this);
	updateOnCameraMove(false);
}
