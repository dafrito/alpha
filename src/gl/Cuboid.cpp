#include "Cuboid.hpp"

#include <GL/gl.h>

namespace nt {
namespace gl {

Cuboid::Cuboid(float size)
{
	setSize(size);
}

Cuboid::Cuboid( float length, float width, float height):
 _length(length/2), _width(width/2), _height(height/2) {}

void Cuboid::setAlpha(GLfloat alpha)
{
	for (int i=0;i<24*4;i++)
	{
		if ( (i+1) % 4 == 0 )
		{
			_colors[i] = alpha;
		}
	}

}
void Cuboid::setSimpleColor(float r, float g, float b, float a)
{
	for (int i=0;i<24*4; i+=4)
	{
		_colors[i] = r;
		_colors[i+1] = g;
		_colors[i+2] = b;
		_colors[i+3] = a;
	}


}

void Cuboid::setSize(const float& size)
{
	setLength(size);
	setWidth(size);
	setHeight(size);
}

void Cuboid::setDimensions(const float& length, const float& width, const float& height)
{
	setLength(length);
	setWidth(width);
	setHeight(height);
}

void Cuboid::draw()
{
	// XXX: surely we can store this somewhere else, so it isn't created every draw

	GLfloat vertices[] = {
	 // Front
	-_width, _length, _height, // v0
	 _width, _length, _height, // v1
	 _width, _length,-_height, // v2
	-_width, _length,-_height, // v3

	 // Back
	 _width,-_length, _height, // v4
	-_width,-_length, _height, // v5
	-_width,-_length,-_height, // v6
	 _width,-_length,-_height, // v7

	// Left
	 _width, _length, _height, // v1
	 _width,-_length, _height, // v4
	 _width,-_length,-_height, // v7
 	 _width, _length,-_height, // v2

	 // Right
	-_width,-_length, _height, // v5
	-_width, _length, _height, // v0
	-_width, _length,-_height, // v3
	-_width,-_length,-_height, // v6

	 // Top
	 _width, _length, _height, // v1
	-_width, _length, _height, // v0
	-_width,-_length, _height, // v5
	 _width,-_length, _height, // v4

	 // Bottom
	 _width,-_length,-_height, // v7
	-_width,-_length,-_height, // v6
	-_width, _length,-_height, // v3
	 _width, _length,-_height, // v2
 	};

    glBegin(GL_QUADS);
    for (int i = 0; i < 24; ++i) {
        glColor4f(_colors[i*4], _colors[i*4 + 1], _colors[i*4 + 2], _colors[i*4 + 3]);
        glVertex3f(vertices[i*3], vertices[i*3 + 1], vertices[i*3 + 2]);
    }
    glEnd();
}

} // namespace nt
} // namespace gl
