#ifndef __MMATH_H__
#define __MMATH_H__

double RandomUniform(double a, double b) {
	double c = 1.0 * rand() / RAND_MAX;
	return c * (b - a) + a;
}

double RandomNormal(double m, double s) {
	static const double pi = 4 * atan(1);

	double u1 = RandomUniform(0, 1);
	double u2 = RandomUniform(0, 1);
	double r = sqrt(-2 * log(u2));
	double theta = 2 * pi * u1;
	double z = r * cos(theta);

	return m + z * s;
}

#endif
