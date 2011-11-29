#include "Alpha.h"
#include "util.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <GL/glut.h>

// Config
const float TURN_SPEED = 1;
const float PLAYER_MOVESPEED = 50;
const float PLAYER_BWD = 0.7; // how fast you move backwards compared to forwards
const float FOV = 65;
const float viewDistance = 800;

const float camRadius = 100; // Distance from player
const float camZoomSpeed = 5; // a multiplier
const float camSpeed = 1; // a multiplier
// end Config



float toDegrees = 180 / M_PI;
float toRadians = M_PI / 180;

Alpha::Alpha(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this)
{
	setFocusPolicy(Qt::ClickFocus); // allows keyPresses to be passed to the rendered window
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	player.pos.setZ(10);
	player.camRadius = camRadius;
	player.camZoomSpeed = camZoomSpeed;
	player.camSpeed = camSpeed;
}

void Alpha::tick(const float& elapsed)
{
	float velocity_init = player.velocity; // for position calculation purposes
	float svelocity_init = player.svelocity;



	if (pad.turnLeft && !pad.turnRight) {
		player.facing += M_PI * elapsed * TURN_SPEED;
	} else if (pad.turnRight && !pad.turnLeft) {
		player.facing -= M_PI * elapsed * TURN_SPEED;
	}

	player.heading = player.facing;

	if ( (pad.turnLeft && player.camRotatePlayer ) && !pad.turnRight ) {
		player.velocity = PLAYER_MOVESPEED;
		player.heading += M_PI / 2;
	} else if ( (pad.turnRight && player.camRotatePlayer ) && !pad.turnLeft ) {
		player.velocity = PLAYER_MOVESPEED;
		player.heading += M_PI / 2;
	} else if (pad.strafeLeft && !pad.strafeRight && !player.camRotatePlayer) {
		player.velocity = PLAYER_MOVESPEED;
		player.heading -= M_PI / 2;
	} else if (pad.strafeRight && !pad.strafeLeft && !player.camRotatePlayer) {
		player.velocity = PLAYER_MOVESPEED;
		player.heading -= M_PI / 2;
	}

	if ((pad.leftMouse && pad.rightMouse) && !pad.backward) {
		player.velocity = PLAYER_MOVESPEED;
	} else if (pad.forward && !pad.backward) {
		player.velocity = PLAYER_MOVESPEED;
	} else if (pad.backward && !pad.forward && !(pad.leftMouse && pad.rightMouse)) {
	 	player.velocity = -PLAYER_MOVESPEED;
	} else {
		player.velocity = 0;
	}



	// TODO: reimplement this
	if (pad.up && !pad.down) {

	} else if (pad.down && !pad.up) {

	}
	// XXX: pretty broken atm;
	if (pad.pitchup && !pad.pitchdown) {
		player.pitch -= M_PI * elapsed * TURN_SPEED; // Zaxis appears to be "backwards"

	}else if (pad.pitchdown && !pad.pitchup)  {
		player.pitch += M_PI * elapsed * TURN_SPEED;
	}

	if ( player.facing >= 2 * M_PI ) { player.facing -= 2 * M_PI; } // TODO: turn this into 1 normalize function
	else if (player.facing <=  0 ) { player.facing += 2 * M_PI; }	// keeps our angles within 1 revolution

	if ( player.pitch >= 2 * M_PI ) { player.pitch -= 2 * M_PI; }
	else if (player.pitch <=  0 ) { player.pitch += 2 * M_PI; }	// keeps our angles within 1 revolution

	// S = Sinit + (1/2) * (V + Vinit) * deltaT
	float x = player.pos.x() + 0.5 * (player.velocity + velocity_init) * elapsed * cos(player.heading) * cos(player.pitch);
	float y = player.pos.y() + 0.5 * (player.velocity + velocity_init) * elapsed * sin(player.heading) * cos(player.pitch);
	float z = player.pos.z() + 0.5 * (player.velocity + velocity_init) * elapsed * sin(-player.pitch);

	player.pos.setX(x);
	player.pos.setY(y);
	player.pos.setZ(z);

}




void Alpha::initializeGL()
{
	glClearColor(0.4,0.6,1,0);	// background: r,g,b,a
	setXRotation(270); // makes the camera horizontal with Z axis positive being up
	setYRotation(0);
	setZRotation(90); // Lines camera up behind player
}

void Alpha::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height); // viewport: (startx,starty, width, height)

	const float aspectRatio = (float) width / height;
	glMatrixMode(GL_PROJECTION); // determines how the the world is viewed by the user
	glLoadIdentity(); // set the matrix to an unmodified state
	nt::setGLFrustrum(FOV, aspectRatio, 1, viewDistance);
	glMatrixMode(GL_MODELVIEW); // the world and where it is viewed from
	glLoadIdentity(); // set the matrix to an unmodified state
}


void Alpha::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// originally the z-axis is near to far
	glTranslatef( 0.0f,0.0f, - player.camRadius);
	applyRotation();
	// keeps the player in the center of the screen
	glTranslatef(-player.pos.x(), -player.pos.y(), -player.pos.z());

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	// The world
	glPushMatrix();
	{

		glBegin(GL_QUADS);
		glColor3f(0.1f, 0.65f, 0.1f);

		glVertex3f( 100.0f, 100.0f, 0.0f); // Top Right
		glVertex3f(-100.0f, 100.0f, 0.0f); // Top Left
		glVertex3f(-100.0f,-100.0f, 0.0f); // Bottom Left
		glVertex3f( 100.0f,-100.0f, 0.0f); // Bottom Right

		glEnd();
		// for bearing
		glPushMatrix();
		{
			glTranslatef(0.0f,90.0f,10.0f);
			glColor3f(1.0f,1.0f,0.0f);
			glutWireSphere(10, 15, 15);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-90.0f,0.0f,10.0f);
			glColor3f(1.0f,0.0f,1.0f);
			glutWireSphere(10, 15, 15);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// draw the player's cube
	glPushMatrix();
	{
		// mobile objects always need to be rotated and moved within the world
		// this isn't actually rotated within the world, it's rotated within everything
		// this is fine because the world is never moved or rotated either
		glTranslatef(player.pos.x(), player.pos.y(), player.pos.z());
		glRotatef(player.facing * toDegrees, 0, 0, 1);
		glRotatef(player.pitch * toDegrees, 0,1,0);



		float pAlpha = player.camRadius / 100;
		glBegin(GL_QUADS);
		// TOP is BLACK
		glColor4f(0.0f,0.0f,0.0f, pAlpha);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f, 4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f, 4.0f); // Bottom Right
			// BOTTOM is WHITE
		glColor4f(1.0f,1.0f,1.0f, pAlpha);
		glVertex3f(-4.0f, 4.0f, -4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, -4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f, -4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f, -4.0f); // Bottom Right
		// BACK is RED
		glColor4f(1.0f,0.0f,0.0f, pAlpha);
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Right
		// FRONT is GREEN
		glColor4f(0.0f,1.0f,0.0f, pAlpha);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Right
		// LEFT is BLUE
		glColor4f(0.0f,0.0f,1.0f, pAlpha);
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Right
		// RIGHT is BLUE
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Right
		glEnd();
	}
	glPopMatrix();


}

// XXX: not set up so you can do single actions on key down
void Alpha::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = true; break;
		case Qt::Key_S: pad.backward = true; break;
		case Qt::Key_A: pad.turnLeft = true; break;
		case Qt::Key_D: pad.turnRight = true; break;
		case Qt::Key_Space: pad.up = true; break;
		case Qt::Key_X: pad.down = true; break;
		case Qt::Key_E: pad.pitchup = true; break;
		case Qt::Key_Q: pad.pitchdown = true; break;
		case Qt::Key_1: pad.strafeLeft = true; break;
		case Qt::Key_2: pad.strafeRight = true; break;
		default: // ???: have frito explain where the esc key is bound to close()
			QGLWidget::keyPressEvent(event);
	}
}

void Alpha::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key()) {
		case Qt::Key_W: pad.forward = false; break;
		case Qt::Key_S: pad.backward = false; break;
		case Qt::Key_A: pad.turnLeft = false; break;
		case Qt::Key_D: pad.turnRight = false; break;
		case Qt::Key_Space: pad.up = false; break;
		case Qt::Key_X: pad.down = false; break;
		case Qt::Key_E: pad.pitchup = false; break;
		case Qt::Key_Q: pad.pitchdown = false; break;
		case Qt::Key_1: pad.strafeLeft = false; break;
		case Qt::Key_2: pad.strafeRight = false; break;
		default:
			QGLWidget::keyReleaseEvent(event);
	}
}

// TODO: prevent the mouse cursor from moving during a Mouse, similar to wow
void Alpha::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
	if (event->button() & Qt::LeftButton) {
		pad.leftMouse = true;
		// Right click behavior overrides left click so it always fires on press
	}else if (event->button() & Qt::RightButton) {
		player.facing = (90 - zRot) * toRadians;
		pad.rightMouse = true;
	}
}
void Alpha::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() & Qt::LeftButton) {
		pad.leftMouse = false;
	}else if (event->button() & Qt::RightButton) {
		pad.rightMouse = false;
	}
}
// Rotates the camera about the player
void Alpha::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	// Right click behavior overrides left click so it always fires on press
	if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + dy * 0.5 * player.camSpeed);
		player.facing -= dx * 0.5 * player.camSpeed * toRadians;
		setZRotation(zRot + dx * 0.5 * player.camSpeed);
	}else if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + dy * 0.5 * player.camSpeed);
		setZRotation(zRot + dx * 0.5 * player.camSpeed);
	}
	lastPos = event->pos();
}
void Alpha::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		player.camRadius -= numSteps * player.camZoomSpeed;
		player.limitCamRadius(player.camRadius); // XXX: this just looks silly
	}
	event->accept();
}

void Alpha::setXRotation(float angle)
{
	qNormalizeAngle(angle);
	// keep us from flipping upside down
	if ( angle < 90 ) { angle = 0; }
	else if ( angle < 180 ) {angle = 180;}

	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setYRotation(float angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setZRotation(float angle)
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
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glRotatef(zRot, 0.0, 0.0, 1.0);
}
