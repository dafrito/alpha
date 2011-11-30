#include "Alpha.h"
#include "util.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <GL/glut.h>
#include <iostream>
#include "Vector.h"

using namespace nt;

// Config
const float TURN_SPEED = 1;
const float PLAYER_MOVESPEED = 50;
const float PLAYER_BWD = 0.7; // how fast you move backwards compared to forwards
const float FOV = 65;

const float viewDistance = 800;
// end Config

const float toDegrees = 180 / M_PI;
const float toRadians = M_PI / 180;

Alpha::Alpha(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this),camera(&player)
{
	setFocusPolicy(Qt::ClickFocus); // allows keyPresses to be passed to the rendered window
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	player.pos.setZ(10);
	player2.pos.setX(50);
	player2.pos.setZ(10);
}

void Alpha::tick(const float& elapsed)
{
	Vector3<double> velocity;

	if (input.switchTarget()) {
		NewTarget();
		input.clear();
	}

	float da = M_PI * elapsed * TURN_SPEED;
	if (input.turnLeft()) {
		camera.target->zRot += da;
		if (camera.rotateWithTarget){
			camera.setZRotation(camera.getZRotation() + da);
		}
	} else if (input.turnRight()) {
		camera.target->zRot -= da;
		if (camera.rotateWithTarget){
			camera.setZRotation(camera.getZRotation() - da);
		}
	}

	if (input.strafeLeft()) {
		velocity.addX(-1);
	} else if (input.strafeRight()) {
		velocity.addX(1);
	}

	// XXX: will be strafing but camera.rotateTarget is perhaps not right
	// the behavior in an FPS camera and in a 3rd person is not necessarily the same
	// TURNLEFT should probably turn you left in an FPS mode, even though the camera is rotating the player
	// in 3rd person a camera rotating the player should make the player strafe, like wow.
	// but if you put in two different methods then a streamlined swap between the two modes is not
	// possible -- maybe a TURNLEFT, STRAFELEFT, and SMARTLEFT?
 /*
	if ( (pad.turnLeft && camera.rotateTarget) && !pad.turnRight ) {
		camera.target->velocity = PLAYER_MOVESPEED;
		camera.target->zRot += M_PI / 2;
	} else if ( (pad.turnRight && camera.rotateTarget) && !pad.turnLeft ) {
		camera.target->velocity = PLAYER_MOVESPEED;
		camera.target->zRot += M_PI / 2;
	} else if (pad.strafeLeft && !pad.strafeRight && !camera.rotatingTarget) {
		camera.target->velocity = PLAYER_MOVESPEED;
		camera.target->zRot -= M_PI / 2;
	} else if (pad.strafeRight && !pad.strafeLeft && !camera.rotatingTarget) {
		camera.target->velocity = PLAYER_MOVESPEED;
		camera.target->zRot -= M_PI / 2;
	}
*/
	if (input.moveForward()) {
		velocity.addY(1);
		camera.target->velocity = PLAYER_MOVESPEED;
	} else if (input.moveBackward()) {
		velocity.addY(-1);
	 	camera.target->velocity = -PLAYER_MOVESPEED;
	}

	// Move the character vertically up and down.
	if (input.verticalUp()) {
		velocity.addZ(1);
	} else if (input.verticalDown()) {
		velocity.addZ(-1);
	}

 	//XXX: lol that is all
 	// ok not all, need to change the camera limits on xRot to be determined by target's pitch
	if (input.pitchUp()) {
		camera.target->xRot += da;
		if (camera.rotateWithTarget){
			camera.setXRotation(camera.getXRotation() + da);
		}
	} else if (input.pitchDown()) {
		camera.target->xRot -= da;
		if (camera.rotateWithTarget){
			camera.setXRotation(camera.getXRotation() - da);
		}
	}

	normalizeAngle(camera.target->zRot);
	normalizeAngle(camera.target->xRot);

	velocity.normalize();
	velocity.rotateX(camera.target->xRot);
	velocity.rotateZ(camera.target->zRot);
	velocity.scale(0.5 * PLAYER_MOVESPEED * elapsed);

	// S = Sinit + (1/2) * (V + Vinit) * deltaT
	float x = camera.target->pos.x() + velocity.x();
	//x += 0.5 * (camera.target->velocity + velocity_init) * elapsed * -sin(camera.target->zRot) * cos(camera.target->xRot);
	float y = camera.target->pos.y() + velocity.y();
	//y += 0.5 * (camera.target->velocity + velocity_init) * elapsed * cos(camera.target->zRot) * cos(camera.target->xRot);
	float z = camera.target->pos.z() + velocity.z();
	//z += 0.5 * (camera.target->velocity + velocity_init) * elapsed * sin(camera.target->xRot);

	camera.target->pos.setX(x);
	camera.target->pos.setY(y);
	camera.target->pos.setZ(z);
}

void Alpha::initializeGL()
{
	glClearColor(0.4,0.6,1,0);	// background: r,g,b,a
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
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	camera.applySettings();

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
		glRotatef(player.zRot * toDegrees, 0, 0, 1);
		glRotatef(player.xRot * toDegrees, 1,0,0);

		glBegin(GL_QUADS);
		// TOP is BLACK
		glColor4f(0.0f,0.0f,0.0f, player.alpha);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f, 4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f, 4.0f); // Bottom Right
			// BOTTOM is WHITE
		glColor4f(1.0f,1.0f,1.0f, player.alpha);
		glVertex3f(-4.0f, 4.0f, -4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, -4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f, -4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f, -4.0f); // Bottom Right
		// LEFT is BLUE
		glColor4f(0.0f,0.0f,1.0f, player.alpha);
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Right
		// RIGHT is BLUE
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Right
		// FRONT is GREEN
		glColor4f(0.0f,1.0f,0.0f, player.alpha);
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Right
		// BACK is RED
		glColor4f(1.0f,0.0f,0.0f, player.alpha);
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Right
		glEnd();
	}
	glPopMatrix();

	// draw the player2
	glPushMatrix();
	{
		// mobile objects always need to be rotated and moved within the world
		// this isn't actually rotated within the world, it's rotated within everything
		// this is fine because the world is never moved or rotated either
		glTranslatef(player2.pos.x(), player2.pos.y(), player2.pos.z());
		glRotatef(player2.zRot * toDegrees, 0, 0, 1);
		glRotatef(player2.xRot * toDegrees, 1,0,0);

		glBegin(GL_QUADS);
		// TOP is BLACK
		glColor4f(0.0f,0.0f,0.0f, player2.alpha);
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f, 4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f, 4.0f); // Bottom Right
			// BOTTOM is WHITE
		glColor4f(1.0f,1.0f,1.0f, player2.alpha);
		glVertex3f(-4.0f, 4.0f, -4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, -4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f, -4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f, -4.0f); // Bottom Right
		// LEFT is BLUE
		glColor4f(0.0f,0.0f,1.0f, player2.alpha);
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Right
		// RIGHT is BLUE
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Right
		// FRONT is GREEN
		glColor4f(0.0f,1.0f,0.0f, player2.alpha);
		glVertex3f(-4.0f, 4.0f, 4.0f); // Top Right
		glVertex3f( 4.0f, 4.0f, 4.0f); // Top Left
		glVertex3f( 4.0f, 4.0f,-4.0f); // Bottom Left
		glVertex3f(-4.0f, 4.0f,-4.0f); // Bottom Right
		// BACK is RED
		glColor4f(1.0f,0.0f,0.0f, player2.alpha);
		glVertex3f( 4.0f,-4.0f, 4.0f); // Top Right
		glVertex3f(-4.0f,-4.0f, 4.0f); // Top Left
		glVertex3f(-4.0f,-4.0f,-4.0f); // Bottom Left
		glVertex3f( 4.0f,-4.0f,-4.0f); // Bottom Right
		glEnd();
	}
	glPopMatrix();


}

// XXX: not set up so you can do single actions on key down
/* XXX:
keyPressEvent() is called whenever a key is pressed, and again when a key has been held down long enough for it to auto-repeat. The Tab and Shift+Tab keys are only passed to the widget if they are not used by the focus-change mechanisms. To force those keys to be processed by your widget, you must reimplement QWidget::event().
*/
void Alpha::keyPressEvent(QKeyEvent* event)
{
	if(!input.handleKeyPress(event)) {
		QGLWidget::keyPressEvent(event);
	}
}

void Alpha::keyReleaseEvent(QKeyEvent* event)
{
	if(!input.handleKeyRelease(event)) {
		QGLWidget::keyReleaseEvent(event);
	}
}

// TODO: prevent the mouse cursor from moving during a Mouse, similar to wow
void Alpha::mousePressEvent(QMouseEvent *event)
{
	input.handleMousePress(event);
	lastPos = event->pos();
	if (event->button() & Qt::LeftButton) {
		camera.rotateWithTarget = false;
		// Right click behavior overrides left click so it always fires on press
	}else if (event->button() & Qt::RightButton) {
		camera.alignTarget();
		camera.rotateTarget=true;
	}
}
void Alpha::mouseReleaseEvent(QMouseEvent * event)
{
	input.handleMouseRelease(event);
	if (event->button() & Qt::LeftButton) {
		camera.rotateWithTarget = true;
	}else if (event->button() & Qt::RightButton) {
		camera.rotateTarget = false;
	}
}
// Rotates the camera about the player
// XXX: camera doesn't stay snapped behind player during keyboard turn while holding right click
void Alpha::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	// Right click behavior overrides left click so it always fires on press
	if (event->buttons() & Qt::RightButton) {
		camera.setXRotation(camera.getXRotation() - dy * camera.xSpeed);
		camera.setZRotation(camera.getZRotation() - dx * camera.zSpeed);
		if (camera.rotateTarget){
			camera.alignTarget();
		}
	}else if (event->buttons() & Qt::LeftButton) {
		camera.setXRotation(camera.getXRotation() - dy *  camera.xSpeed);
		camera.setZRotation(camera.getZRotation() - dx *  camera.zSpeed);
	}
	lastPos = event->pos();
}
void Alpha::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		camera.setTargetDistance ( camera.getTargetDistance() - numSteps * camera.zoomSpeed );
	}
	event->accept();
}

