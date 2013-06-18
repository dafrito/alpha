#include "LuaGLDemo.hpp"

#include <QtGui>
#include <QBoxLayout>
#include <iostream>
#include <lua-cxx/LuaException.hpp>
#include <lua-cxx/LuaStack.hpp>
#include <lua-cxx/LuaValue.hpp>

LuaGLDemo::LuaGLDemo(QWidget* const parent) :
	QWidget(parent),
	glWidget(new LuaGLWidget(this)),
	codeLine(new QLineEdit(this))
{
	QBoxLayout* const mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(mainLayout);

	connect(codeLine, SIGNAL(editingFinished()), this, SLOT(updateWidget()));
	mainLayout->addWidget(codeLine, 0);
	mainLayout->addWidget(glWidget, 1);

	codeLine->setText("function calc(x, z) return math.exp(x / 2) * math.sin(z) + math.random() / 4; end;");
	updateWidget();
}

void LuaGLDemo::updateWidget()
{
	try {
		Lua l;
		l(codeLine->text().toStdString());
		glWidget->update(l["calc"]);
	} catch (LuaException e) {
		std::cerr << e.what() << std::endl;
	}
}

LuaGLDemo::~LuaGLDemo()
{

}
