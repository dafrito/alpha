#ifndef MEASUREDTIMER_H
#define MEASUREDTIMER_H

#include <QObject>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QWidget;
class QEvent;
QT_END_NAMESPACE



class MeasuredTimer : public QObject
{
	Q_OBJECT

	const int msec;
	QTime time;
	QTimer timer;
public:
	static const int DEFAULT_RATE = 60;

	MeasuredTimer(QObject* const parent = 0, const int msec = 1000 / DEFAULT_RATE);

	void startOnShow(QWidget* const widget);
	bool eventFilter(QObject* obj, QEvent* event);
signals:
	void timeout(const float& elapsed);
public slots:
	void start();
	void stop();
private slots:
	void dispatchTick();
};

#endif // MEASUREDTIMER_H
