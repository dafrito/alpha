#ifndef CUBOID_H
#define CUBOID_H

#include <GL/gl.h>

namespace nt {
namespace gl {

/*
	       -X ---width--- +X
	+Z        v0-------v1
	 |       /|       /|
	 |      v5-------v4|     +Y
	 height | |      | |    /
	 |      |v3      | v2  length
	 |      |/       |/   /
	-Z      v6------v7  -Y

*/

// drawn Front->Back->Left->Right->Top->Bottom
// TODO: add offsets so all angles do not have to be right angles
// and opposing faces don't have to be the same size
class Cuboid
{
	float _length;
	float _width;
	float _height;
	GLfloat _colors[24*4];

public:
	Cuboid(float size);
	Cuboid( float length, float width, float height);
	void draw();

	void setSize(const float& size);

	void setDimensions(
			const float& length,
			const float& width,
			const float& height);

	void setWidth(const float width) { _width = width/2; }
	float width() { return _width*2; }

	void setLength(const float length) { _length = length/2; }
	float length() { return _length*2; }

	void setHeight(const float height) { _height = height/2; }
	float height() { return _height*2; }

	void colors(GLfloat colors[24*4]) { for (int i=0;i<24*4-1;i++) {_colors[i] = colors[i];} }
	void setSimpleColor(float r, float g, float b, float a);
	GLfloat colors() { return *_colors;}

	void setAlpha(GLfloat alpha);
};

} // namespace gl
} // namespace nt

#endif // CUBOID_H
