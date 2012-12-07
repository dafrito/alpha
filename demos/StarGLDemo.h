#ifndef STARGLDEMO_H
#define STARGLDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
QT_END_NAMESPACE
class StarGLWidget;

class StarGLDemo : public QWidget
{
	Q_OBJECT
	
	StarGLWidget* const glWidget;
	QCheckBox* const showInsignificantEdgesOption;
public:
	StarGLDemo(QWidget* const parent = 0);
};

#endif // STARGLDEMO_H
