#include <QTabWidget>
#include <QKeyEvent>

class DemoTabWidget : public QTabWidget
{
	Q_OBJECT

private slots:
	void updateTitle(int index)
	{
		if (index == -1) {
			setWindowTitle("Demo");
		} else {
			QString title = tabText(index);
			if (title != "") {
				setWindowTitle(QString("Demo - ") + title);
			} else {
				setWindowTitle("Demo");
			}
		}
	}
protected:

	void keyPressEvent(QKeyEvent* event)
	{
		if (event->key() == Qt::Key_Escape) {
			close();
		} else {
			QWidget::keyPressEvent(event);
		}
	}
public:
	DemoTabWidget() : QTabWidget()
	{
		connect(this, SIGNAL(currentChanged(int)), this, SLOT(updateTitle(int)));
	}
};

