#include "AnimatedGLWidget.hpp"

AnimatedGLWidget::AnimatedGLWidget(QWidget* const parent) :
	GLWidget(parent),
	timer(1000 / 60, this)
{
	connect(&timer, SIGNAL(timeout(const double&)), this, SLOT(updateGL()));
	connect(&timer, SIGNAL(timeout(const double&)), this, SLOT(tick(const double&)));
	timer.startOnShow(this);
	updateOnCameraMove(false);
}
