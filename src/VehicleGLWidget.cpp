#include "VehicleGLWidget.h"
#include <QKeyEvent>
#include <cmath>

// All values are half-size.
const int VEHICLE_LENGTH = 30;
const int VEHICLE_WIDTH = 15;
const int ARENA_SIZE = 500;
const int WALL_SIZE = 10;

VehicleGLWidget::VehicleGLWidget(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this)
{
	setFocusPolicy(Qt::ClickFocus);
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
}

void VehicleGLWidget::initializeGL()
{
	qglClearColor(Qt::black);
}

void VehicleGLWidget::tick(const float& elapsed)
{
	float accel = 0;
	if (pad.accelerator && pad.brake) {
		accel = -125;
	} else if (pad.accelerator) {
		accel = 250;
	} else if (abs(car.velocity) > 10) {
		const float dir = car.velocity > 0 ? -1 : 1;
		const float friction = pad.brake ? 1500 : 50;
		accel = dir * friction;
	} else {
		car.velocity = 0;
	}
	if (pad.left && !pad.right) {
		car.angle += M_PI * elapsed;
	}
	if (pad.right && !pad.left) {
		car.angle -= M_PI * elapsed;
	}
	float x = elapsed * cos(car.angle) * (.5 * accel * elapsed + car.velocity) + car.pos.x();
	float y = elapsed * sin(car.angle) * (.5 * accel * elapsed + car.velocity) + car.pos.y();
	car.velocity += accel * elapsed;
	car.pos.setX(x);
	car.pos.setY(y);
	const int range = ARENA_SIZE - VEHICLE_WIDTH;
	{
		const double diff = abs(x) - range;
		if (diff > 0) {
			car.velocity *= -1;
			if (x > 0) {
				// X is positive; head negative
				x = range - diff;
			} else {
				// X is negative; head positive
				x = -range + diff;
			}
		}
		car.pos.setX(x);
	}
	{
		const double diff = abs(y) - range;
		if (diff > 0) {
			car.velocity *= -1;
			if (y > 0) {
				// Y is positive; head negative
				y = range - diff;
			} else {
				// Y is negative; head positive
				y = -range + diff;
			}
		}
		car.pos.setY(y);
	}
}

void drawQuad(float left, float right, float bottom, float top)
{
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glVertex2f(left, top);
	glVertex2f(left, bottom);
}

void drawQuad(float width, float height)
{
	drawQuad(-width, width, height, -height);
}

void VehicleGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Render walls
	glBegin(GL_QUADS);
	glColor3ub(0xa3, 0xa5, 0x9f);
	drawQuad(ARENA_SIZE+WALL_SIZE, ARENA_SIZE+WALL_SIZE);
	glColor3ub(75, 54, 33);
	drawQuad(ARENA_SIZE, ARENA_SIZE);
	glEnd();
	// Render car
	glTranslatef(car.pos.x(), car.pos.y(), car.pos.z());
	glRotatef(car.angle * 180 / M_PI, 0, 0, 1);
	glBegin(GL_QUADS);
	// Body
	glColor3ub(0, 0x5b, 0xa9);
	drawQuad(VEHICLE_LENGTH, VEHICLE_WIDTH);
	// Windshields
	glColor3ub(35, 35, 35);
	drawQuad(
		-VEHICLE_LENGTH + 10,
		VEHICLE_LENGTH / 3,
		-VEHICLE_WIDTH + 2,
		VEHICLE_WIDTH - 2
		);
	// Front lights
	glColor3f(1, 1, .2);
	drawQuad(
		VEHICLE_LENGTH,
		VEHICLE_LENGTH - 3,
		-VEHICLE_WIDTH,
		VEHICLE_WIDTH
		);
	glColor3ub(0, 0x5b, 0xa9);
	drawQuad(
		VEHICLE_LENGTH,
		VEHICLE_LENGTH - 3,
		-VEHICLE_WIDTH + 5,
		VEHICLE_WIDTH - 5
		);
	// Rear lights
	if (pad.brake) {
		glColor3f(1, .2, .2);
	} else {
		glColor3f(.7, 0, 0);
	}
	drawQuad(
		-VEHICLE_LENGTH,
		-VEHICLE_LENGTH + 2,
		-VEHICLE_WIDTH,
		VEHICLE_WIDTH
		);
	glColor3ub(0, 0x5b, 0xa9);
	drawQuad(
		-VEHICLE_LENGTH,
		-VEHICLE_LENGTH + 2,
		-VEHICLE_WIDTH + 7,
		VEHICLE_WIDTH - 7
		);
	// Top
	glColor3ub(0, 0x5b, 0xa9);
	drawQuad(
		-VEHICLE_LENGTH / 2 + 2,
		0,
		-VEHICLE_WIDTH + 4,
		VEHICLE_WIDTH - 4
		);
	glEnd();
}

void VehicleGLWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_Space:
			car.pos = QVector3D(0, 0, 0);
			car.velocity = 0;
			car.angle = 0;
			break;
		case Qt::Key_W: pad.accelerator = true; break;
		case Qt::Key_S: pad.brake = true; break;
		case Qt::Key_A: pad.left = true; break;
		case Qt::Key_D: pad.right = true; break;
		default:
			QGLWidget::keyPressEvent(event);
	}
}

void VehicleGLWidget::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.accelerator = false; break;
		case Qt::Key_S: pad.brake = false; break;
		case Qt::Key_A: pad.left = false; break;
		case Qt::Key_D: pad.right = false; break;
		default:
			QGLWidget::keyReleaseEvent(event);
	}
}

void VehicleGLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-ARENA_SIZE - WALL_SIZE, ARENA_SIZE + WALL_SIZE,
		-ARENA_SIZE - WALL_SIZE, ARENA_SIZE + WALL_SIZE,
		-100, 100);
	glMatrixMode(GL_MODELVIEW);
}
