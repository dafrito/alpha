#include <QtGui>

#include "LuaGLDemo.h"

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
}

void LuaGLDemo::updateWidget()
{
	qDebug(qPrintable(codeLine->text()));
}

LuaGLDemo::~LuaGLDemo()
{

}
