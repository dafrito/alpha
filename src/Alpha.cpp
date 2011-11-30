#include "Alpha.h"
#include "util.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <GL/glut.h>
#include <iostream>

// Config
const float TURN_SPEED = 1;
const float PLAYER_MOVESPEED = 50;
const float PLAYER_BWD = 0.7; // how fast you move backwards compared to forwards
const float FOV = 65;

const float viewDistance = 800;


// end Config



float toDegrees = 180 / M_PI;
float toRadians = M_PI / 180;



Alpha::Alpha(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this)
{
	camera.setTarget(player);
	setFocusPolicy(Qt::ClickFocus); // allows keyPresses to be passed to the rendered window
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	player.pos.setZ(10);
	player2.pos.setX(50);
	player2.pos.setZ(10);
	// camera faces whatever the player is
	camera.setXRotation(camera.target->xRot + M_PI_2);
	camera.setYRotation(camera.target->yRot);
	camera.setZRotation(camera.target->zRot);

}

void Alpha::tick(const float& elapsed)
{
	float velocity_init = camera.target->velocity; // for position calculation purposes
	float svelocity_init = camera.target->svelocity;
	if (pad.F1){
		NewTarget();
		pad.F1 = false; // only fires once
	}


	float da = M_PI * elapsed * TURN_SPEED;
	if (pad.turnLeft && !pad.turnRight) {
		camera.target->zRot += da;
		if (camera.rotateWithTarget){
			camera.setZRotation(camera.zRot + da);
		}
	} else if (pad.turnRight && !pad.turnLeft) {
		da = M_PI * elapsed * TURN_SPEED;
		camera.target->zRot -= da;
		if (camera.rotateWithTarget){
			camera.setZRotation(camera.zRot - da);
		}
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
	if ((pad.leftMouse && pad.rightMouse) && !pad.backward) {
		camera.target->velocity = PLAYER_MOVESPEED;
	} else if (pad.forward && !pad.backward) {
		camera.target->velocity = PLAYER_MOVESPEED;
	} else if (pad.backward && !pad.forward && !(pad.leftMouse && pad.rightMouse)) {
	 	camera.target->velocity = -PLAYER_MOVESPEED;
	} else {
		camera.target->velocity = 0;
	}



	// TODO: reimplement this
	if (pad.up && !pad.down) {

	} else if (pad.down && !pad.up) {

	}

	if (pad.pitchup && !pad.pitchdown) {
		camera.target->xRot += M_PI * elapsed * TURN_SPEED;

	}else if (pad.pitchdown && !pad.pitchup)  {
		camera.target->xRot -= M_PI * elapsed * TURN_SPEED;
	}

	if ( camera.target->zRot >= 2 * M_PI ) { camera.target->zRot -= 2 * M_PI; } // TODO: turn this into 1 normalize function
	else if (camera.target->zRot <=  0 ) { camera.target->zRot += 2 * M_PI; }	// keeps our angles within 1 revolution

	if ( camera.target->xRot >= 2 * M_PI ) { camera.target->xRot -= 2 * M_PI; }
	else if (camera.target->xRot <=  0 ) { camera.target->xRot += 2 * M_PI; }	// keeps our angles within 1 revolution

	// S = Sinit + (1/2) * (V + Vinit) * deltaT
	float x = camera.target->pos.x() + 0.5 * (camera.target->velocity + velocity_init) * elapsed * -sin(camera.target->zRot) * cos(camera.target->xRot);
	float y = camera.target->pos.y() + 0.5 * (camera.target->velocity + velocity_init) * elapsed * cos(camera.target->zRot) * cos(camera.target->xRot);
	float z = camera.target->pos.z() + 0.5 * (camera.target->velocity + velocity_init) * elapsed * sin(camera.target->xRot);

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
		case Qt::Key_F1: pad.F1 = true; break;
		default:
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
		case Qt::Key_F1: pad.F1 = false; break;
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
		camera.rotateWithTarget = false;
		// Right click behavior overrides left click so it always fires on press
	}else if (event->button() & Qt::RightButton) {
		camera.target->zRot = (camera.zRot);
		camera.target->xRot = (camera.xRot - M_PI_2);
		pad.rightMouse = true;
		camera.rotateTarget=true;
	}
}
void Alpha::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() & Qt::LeftButton) {
		pad.leftMouse = false;
		camera.rotateWithTarget = true;
	}else if (event->button() & Qt::RightButton) {
		pad.rightMouse = false;
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
		camera.setXRotation(camera.xRot - dy * camera.xSpeed);
		camera.setZRotation(camera.zRot - dx * camera.zSpeed);
		if (camera.rotateTarget){
			camera.target->zRot -= dx *  camera.zSpeed;
			camera.target->xRot -= dy *  camera.xSpeed;
		}
	}else if (event->buttons() & Qt::LeftButton) {
		camera.setXRotation(camera.xRot - dy *  camera.xSpeed);
		camera.setZRotation(camera.zRot - dx *  camera.zSpeed);
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

