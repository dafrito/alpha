#ifndef CUBOID_H
#define CUBOID_H

#include <GL/gl.h>


/*
	       -X ---width--- +X
	+Z        v0-------v1
	 |       /|       /|
	 |      v5-------v4|     +Y
	 height | |      | |    /
	 |      |v3      | v2  length
	 |      |/       |/   /
	-Z      v6------v7   -Y

*/

// drawn Front->Back->Left->Right->Top->Bottom
// TODO: add offsets so all angles do not have to be right angles
// and opposing faces don't have to be the same size
class Cuboid
{
	float _length;
	float _width;
	float _height;
	GLfloat *_colors;

public:
	Cuboid( float length, float width, float height,GLfloat* colors);
	void draw();

	void setWidth(const float width) { _width = width; }
	float width() { return _width; }

	void setLength(const float length) { _length = length; }
	float length() { return _length; }

	void setHeight(const float height) { _height = height; }
	float height() { return _height; }
};

/*
class Cube
{
	float _size;
	float _alpha;
public:
	Cube(const float& size) : _size(size), _alpha(1) {}
	void draw();

	void setAlpha(const float& alpha) { _alpha = alpha; }
	float alpha() { return _alpha; }

	void setSize(const float& size) { _size = size; }
	float size() { return _size; }
};
*/
#endif // CUBOID_H
