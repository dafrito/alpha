#include "Cube.h"
#include <GL/gl.h>

void Cube::draw()
{
	const float size = this->size();
	const float alpha = this->alpha();
	glBegin(GL_QUADS);
	// TOP is BLACK
	glColor4f(0.0f,0.0f,0.0f, alpha);
	glVertex3f( size, size, size); // Top Right
	glVertex3f(-size, size, size); // Top Left
	glVertex3f(-size,-size, size); // Bottom Left
	glVertex3f( size,-size, size); // Bottom Right
	// BOTTOM is WHITE
	glColor4f(1.0f,1.0f,1.0f, alpha);
	glVertex3f(-size, size, -size); // Top Right
	glVertex3f( size, size, -size); // Top Left
	glVertex3f( size,-size, -size); // Bottom Left
	glVertex3f(-size,-size, -size); // Bottom Right
	// LEFT is BLUE
	glColor4f(0.0f,0.0f,1.0f, alpha);
	glVertex3f(-size,-size, size); // Top Right
	glVertex3f(-size, size, size); // Top Left
	glVertex3f(-size, size,-size); // Bottom Left
	glVertex3f(-size,-size,-size); // Bottom Right
	// RIGHT is BLUE
	glVertex3f( size, size, size); // Top Right
	glVertex3f( size,-size, size); // Top Left
	glVertex3f( size,-size,-size); // Bottom Left
	glVertex3f( size, size,-size); // Bottom Right
	// FRONT is GREEN
	glColor4f(0.0f,1.0f,0.0f, alpha);
	glVertex3f(-size, size, size); // Top Right
	glVertex3f( size, size, size); // Top Left
	glVertex3f( size, size,-size); // Bottom Left
	glVertex3f(-size, size,-size); // Bottom Right
	// BACK is RED
	glColor4f(1.0f,0.0f,0.0f, alpha);
	glVertex3f( size,-size, size); // Top Right
	glVertex3f(-size,-size, size); // Top Left
	glVertex3f(-size,-size,-size); // Bottom Left
	glVertex3f( size,-size,-size); // Bottom Right
	glEnd();
}
