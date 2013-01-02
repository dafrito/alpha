#ifndef FONTGLWIDGET_H
#define FONTGLWIDGET_H

#include "AnimatedGLWidget.hpp"

class FontGLWidget : public AnimatedGLWidget
{
    Q_OBJECT

	float rotation;
	static const int FONT_SIZE = 18;
	static const int ROTATION_SPEED = 30;
public:
	FontGLWidget(QWidget* const parent = 0);
protected:
	void initializeGL();
	void tick(const double& elapsed);
	void render();
};

#endif // FONTGLWIDGET_H
