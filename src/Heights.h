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

	Heights()
	{
		memset(heights, 0, (HALFSIZE * 2) * (HALFSIZE * 2));
		memset(targetHeights, 0, (HALFSIZE * 2) * (HALFSIZE * 2));
	}

	template <typename F>
	void update(F func)
	{
		// The amount of compression between values. Higher values
		// cause a wider range of values to be shown.
		static const float FREQUENCY=.3;

		for (int y = -HALFSIZE; y < HALFSIZE; y++) {
			for (int x = -HALFSIZE; x < HALFSIZE; x++) {
				set(x, y, func(FREQUENCY*x, FREQUENCY*y));
			}
		}
	}

	void set(int x, int y, const float& value)
	{
		validate(x, y);
		heights[y][x] = value;
	}

	float get(int x, int y)
	{
		validate(x, y);
		return heights[y][x];
	}
private:
	void validate(int& x, int& y)
	{
		x = max(0, min(x + HALFSIZE, HALFSIZE * 2 - 1));
		y = max(0, min(y + HALFSIZE, HALFSIZE * 2 - 1));
	}

	T heights[HALFSIZE*2][HALFSIZE*2];
	T targetHeights[HALFSIZE*2][HALFSIZE*2];
};

#endif // HEIGHTS_H
