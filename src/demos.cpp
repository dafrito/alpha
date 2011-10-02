#include <QApplication>
#include <QDesktopWidget>
#include <QTabWidget>
#include <QKeyEvent>

#include "SpiralGLDemo.h"
#include "BlankGLDemo.h"
#include "LogoGLDemo.h"

class DemoTabWidget : public QTabWidget
{
protected:

	void keyPressEvent(QKeyEvent* event)
	{
		if (event->key() == Qt::Key_Escape) {
			close();
		} else {
			QWidget::keyPressEvent(event);
		}
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSize appSize(800, 600);

	DemoTabWidget demoStack;
	demoStack.resize(appSize);

	BlankGLDemo blankDemo;
	demoStack.addTab(&blankDemo, "Blank");

	SpiralGLDemo spiralDemo;
	demoStack.addTab(&spiralDemo, "Spiral");

	LogoGLDemo logoDemo;
	demoStack.addTab(&logoDemo, "Logo");

	// Display most recently added tab.
	demoStack.setCurrentIndex(demoStack.count() -1);

	QDesktopWidget* desktop = QApplication::desktop();

	int desktopArea = desktop->width() * desktop->height();
	int appArea = appSize.width() * appSize.height();
	if (((float)appArea / (float)desktopArea) > 0.75f) {
		// Just maximize it if the desktop isn't significantly
		// bigger than our app's area.
		demoStack.showMaximized();
	} else {
		// Center the app on the primary monitor.
		QPoint windowLocation = desktop->screenGeometry(desktop->primaryScreen()).center();
		windowLocation.setX(windowLocation.x() - appSize.width() / 2);
		windowLocation.setY(windowLocation.y() - appSize.height() / 2);
		demoStack.move(windowLocation);
		demoStack.show();
	}

	return app.exec();
}
