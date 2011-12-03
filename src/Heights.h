#ifndef HEIGHTS_H
#define HEIGHTS_H

#include <cmath>
using std::max;
using std::min;

template <class T>
class Heights
{
public:
	// Proportional to the total amount of vertices rendered.
	static const int HALFSIZE=50;

	const float MAX_TIME;

	Heights() :
		MAX_TIME(6),
		time(0)
	{
		memset(heights, 0, sizeof(T) * ((HALFSIZE * 2) * (HALFSIZE * 2) - 1));
		memset(targetHeights, 0, sizeof(T) * ((HALFSIZE * 2) * (HALFSIZE * 2) - 1));
	}

	void tick(const float& elapsed)
	{
		if (time > 0)
			time -= elapsed;
		if (time < 0)
			time = 0;
	}

	template <typename F>
	void update(F func)
	{
		// The amount of compression between values. Higher values
		// cause a wider range of values to be shown.
		static const float FREQUENCY=.3;

		// Save the current vertices in the current heightmap.
		for (int y = -HALFSIZE; y < HALFSIZE; y++) {
			for (int x = -HALFSIZE; x < HALFSIZE; x++) {
				setCurrent(x, y, get(x, y));
			}
		}

		// Reset the time.
		time = MAX_TIME;

		// Set the target heightmap to the values produced by the specified
		// function.
		for (int y = -HALFSIZE; y < HALFSIZE; y++) {
			for (int x = -HALFSIZE; x < HALFSIZE; x++) {
				setTarget(x, y, func(FREQUENCY*x, FREQUENCY*y));
			}
		}
	}

	float get(int x, int y) const
	{
		convert(x, y);
		float interp = getInterpolation();
		return interp * (targetHeights[y][x] - heights[y][x]) + heights[y][x];
	}
private:

	void setTarget(int x, int y, const float& value)
	{
		convert(x, y);
		targetHeights[y][x] = value;
	}

	void setCurrent(int x, int y, const float& value)
	{
		convert(x, y);
		heights[y][x] = value;
	}

	float getInterpolation() const
	{
		return 1 - time / MAX_TIME;
	}

	void convert(int& x, int& y) const
	{
		x = max(0, min(x + HALFSIZE, HALFSIZE * 2 - 1));
		y = max(0, min(y + HALFSIZE, HALFSIZE * 2 - 1));
	}

	T heights[HALFSIZE*2][HALFSIZE*2];
	T targetHeights[HALFSIZE*2][HALFSIZE*2];

	float time;
};

#endif // HEIGHTS_H
