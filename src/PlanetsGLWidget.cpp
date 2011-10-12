#include "PlanetsGLWidget.h"

PlanetsGLWidget::PlanetsGLWidget(QWidget* const parent) :
	AnimatedGLWidget(parent),
	rotation(0)
{
}

void PlanetsGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(90);

	glEnable(GL_DEPTH_TEST);
}

void PlanetsGLWidget::tick(const float& elapsed)
{
	AnimatedGLWidget::tick(elapsed);
	rotation += 30 * elapsed;
	while (rotation > 360) {
		rotation -= 360;
	}
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
		glRotatef(-rotation,0,0,1); 		// the space this planet exists in will rotate on its z-axis
		glutWireSphere(20, 15, 15);  		// creates the planet, centered at the origin, so it rotates on its own z-axis											
	}						
	glPopMatrix();							// ends object manipulation, returns to the previous state -- in this case the original state

	glPushMatrix();							// another object
	{
		glColor3f(1,1,0);		// Yellow
		glRotatef(90,1,0,0);				// the space this object is in is rotated 90 degrees along the X-axis upon creation
		glutWireSphere(15,15,15);			// no translations happen so this sphere is built right on top of the previous one
											// no variables are in the rotation so it will remain still
	}
	glPopMatrix();							// ends the second objects manipulation
	
							
	glPushMatrix();
	{
		glColor3f(1, 0.5, 0);	// Orange
		glRotatef(90,1,0,0);				// rotates the space this moon is in so that its equator will parallel its orbit around the planet
		glRotatef(rotation, 0, 0, 1);		// this space will rotate about its z-axis
		glTranslatef(90, 0, 0);				// moves the place point 90 x-units from the origin.
		glutWireSphere(6, 15, 15);			// places the moon at the place point, which will rotate about the origin
	}										// this moon is tide-locked
	glPopMatrix();
					

	
	glPushMatrix(); 					
	{
		glColor3f(0,1,0);		// Green
		glRotatef(rotation, 0, 0, 1); 		// this space will rotate about its z-axis
		glTranslatef(0, 80, 0); 			// moves the place point 80 y-units away from the origin
		glRotatef(rotation, 0, 0, 1);		// rotates the new space centered on the place point
		glutWireSphere(15, 15, 15);			// this moon will both orbit the origin and spin on its own axis
											// this moon is not tide-locked

		glPushMatrix();
		{
			glColor3f(0,1,1);	// Cyan
			glTranslatef(25,0,0);			// moves the place point 25 x-units from the origin, which is the green moon's place point
			glutSolidSphere(3,15,15);		// this mini-moon orbits entirely because of its on the rotating plane from the green moon
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(0,0,1);	// Blue
			glRotatef(rotation*2,0,0,1);	// this mini-moon's space is rotating from its own power and that of the green moon's
			glTranslatef(45,0,0);			// since the place point is no longer on the origin the object will not orbit the origin
			glutSolidSphere(3,15,15);			

		}
		glPopMatrix();


		glPushMatrix();
		{
			glColor3f(1,0,1);	// Purple
			glRotatef(-rotation,0,0,1);		// this mini-moon is rotating against the green moon's space's rotation
			glTranslatef(35,0,0);			// making it appear that its actually orbiting the main planet
			glutWireSphere(3,15,15);
		}
		glPopMatrix();
											// all of the mini-moons are tide-locked
	}
	glPopMatrix(); 							

}
