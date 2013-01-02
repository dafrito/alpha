#ifndef LUAGLWIDGET_H
#define LUAGLWIDGET_H

#include <QVector3D>

#include "GLWidget.hpp"
#include <lua-cxx/LuaEnvironment.hpp>
#include "Heights.hpp"
#include "MeasuredTimer.hpp"

using namespace std;

class LuaGLWidget : public GLWidget
{
	Q_OBJECT

	nt::MeasuredTimer timer;

	// The vertical scaling applied to each vertex. Higher
	// values mean higher peaks and lower troughs.
	static const int AMPLITUDE=2;

	Heights<float> heights;
public:
	LuaGLWidget(QWidget* const parent = 0);

	template <class F>
	void update(F func)
	{
		heights.update(func);
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

	float get(int x, int y)
	{
		return heights.get(x, y);
	}
protected slots:
	void tick(const double& elapsed);
protected:
	void render();
	void initializeGL();
	void resizeGL(int width, int height);
};

#endif // LUAGLWIDGET_H
