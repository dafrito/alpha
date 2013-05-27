#ifndef MEASUREDTIMER_H
#define MEASUREDTIMER_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QWidget;
class QEvent;
QT_END_NAMESPACE

namespace nt {

class MeasuredTimer : public QObject
{
	Q_OBJECT

	const int msec;
	QElapsedTimer time;
	QTimer timer;

public:
	MeasuredTimer(const int msec, QObject* const parent = 0);

	void startOnShow(QWidget* const widget);
	bool eventFilter(QObject* obj, QEvent* event);
signals:
	void timeout(const double& elapsed);
public slots:
	void start();
	void stop();
private slots:
	void dispatchTick();
};

} // namespace nt

#endif // MEASUREDTIMER_H
