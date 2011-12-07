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



Alpha::Alpha(QWidget* const parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		timer(this),player("Player 1"),player2("?"), camera(&player), playerShape(8.0f,8.0f,8.0f),
		font("DejaVuSansMono.ttf")
{
	setFocusPolicy(Qt::ClickFocus); // allows keyPresses to be passed to the rendered window
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	player.position().setZ(10);
	player2.position().set(50, 0, 10);
	GLfloat playerColors[] = {
		0,1,0,1,
		0,1,0,1,
		0,1,0,1,
		0,1,0,1,

		1,0,0,1,
		1,0,0,1,
		1,0,0,1,
		1,0,0,1,

		0,0,1,1,
		0,0,1,1,
		0,0,1,1,
		0,0,1,1,

		0,0,1,1,
		0,0,1,1,
		0,0,1,1,
		0,0,1,1,

		0,0,0,1,
		0,0,0,1,
		0,0,0,1,
		0,0,0,1,

		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1
	};
	playerShape.colors(playerColors);
}
void Alpha::drawCameraOrientedText(FTFont* const font, const char* text, int zOffset)
	{
		glPushMatrix();
		const float width = font->BBox(text).Upper().X();
		glTranslatef(0, 0, zOffset + 2 + font->FaceSize());
		glRotatef(camera.rotation().z() * TO_DEGREES, 0, 0, 1);
		glRotatef(90,1,0,0);
		// glRotatef( camera.rotation().x() * TO_DEGREES, 1,0,0);
		glTranslatef(-width/2,0,0);
		font->Render(text);
		glPopMatrix();
	}

void Alpha::tick(const float& elapsed)
{
	Vector3<double> velocity;

	float da = M_PI * elapsed * TURN_SPEED;

	if (input.switchTarget()) {
		NewTarget();
		input.clear();
	}
	// XXX: will be strafing but camera.rotateTarget is perhaps not right
	// the behavior in an FPS camera and in a 3rd person is not necessarily the same
	// TURNLEFT should probably turn you left in an FPS mode, even though the camera is rotating the player
	// in 3rd person a camera rotating the player should make the player strafe, like wow.
	// but if you put in two different methods then a streamlined swap between the two modes is not
	// possible -- maybe a TURNLEFT, STRAFELEFT, and SMARTLEFT?


	if ( (input.turnLeft() && camera.rotateTarget ) && !input.turnRight() ) {
		velocity.addX(-1);
	} else if ( (input.turnRight() && camera.rotateTarget ) && !input.turnLeft() ) {
		velocity.addX(1);
	} else if (input.turnLeft()) {
		camera.addTargetZRotation(da);
	} else if (input.turnRight()) {
		camera.addTargetZRotation(-da);
	}

	if (input.strafeLeft() && !input.strafeRight() ) {
		velocity.addX(-1);
	} else if (input.strafeRight() && !input.strafeLeft() ) {
		velocity.addX(1);
	}

	if (input.moveForward()) {
		velocity.addY(1);
	} else if (input.moveBackward()) {
		velocity.addY(-1);
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
		camera.addTargetXRotation(da);
	} else if (input.pitchDown()) {
		camera.addTargetXRotation(-da);
	}

	if ( input.rollLeft() ) {
		camera.addTargetYRotation( -da );
	} else if ( input.rollRight() ){
		camera.addTargetYRotation( da );
	}


	velocity.normalize();
	velocity.rotateX(camera.target->rotation().x());
	velocity.rotateZ(camera.target->rotation().z());
	velocity.scale(0.5 * PLAYER_MOVESPEED * elapsed);
	camera.target->position().add(velocity);
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
	nt::setGLFrustum(FOV, aspectRatio, 1, viewDistance);
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
		glPushMatrix();
		{
			glTranslatef(0.0f,-90.0f,10.0f);
			glColor3f(0.0f,0.0f,0.0f);
			playerShape.draw();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// draw the player's cube
	// FIXME: this cube cannot see player2's cube through it when transparent
	// possibly because of the order drawn, if thats the case then ghosts are out
	glPushMatrix();
	{
		// mobile objects always need to be rotated and moved within the world
		// this isn't actually rotated within the world, it's rotated within everything
		// this is fine because the world is never moved or rotated either

		glTranslate(player.position());
		glColor3f(1.0f,1.0f,1.0f);
		font.FaceSize(4);
		drawCameraOrientedText(&font,player.name(),4);
		glRotateRadians(player.rotation());
		playerShape.setAlpha(player.alpha());
		playerShape.draw();

	}
	glPopMatrix();

	// draw the player2
	glPushMatrix();
	{
		// mobile objects always need to be rotated and moved within the world
		// this isn't actually rotated within the world, it's rotated within everything
		// this is fine because the world is never moved or rotated either
		glTranslate(player2.position());
		glColor3f(1.0f,1.0f,0.0f);
		font.FaceSize(14);
		drawCameraOrientedText(&font,player2.name(),-10);
		glRotateRadians(player2.rotation());
		playerShape.setAlpha(player2.alpha());
		playerShape.draw();

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
	float dx = event->x() - lastPos.x();
	float dy = event->y() - lastPos.y();
	dx *= camera.zSpeed; // horizontal rotation
	dy *= camera.xSpeed; // vertical rotation
	// Right click behavior overrides left click so it always fires on press
	// cameras rotate opposite the direction you move, in order to look that way
	if (event->buttons() & Qt::RightButton) {
		camera.addXRotation(-dy );
		camera.addZRotation(-dx );
	}else if (event->buttons() & Qt::LeftButton) {
		camera.addXRotation(-dy );
		camera.addZRotation(-dx );


	}
	lastPos = event->pos();
}
void Alpha::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		camera.addTargetDistance(-numSteps * camera.zoomSpeed );
	}
	event->accept();
}

