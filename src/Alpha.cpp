#include "Alpha.h"
#include "ntgl.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <GL/glut.h>
#include "Vector3.h"
#include <FTGL/ftgl.h>

using namespace nt;

const float TURN_SPEED = M_PI;
const float PLAYER_MOVESPEED = 50;
const float PLAYER_BWD = 0.7; // how fast you move backwards compared to forwards
const float FOV = 65;
const float viewDistance = 800;

Alpha::Alpha(QWidget* const parent) :
        QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
        timer(this),
        player("Player 1"),
        player2("?"),
        camera(&player),
        playerShape(8.0f,8.0f,8.0f),
        font(MEDIA_DIR "/DejaVuSansMono.ttf"),
        cursor(Qt::ArrowCursor),
        cursorShown(true),
        _desktop(QApplication::desktop()->screenGeometry())
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
	// set our base cursor, shouldn't be possible to get to get below it
	// cursorLoadIdentity() or more accurately cursorPush()
	QApplication::setOverrideCursor(cursor);
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

	float da = TURN_SPEED * elapsed;

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
	// up/down commands now move you up/down relative to the world
	if ( velocity.z() == 0 ) {
		velocity.rotateX(camera.target->rotation().x());
	}
	velocity.rotateZ(camera.target->rotation().z());
	velocity *= PLAYER_MOVESPEED * elapsed;
	camera.target->position() += velocity;


	static int step = 0;

	int i = 0;
	// if we want the object to rotate instantly: think onyxia
	// FIXME: dear god
	static bool rotateInstantly = false;
	Object*  obj[3];
	obj[0] = &player2;
	// How far center of object needs to get to the radius
	// XXX: probably should be something like obj->skin.hitboxradius()
	// and the target's hitboxRadius if the wayPoint is a target
	float wpRadius = .5; // XXX: this seems to be as accurate as it can get
	if (step < 4) {

		Vector3<double> pivot(obj[i]->position());

		Vector3<double> wayPoint[4];
		wayPoint[0].set(40,0,10);
		wayPoint[1].set(-100,0,10);
		wayPoint[2].set(0,100,20);
		wayPoint[3].set(0,100,70);
		Vector3<double> difference;
		// get our distance difference vector
		difference.setX( wayPoint[step].x() - obj[i]->position().x() );
		difference.setY( wayPoint[step].y() - obj[i]->position().y() );
		difference.setZ( wayPoint[step].z() - obj[i]->position().z() );


		// XXX: rotations needed are calculated each tick
		// could perhaps calculate it just once, and only recalculate based on wayPoint made or
		// upset condition (blocked path / attacked / attacking)
		float zRot = 0; // Target Horizontal Angle
		float xRot = 0; // Target Vertical Angle

		// keeping zeros from giving us bad data
		if (difference.x() == 0) {
			if (difference.y() >= 0){
				zRot = 0;
			} else {
				zRot = M_PI_2 * 2;
			}
		} else if (difference.y() == 0) {
			if (difference.x() > 0) {
				zRot = M_PI_2 * 3;
			} else {
				zRot = M_PI_2;
			}
		} else {
			// figure out correct TOTAL angle, changes based on quadrant
			zRot = atan( difference.y() / difference.x() );
			if (difference.x() < 0){
				zRot += M_PI_2;
			} else {
				zRot += M_PI_2 * 3;
			}
		}
		// horizontal distance
		float dxy = sqrt(
			difference.x() * difference.x() + difference.y() * difference.y()
		);
		// vertical and horizontal angle calculation's aren't exacly the same
		// a function may be used but it probably would make it just as long
		if (difference.z() == 0) {
			xRot = 0;
		} else if (dxy == 0) {
			if (difference.z() > 0){
				xRot = M_PI_2;
			} else {
				xRot = M_PI_2 * 3;
			}
		} else {
			xRot = atan( dxy / difference.z() );
			if (difference.z() < 0){
				xRot = M_PI_2 * 3 - xRot;
			} else {
				xRot = M_PI_2 - xRot;
			}
		}

		// find the change in angles needed: current rotation - target rotation
		zRot = obj[i]->rotation().z() - zRot;
		xRot = obj[i]->rotation().x() - xRot;

		// if we are rotating instantly we simply set the current rotation to the target rotation
		if (!rotateInstantly)
		{

			// make sure all our comparisons are between 0-2*M_PI
			normalizeRadians(zRot);
			normalizeRadians(xRot);

			// XXX: could turn this part into a function
			// getTurnAmountThisTick()

			// positive is a left turn
			if ( zRot < M_PI) {
				// we can only rotate so fast
				if (zRot > da) {
					zRot = -da;
				} else {
					zRot = -zRot;
				}
			} else {
				if (zRot > da) {
					zRot = da;
				} // else { zRot = zRot; }
			}

			// positive is a pitch up
			if ( xRot < M_PI) {
				if (xRot > da) {
					xRot = -da;
				} else {
					xRot = -xRot;
				}
			} else {
				if (xRot > da) {
					xRot = da;
				} // else {xRot = xRot;}
			}
		}
		// so it will be more versatile later on
		static float v = PLAYER_MOVESPEED; // velocity
		static float w = TURN_SPEED; // angular velocity
		double radius = v/w;
		// if we aren't at the waypoint, start moving
		if (difference.length() > wpRadius)
		{

			// remove all previous velocities
			// find the pivot point for a turn, if the wayPoint is too close and we can't move and turn
			// to that point we need to slow down to give it time for the turn
			// XXX: really don't know if vectors are worth it in these cases
			// lots of reusing or brand new variables
			velocity.clear();
			velocity.set(-zRot, 0, 0 ); // "strafe" into position
			velocity.normalize(); // set the zRot to +-1;
			velocity.rotateZ(obj[i]->rotation().z()); // set it to the current rotation
			velocity *= radius; // actually move it
			pivot += velocity; // set pivot position to the determined coords
			difference.clear(); // once we are inside this if, we no longer use the original
			difference.setX( wayPoint[step].x() - pivot.x() );
			difference.setY( wayPoint[step].y() - pivot.y() );
			difference.setZ( wayPoint[step].z() - pivot.z() );

			velocity.clear(); // reset for the actual object movement
			velocity.addY(1); // object only moves forward
			// float comparisons seem to be off by a bit
			// so instead of seeing if dead on, just see if close
			bool x = xRot < 0.001f && xRot > -0.001f;
			bool z = zRot < 0.001f && zRot > -0.001f;
			if (difference.length() < radius && !(x && z) ) {\
				// if the target point is inside our turn radius, then slow down
				v = w * difference.length();
			}
		} else { // head to next waypoint
			step++;
			v = PLAYER_MOVESPEED;
			w = TURN_SPEED;
		}

		// add in our rotations
		obj[i]->rotation().addZ(zRot);
		obj[i]->rotation().addX(xRot);

		// currently not needed but strafing / hovering may be implemented
		velocity.normalize();
		velocity.rotateX(obj[i]->rotation().x());
		velocity.rotateZ(obj[i]->rotation().z());


		// Move our object
		velocity *= v * elapsed;
		obj[i]->position() += velocity;


	}


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
			glTranslatef(100.0f,100.0f,10.0f);
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
	hideCursor();

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
	showCursor();
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
	if (event->x()  > size().rwidth() || event->y() > size().rheight() ||
	    event->x() < 0 || event->y() < 0)
	{
		cursor.setPos(desktop().center());
		lastPos = QWidget::mapFromGlobal( desktop().center() );
	} else {
		lastPos = event->pos();
	}
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

void Alpha::hideCursor()
{
	if (cursorShown) // hide
	{
		// cursorPush()
		QApplication::setOverrideCursor(Qt::BlankCursor);
		// set the hidden cursor to the middle of the desktop
		// so regardless of where your window is you have a long
		// way to move the mouse before it hits an edge
		cursorHiddenAt = cursor.pos();
		cursor.setPos(desktop().center());
		lastPos = QWidget::mapFromGlobal( desktop().center() );
		cursorShown = false;
	}
}
void Alpha::showCursor()
{
	// if neither mouseButton is pressed
	if ( !input.leftMouse() and !input.rightMouse() )
	{
		// cursorPop()
		QApplication::restoreOverrideCursor();
		cursor.setPos(cursorHiddenAt);
		cursorShown = true;
	}
}
