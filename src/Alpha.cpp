#include "Alpha.h"
#include <QKeyEvent>
#include <cmath>


// Config
const float TURN_SPEED = 1;
const float PLAYER_FWD = 50;
const float PLAYER_BWD = 30;
// end Config

Alpha::Alpha(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this)
{
	setFocusPolicy(Qt::ClickFocus); // allows keypresses to passed to the rendered window
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	player.pos.setZ(10);
}

void Alpha::tick(const float& elapsed)
{
	float velocity_init = player.velocity; // for position calculation purposes

	if (pad.forward) {
		player.velocity = PLAYER_FWD;
	} else if (pad.backward) {
	 	player.velocity = -PLAYER_BWD;
	} else {
		player.velocity = 0;
	}

	if (pad.yawleft && !pad.yawright) {
		player.yaw -= M_PI * elapsed * TURN_SPEED;
	}
	if (pad.yawright && !pad.yawleft) {
		player.yaw += M_PI * elapsed * TURN_SPEED;
	}

	if (pad.pitchup && !pad.pitchdown) {
		player.pitch += M_PI * elapsed * TURN_SPEED;
	}
	if (pad.pitchdown && !pad.pitchup) {
		player.pitch -= M_PI * elapsed * TURN_SPEED;
	}

	if ( player.yaw >= 2 * M_PI ) { player.yaw -= 2 * M_PI; } // TODO: turn this into 1 normalize function
	else if (player.yaw <=  0 ) { player.yaw += 2 * M_PI; }	// keeps our angles within 1 revolution

	if ( player.pitch >= 2 * M_PI ) { player.pitch -= 2 * M_PI; } // TODO: turn this into 1 normalize function
	else if (player.pitch <=  0 ) { player.pitch += 2 * M_PI; }	// keeps our angles within 1 revolution

	// S = Sinit + (1/2) * (V + Vinit) * deltaT
	float x = player.pos.x() + 0.5 * (player.velocity + velocity_init) * elapsed * cos(player.yaw);
	float y = player.pos.y() + 0.5 * (player.velocity + velocity_init) * elapsed * sin(player.yaw);
	float z; // TODO: use this;

	player.pos.setX(x);
	player.pos.setY(y);


}


void Alpha::initializeGL()
{
	glClearColor(0.4,0.6,1,0);	// background: r,g,b,a
	setXRotation(130);
	setYRotation(0);
	setZRotation(0);
}

void Alpha::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height); // viewport: (startx,starty, width, height)

	const float aspectRatio = (float) height / (float) width;
	const float range = 100.0;
	// do not do anything with GL_PROJECTION besides set glOrtho
	glMatrixMode(GL_PROJECTION); // determines how the the world is viewed by the user
	glLoadIdentity(); // set the matrix to an unmodified state
	if (width <= height) {
		glOrtho( // clips everything drawn outside the params
			-range, // left
			range, // right
			-range * aspectRatio, // bottom
			range * aspectRatio, // top
			2 * -range, // back
			2 * range); // front
	} else {
		glOrtho(
			-range / aspectRatio,
			range / aspectRatio, -range,
			range,
			2 * -range,
			2 * range);
	}
	glMatrixMode(GL_MODELVIEW); // the world and where it is viewed from
	glLoadIdentity(); // set the matrix to an unmodified state
}


void Alpha::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	applyRotation();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	// draw the player's cube
	glRotatef(player.yaw * 180 / M_PI, 0, 0, 1);
	glRotatef(player.pitch * 180 /M_PI, 0,1,0);
	glBegin(GL_QUADS);
	{

		// TOP is BLACK
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f, 4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f, 4.0f); // Bottom Right
		// BOTTOM is WHITE
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(-4.0f, 4.0f, -4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, -4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f, -4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f, -4.0f); // Bottom Right

		// BACK is RED
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Right
		// FRONT is GREEN
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Right
		// LEFT is BLUE
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Right
		// RIGHT is BLUE
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Right
	}
	glEnd();

	// draw the ground
	glPushMatrix();
	{
		glTranslatef(player.pos.x(), player.pos.y(), player.pos.z()); // move the world, not the camera
		glBegin(GL_QUADS);
		{
			glColor3f(0.1f, 0.65f, 0.1f);
			// XXX: This is all backwards
			glVertex3f(-80.0f, 80.0f, 0.0f); // Top Left
			glVertex3f( 80.0f, 80.0f, 0.0f); // Top Right
			glVertex3f( 80.0f,-80.0f, 0.0f); // Bottom Right
			glVertex3f(-80.0f,-80.0f, 0.0f); // Bottom Left

		}
		glEnd();
	}
	glPopMatrix();
}

void Alpha::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = true; break;
		case Qt::Key_S: pad.backward = true; break;
		case Qt::Key_A: pad.yawleft = true; break;
		case Qt::Key_D: pad.yawright = true; break;
		case Qt::Key_Space: pad.up = true; break;
		case Qt::Key_X: pad.down = true; break;
		case Qt::Key_Q: pad.pitchup = true; break;
		case Qt::Key_E: pad.pitchdown = true; break;
		default: // TODO: have frito explain where the esc key is bound to close()
			QGLWidget::keyPressEvent(event);
	}
}

void Alpha::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = false; break;
		case Qt::Key_S: pad.backward = false; break;
		case Qt::Key_A: pad.yawleft = false; break;
		case Qt::Key_D: pad.yawright = false; break;
		case Qt::Key_Space: pad.up = false; break;
		case Qt::Key_X: pad.down = false; break;
		case Qt::Key_Q: pad.pitchup = false; break;
		case Qt::Key_E: pad.pitchdown = false; break;
		default:
			QGLWidget::keyPressEvent(event);
	}
}

void Alpha::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

/**
 * Interpret the mouse event to rotate the camera around the scene.
 */
void Alpha::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setScaledXRotation(xRot + dy * Alpha::ROTATION_SCALE / 2);
		setScaledYRotation(yRot + dx * Alpha::ROTATION_SCALE / 2);
	} else if (event->buttons() & Qt::RightButton) {
		setScaledXRotation(xRot + dy * Alpha::ROTATION_SCALE / 2);
		setScaledZRotation(zRot + dx * Alpha::ROTATION_SCALE / 2);
	}
	lastPos = event->pos();
}

void Alpha::setScaledXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setScaledYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setScaledZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void Alpha::applyRotation() const
{
	static const float ROTATION_DENOM = 1 / (float)Alpha::ROTATION_SCALE;
	glRotatef((float)(xRot) * ROTATION_DENOM, 1.0, 0.0, 0.0);
	glRotatef((float)(yRot) * ROTATION_DENOM, 0.0, 1.0, 0.0);
	glRotatef((float)(zRot) * ROTATION_DENOM, 0.0, 0.0, 1.0);
}
