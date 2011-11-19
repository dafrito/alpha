#include "Alpha.h"
#include "util.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <cmath>
#include <GL/glut.h>

// Config
const float TURN_SPEED = 1;
const float PLAYER_FWD = 50;
const float PLAYER_BWD = 30;
const float FOV = 65;
const float viewDistance = 800;

const float camRadius = 100;
const float camZoomSpeed = 5; // a multiplier
const float camSpeed = 1; // a multiplier



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
	player.yaw = M_PI / 2;
	player.camRadius = camRadius;
	player.camZoomSpeed = camZoomSpeed;
	player.camSpeed = camSpeed;
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
		player.yaw += M_PI * elapsed * TURN_SPEED;
	}
	if (pad.yawright && !pad.yawleft) {
		player.yaw -= M_PI * elapsed * TURN_SPEED;
	}

	if (pad.pitchup) {
		//player.pitch -= M_PI * elapsed * TURN_SPEED; // Zaxis appears to be "backwards"
		pad.pitchup = false;
		setZRotation(zRot + 90);
	}
	if (pad.pitchdown)  {
		//player.pitch += M_PI * elapsed * TURN_SPEED;
		pad.pitchdown = false;
		setZRotation(zRot-90);

	}

	if ( player.yaw >= 2 * M_PI ) { player.yaw -= 2 * M_PI; } // TODO: turn this into 1 normalize function
	else if (player.yaw <=  0 ) { player.yaw += 2 * M_PI; }	// keeps our angles within 1 revolution

	if ( player.pitch >= 2 * M_PI ) { player.pitch -= 2 * M_PI; }
	else if (player.pitch <=  0 ) { player.pitch += 2 * M_PI; }	// keeps our angles within 1 revolution

	// S = Sinit + (1/2) * (V + Vinit) * deltaT
	float x = player.pos.x() + 0.5 * (player.velocity + velocity_init) * elapsed * cos(player.yaw) * cos(player.pitch);
	float y = player.pos.y() + 0.5 * (player.velocity + velocity_init) * elapsed * sin(player.yaw) * cos(player.pitch);
	float z = player.pos.z() + 0.5 * (player.velocity + velocity_init) * elapsed * sin(-player.pitch);

	player.pos.setX(x);
	player.pos.setY(y);
	player.pos.setZ(z);

}


void Alpha::initializeGL()
{
	glClearColor(0.4,0.6,1,0);	// background: r,g,b,a
	setXRotation(-90); // makes the camera horizontal
	setYRotation(0);
	setZRotation(90); // makes the camera line up with the player's view
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
	// originally the z-axis is near to far and we haven't rotated yet
	glTranslatef(0.0f,0.0f,-player.camRadius); // for 3rd person perspective
	applyRotation();


	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);





	// The world
	glPushMatrix();
	{

		// rotate world around player
		glRotatef(-player.yaw * 180 / M_PI, 0, 0, 1);
		glRotatef(-player.pitch * 180 /M_PI, 0,1,0);


		// move the world around the player
		glTranslatef(-player.pos.x(), -player.pos.y(), -player.pos.z());

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


		glBegin(GL_QUADS);
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
		case Qt::Key_A: pad.yawleft = true; break;
		case Qt::Key_D: pad.yawright = true; break;
		case Qt::Key_Space: pad.up = true; break;
		case Qt::Key_X: pad.down = true; break;
		case Qt::Key_E: pad.pitchup = false; break;
		case Qt::Key_Q: pad.pitchdown = false; break;
		default: // ???: have frito explain where the esc key is bound to close()
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
		case Qt::Key_E: pad.pitchup = true; break;
		case Qt::Key_Q: pad.pitchdown = true; break;
		default:
			QGLWidget::keyReleaseEvent(event);
	}
}

// TODO: prevent the mouse from moving during a press, similar to wow
void Alpha::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
	if (event->buttons() & Qt::LeftButton) {
		pad.leftPress = true;
	}
	if (event->buttons() & Qt::RightButton) {
		pad.rightPress = true;
	}
}
void Alpha::mouseReleaseEvent(QMouseEvent * event)
{
	// XXX: why do I have to use event->button() here?
	if (event->button() & Qt::LeftButton) {
		pad.leftPress = false;
	}
	if (event->button() & Qt::RightButton) {
		pad.rightPress = false;
	}
}
// Rotates the camera about the player
void Alpha::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + dy * 0.5 * player.camSpeed);
		setZRotation(zRot + dx * 0.5 * player.camSpeed);
	} else if (event->buttons() & Qt::RightButton) {

	}
	lastPos = event->pos();
}
void Alpha::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		player.camRadius -= numSteps * player.camZoomSpeed;
	}
	event->accept();
}

void Alpha::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void Alpha::setZRotation(int angle)
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
	glRotatef((float)(xRot), 1.0, 0.0, 0.0);
	glRotatef((float)(yRot), 0.0, 1.0, 0.0);
	glRotatef((float)(zRot), 0.0, 0.0, 1.0);
}
