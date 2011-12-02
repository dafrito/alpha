#include "Cuboid.h"
#include <GL/gl.h>


Cuboid::Cuboid( float length, float width, float height, GLfloat* colors):
 _length(length), _width(width), _height(height),_colors(colors) {}


void Cuboid::draw()
{
	// XXX: surely we can store this somewhere else, so it isn't created every draw
	const float width = _width/2;
	const float length = _length/2;
	const float height = _height/2;

	GLfloat vertices[] = {
	 // Front
	-width, length, height, // v0
	 width, length, height, // v1
	 width, length,-height, // v2
	-width, length,-height, // v3

	 // Back
	 width,-length, height, // v4
	-width,-length, height, // v5
	-width,-length,-height, // v6
	 width,-length,-height, // v7

	// Left
	 width, length, height, // v1
	 width,-length, height, // v4
	 width,-length,-height, // v7
 	 width, length,-height, // v2

	 // Right
	-width,-length, height, // v5
	-width, length, height, // v0
	-width, length,-height, // v3
	-width,-length,-height, // v6

	 // Top
	 width, length, height, // v1
	-width, length, height, // v0
	-width,-length, height, // v5
	 width,-length, height, // v4

	 // Bottom
	 width,-length,-height, // v7
	-width,-length,-height, // v6
	-width, length,-height, // v3
	 width, length,-height, // v2
 	};

 	GLubyte indices[] = {
		 0, 1, 2, 3,
		 4, 5, 6, 7,
		 8, 9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glColorPointer(4, GL_FLOAT, 0, _colors);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}


