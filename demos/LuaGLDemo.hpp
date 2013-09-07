#ifndef LUAGLDEMO_H
#define LUAGLDEMO_H

#include <QWidget>
#include <QLineEdit>
#include "LuaGLWidget.hpp"
#include <lua-cxx/LuaEnvironment.hpp>

class LuaGLDemo : public QWidget
{
	Q_OBJECT

	LuaGLWidget* const glWidget;

	QLineEdit* const codeLine;

	LuaEnvironment lua;

public slots:
	void updateWidget();

public:
	LuaGLDemo(QWidget* const parent = 0);
	~LuaGLDemo();
};

#endif // LUAGLDEMO_H
