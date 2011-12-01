#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

QT_BEGIN_NAMESPACE
class QKeyEvent;
class QMouseEvent;
QT_END_NAMESPACE

// XXX: hardcoded keybinds
struct KeyBinds
{
	bool forward;
	bool backward;
	bool turnLeft;
	bool turnRight;
	bool strafeLeft;
	bool strafeRight;
	bool verticalUp;
	bool verticalDown;
	bool pitchUp; // aim up
	bool pitchDown; // aim down
	bool rollLeft;
	bool rollRight;

	bool leftMouse;	// mouse clicks
	bool rightMouse;

	bool switchTarget;
	KeyBinds() :
	forward(false),
	backward(false),
	turnLeft(false),
	turnRight(false),
	strafeLeft(false),
	strafeRight(false),
	verticalUp(false),
	verticalDown(false),
	pitchUp(false),
	pitchDown(false),
	rollLeft(false),
	rollRight(false),
	leftMouse(false),
	rightMouse(false),
	switchTarget(false)
	{};
};

class PlayerInput
{
	KeyBinds pad;
public:
	bool handleKeyPress(QKeyEvent* event);
	bool handleKeyRelease(QKeyEvent* event);
	bool handleMousePress(QMouseEvent* event);
	bool handleMouseRelease(QMouseEvent* event);

	bool strafeLeft()
	{
		return pad.strafeLeft && !pad.strafeRight;
	}

	bool strafeRight()
	{
		return pad.strafeRight && !pad.strafeLeft;
	}

	bool turnLeft()
	{
		return pad.turnLeft && !pad.turnRight;
	}

	bool turnRight()
	{
		return pad.turnRight && !pad.turnLeft;
	}

	bool moveForward()
	{
		return !pad.backward && (
			(pad.leftMouse && pad.rightMouse) ||
			pad.forward);
	}

	bool moveBackward()
	{
		return pad.backward && !pad.forward &&
			!(pad.leftMouse && pad.rightMouse);
	}

	bool pitchUp()
	{
		return pad.pitchUp && !pad.pitchDown;
	}

	bool pitchDown()
	{
		return pad.pitchDown && !pad.pitchUp;
	}

	bool rollLeft()
	{
		return pad.rollLeft && !pad.rollRight;
	}

	bool rollRight()
	{
		return pad.rollRight && !pad.rollLeft;
	}


	bool verticalUp()
	{
		return pad.verticalUp && !pad.verticalDown;
	}

	bool verticalDown()
	{
		return pad.verticalDown && !pad.verticalUp;
	}

	bool switchTarget()
	{
		return pad.switchTarget;
	}

	void clear()
	{
		pad.switchTarget = false;
	}
};

#endif // PLAYERINPUT_H
