#include "common.h"

float getAngle(int x1, int y1, int x2, int y2) {
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0) {
		*dx = *dy = 0;
		return;
	}
	*dx = (x1 - x2);
	*dx /= steps;
	*dy = (y1 - y2);
	*dy /= steps;
}

int getDistance(int x1, int y1, int x2, int y2) {
    int x = x2 - x1;
	int y = y2 - y1;
	return sqrt(x * x + y *y);
}

void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy) {
    angle *= (PI/180);
    float x3 = (x1 - x2) * cos(angle) - (y1 - y2) * sin(angle);
    float y3 = (y1 - y2) * cos(angle) + (x1 - x2) * sin(angle);
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));
    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }
    *dx = x3;
    *dx /= steps;
    *dy = y3;
    *dy /= steps;
}