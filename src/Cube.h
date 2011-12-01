#ifndef CUBE_H
#define CUBE_H

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

#endif // CUBE_H
