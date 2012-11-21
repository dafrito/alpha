#include <QMouseEvent>
#include <QKeyEvent>

#include "PlayerInput.h"

// XXX: not set up so you can do single actions on key down
/* XXX:
keyPressEvent() is called whenever a key is pressed, and again when a key has been held down long enough for it to auto-repeat. The Tab and Shift+Tab keys are only passed to the widget if they are not used by the focus-change mechanisms. To force those keys to be processed by your widget, you must reimplement QWidget::event().
*/
bool PlayerInput::handleKeyPress(QKeyEvent* const event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = true; break;
		case Qt::Key_S: pad.backward = true; break;
		case Qt::Key_A: pad.turnLeft = true; break;
		case Qt::Key_D: pad.turnRight = true; break;
		case Qt::Key_Space: pad.verticalUp = true; break;
		case Qt::Key_X: pad.verticalDown = true; break;
		case Qt::Key_E: pad.pitchUp = true; break;
		case Qt::Key_Q: pad.pitchDown = true; break;
		case Qt::Key_1: pad.strafeLeft = true; break;
		case Qt::Key_2: pad.strafeRight = true; break;
		case Qt::Key_F1: pad.switchTarget = true; break;
		case Qt::Key_9: pad.rollLeft = true; break;
		case Qt::Key_0: pad.rollRight = true; break;
		default:
			return false;
	}
	return true;
}

bool PlayerInput::handleKeyRelease(QKeyEvent* const event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = false; break;
		case Qt::Key_S: pad.backward = false; break;
		case Qt::Key_A: pad.turnLeft = false; break;
		case Qt::Key_D: pad.turnRight = false; break;
		case Qt::Key_Space: pad.verticalUp = false; break;
		case Qt::Key_X: pad.verticalDown = false; break;
		case Qt::Key_E: pad.pitchUp = false; break;
		case Qt::Key_Q: pad.pitchDown = false; break;
		case Qt::Key_1: pad.strafeLeft = false; break;
		case Qt::Key_2: pad.strafeRight = false; break;
		case Qt::Key_F1: pad.switchTarget = false; break;
		case Qt::Key_9: pad.rollLeft = false; break;
		case Qt::Key_0: pad.rollRight = false; break;
		default:
			return false;
	}
	return true;
}

bool PlayerInput::handleMousePress(QMouseEvent* const event)
{
	switch (event->button()) {
		case Qt::LeftButton: pad.leftMouse = true; break;
		case Qt::RightButton: pad.rightMouse = true; break;
		default:
			return false;
	}
	return true;
}

bool PlayerInput::handleMouseRelease(QMouseEvent* const event)
{
	switch (event->button()) {
		case Qt::LeftButton: pad.leftMouse = false; break;
		case Qt::RightButton: pad.rightMouse = false; break;
		default:
			return false;
	}
	return true;
}
