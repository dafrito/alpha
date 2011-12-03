#ifndef LUAGLWIDGET_H
#define LUAGLWIDGET_H

#include <QVector3D>

#include "GLWidget.h"
#include "Lua.hpp"
#include "MeasuredTimer.h"

using namespace std;

class LuaGLWidget : public GLWidget
{
	Q_OBJECT
	MeasuredTimer timer;

	// Proportional to the total amount of vertices rendered.
	// TODO Implement a display list so this value can be raised
	static const int HALFSIZE=50;

	// The vertical scaling applied to each vertex. Higher
	// values mean higher peaks and lower troughs.
	static const int AMPLITUDE=2;

	float heights[HALFSIZE*2][HALFSIZE*2];
public:
	LuaGLWidget(QWidget* const parent = 0);

	template <typename T>
	void update(T& func)
	{
		// The amount of compression between values. Higher values
		// cause a wider range of values to be shown.
		static const float FREQUENCY=.3;

		for (int y = -HALFSIZE; y < HALFSIZE; y++) {
			for (int x = -HALFSIZE; x < HALFSIZE; x++) {
				set(x, y, func(FREQUENCY*x, FREQUENCY*y));
			}
		}
	}

private:
	
	QVector3D normal(int x, int y)
	{
		QVector3D a(x, AMPLITUDE*get(x, y), y);
		QVector3D b(x, AMPLITUDE*get(x, y+1), y+1);
		QVector3D c(x+1, AMPLITUDE*get(x+1, y+1), y+1);
		return QVector3D::normal(a - b, b - c);
	}

	QVector3D average(const QVector3D& a, const QVector3D& b)
	{
		QVector3D r;
		r.setX((a.x() + b.x()) / 2);
		r.setY((a.y() + b.y()) / 2);
		r.setZ((a.z() + b.z()) / 2);
		return r;
	}

	void renderVertex(const QVector3D& vec)
	{
		glVertex3f(vec.x(), vec.y(), vec.z());
	}

	void renderNormal(const QVector3D& vec)
	{
		glNormal3f(vec.x(), vec.y(), vec.z());
	}

	void validate(int& x, int& y)
	{
		x = max(0, min(x + HALFSIZE, HALFSIZE * 2 - 1));
		y = max(0, min(y + HALFSIZE, HALFSIZE * 2 - 1));
	}
	
	void set(int x, int y, float value)
	{
		validate(x, y);
		heights[y][x] = value;
	}

	float get(int x, int y)
	{
		validate(x, y);
		return heights[y][x];
	}

protected:
	void render();
	void initializeGL();
	void resizeGL(int width, int height);
private slots:
	void tick(const float& elapsed);
};

#endif // LUAGLWIDGET_H
