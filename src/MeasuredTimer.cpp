#include "MeasuredTimer.h"

#include <QEvent>
#include <QWidget>

namespace nt {

MeasuredTimer::MeasuredTimer(QObject* const parent, const int msec) :
	QObject(parent),
	msec(msec),
	time(),
	timer(this)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(dispatchTick()));
}

/**
 * This method along with eventFilter really should be in a separate class
 */
void MeasuredTimer::startOnShow(QWidget* const widget)
{
	widget->installEventFilter(this);
}

bool MeasuredTimer::eventFilter(QObject* obj, QEvent* event)
{
	switch (event->type()) {
		case QEvent::Show: start(); break;
		case QEvent::Hide: stop(); break;
		default: break;
	}
	return QObject::eventFilter(obj, event);
}

void MeasuredTimer::start()
{
	if (!timer.isActive()) {
		timer.start(msec);
		time.start();
	}
}

void MeasuredTimer::dispatchTick()
{
	emit timeout((float)time.restart() / 1000);
}

void MeasuredTimer::stop()
{
	if (timer.isActive()) {
		timer.stop();
	}
}

} // namespace nt
