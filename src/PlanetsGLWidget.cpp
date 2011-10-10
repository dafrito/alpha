#include "PlanetsGLWidget.h"

PlanetsGLWidget::PlanetsGLWidget() :
	timer(new QTimer(this)),
	rotation(0)
{
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void PlanetsGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(90);
	setYRotation(0);
	setZRotation(0);

	glEnable(GL_DEPTH_TEST);
}

void PlanetsGLWidget::showEvent(QShowEvent* const)
{
	if(!timer->isActive()) {
		timer->start(1000 / 60);
	}
}

void PlanetsGLWidget::tick()
{
	rotation += 1.0f;
	while (rotation > 360) {
		rotation -= 360;
	}
	updateGL();
}

void PlanetsGLWidget::render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	//
	// original state, nothing is manipulated
	//
	glPushMatrix(); 						//begin object manipulation
	{
		glColor3f(1, 0, 0);		// Red
		glRotatef(-rotation,0,0,1); 		// the planet will rotate about its z-axis (north/south)
		glutWireSphere(20, 15, 15);  		// creates the planet
	}
	glPopMatrix();							// ends object manipulation, returns to the previous state -- in this case the original state

	glPushMatrix();							// another object
	{
		glColor3f(1,1,0);		// Yellow
		glRotatef(90,1,0,0);				// the sphere is rotated 90 degrees along the X-axis upon creation.
		glutWireSphere(15,15,15);			// no translations happen so this sphere is built right on top of the previous one
											// no variables are in the rotation so it will remain still
	}
	glPopMatrix();							// ends the second objects manipulation
	
							
	glPushMatrix();
	{
		glColor3f(1, 0, 1);		// Purple
		glRotatef(90,1,0,0);				// rotates the moon so that its equator will parallel its orbit around the planet
		glRotatef(rotation, 0, 0, 1);		// the moon will rotate around its z-axis
		glTranslatef(90, 0, 0);				// moves the object 90 x-units from the origin. The entire space that this object exists in will rotate around its z-axis.
		glutWireSphere(6, 9, 9);			// but the object is 90 units from the center, so it is now in orbit. A tide-locked orbit.
	}										// if the translate had taken place first then the space would have rotated around that translation.
	glPopMatrix();
					

	
	glPushMatrix(); 					
	{
		glColor3f(0,1,0);		// Green
		glRotatef(rotation, 0, 0, 1); 		// moon rotates around its z-axis
		glTranslatef(0, 70, 0); 			// moves the object 70 y-units from the origin.
		glRotatef(rotation, 0, 0, 1);		// the space the object exists in rotates about its z-axis.
											// this causes the object to spin at its new location and for the entire plane to spin.
											// this is an orbit that is not tide-locked.
		glutWireSphere(15, 15, 15);		
		glPushMatrix();
		{
			glColor3f(0,1,1);	//Cyan
			glRotatef((rotation*3),0,0,1);	// mini-moon rotates around its z-axis.
			glTranslatef(30,0,0);			// it is 30 x-units from its origin, which is the previous moon, not the origin!
			glutSolidSphere(6,15,15);
		}
		glPopMatrix();			
	}
	glPopMatrix();

}

void PlanetsGLWidget::hideEvent(QHideEvent* const)
{
	if(timer->isActive()) {
		timer->stop();
	}
}

