#include <QtGui>
#include <cassert>

#include "StarGLWidget.hpp"
#include "StarGLDemo.hpp"

StarGLDemo::StarGLDemo(QWidget* const parent) :
	QWidget(parent),
	glWidget(new StarGLWidget(this)),
	showInsignificantEdgesOption(new QCheckBox("Show Insignificant Edges"))
{
	QBoxLayout* const mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(mainLayout);

	showInsignificantEdgesOption->setChecked(true);
	showInsignificantEdgesOption->setToolTip("Sets whether the interior edges of the polygon are shown.");
	connect(showInsignificantEdgesOption, SIGNAL(toggled(bool)), glWidget, SLOT(showInsignificantEdges(bool)));
	mainLayout->addWidget(showInsignificantEdgesOption, 0);

	mainLayout->addWidget(glWidget, 1);
}
