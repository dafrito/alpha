#ifndef BLANKGLWIDGET_H
#define BLANKGLWIDGET_H

#include "GLWidget.hpp"

class BlankGLWidget : public GLWidget
{
	void render();
};

void BlankGLWidget::render()
{
	// If there was rendering to be done, it would
	// be done here.
}

#endif // BLANKGLWIDGET_H
