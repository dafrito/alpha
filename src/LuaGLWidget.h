#ifndef LUAGLWIDGET_H
#define LUAGLWIDGET_H

#include "GLWidget.h"
#include "Lua.hpp"
#include "MeasuredTimer.h"

class Square : public QObject
{
	Q_OBJECT
	Q_PROPERTY(double x READ getX WRITE setX)
public:
	double x, y;
	void setX(double x)
	{
		this->x = x;
	}

	double getX()
	{
		return x;
	}

	void setY(double y)
	{
		this->y = y;
	}

	double getY()
	{
		return y;
	}
};

class LuaGLWidget : public GLWidget
{
	Q_OBJECT
	Lua lua;
	MeasuredTimer timer;
	Square square;
public:
	LuaGLWidget();
protected:
	void render();
private slots:
	void tick(const float& elapsed);
};

#endif // LUAGLWIDGET_H
