#ifndef LUAGLDEMO_H
#define LUAGLDEMO_H

#include <QWidget>
#include <QLineEdit>
#include "LuaGLWidget.h"
#include "Lua.hpp"

class LuaGLDemo : public QWidget
{
	Q_OBJECT

	LuaGLWidget* const glWidget;

	QLineEdit* const codeLine;

	Lua lua;

public slots:
	void updateWidget();

public:
	LuaGLDemo(QWidget* const parent = 0);
	~LuaGLDemo();
};

#endif // LUAGLDEMO_H
