#ifndef __NVector_H__
#define __NVector_H__

#include "basic.h"
#include "mmath.h"

template <int N>
class NVector{
public:
	double elements[N];

	NVector() {
		memset(elements, 0, sizeof elements);
	}
	NVector(double data) {
		memset(elements, 0, sizeof elements);
		for (int i = 0; i < N; i++) {
			elements[i] = data;
		}
	}
	NVector(double *data) {
		memset(elements, 0, sizeof elements);
		for (int i = 0; i < N; i++) {
			elements[i] = data[i];
		}
	}

	static double distance(const NVector &a, const NVector &b) {
		double d = 0;
		for (int i = 0; i < N; i++) {
			d += pow(a.elements[i] - b.elements[i], 2);
		}
		d = sqrt(d);
		return d;
	}

	static NVector max(const NVector &a, const NVector &b) {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = std::max(a.elements[i], b.elements[i]);
		}
		return c;
	}

	static NVector min(const NVector &a, const NVector &b) {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = std::min(a.elements[i], b.elements[i]);
		}
		return c;
	}

	NVector operator + (const NVector &a) const {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = elements[i] + a.elements[i];
		}
		return c;
	}

	NVector operator - (const NVector &a) const {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = elements[i] - a.elements[i];
		}
		return c;
	}

	NVector operator / (const NVector &a) const {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = elements[i] / a.elements[i];
		}
		return c;
	}

	double operator * (const NVector &a) const {
		double d = 0;
		for (int i = 0; i < N; i++) {
			d += elements[i] * a.elements[i];
		}
		return d;
	}

	NVector operator * (const double a) const {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = elements[i] * a;
		}
		return c;
	}

	NVector operator / (const double a) const {
		NVector<N> c;
		for (int i = 0; i < N; i++) {
			c.elements[i] = elements[i] / a;
		}
		return c;
	}

	bool operator != (const NVector &a) const {
		for (int i = 0; i < N; i++) {
			if (abs(elements[i] - a.elements[i]) > 1e-6) {
				return true;
			}
		}
		return false;
	}

	NVector & operator = (const NVector &a) {
		for (int i = 0; i < N; i++) {
			elements[i] = a.elements[i];
		}
		return *this;
	}

	void clear() {
		memset(elements, 0, sizeof elements);
	}

	double norm() {
		double d = 0;
		for (int i = 0; i < N; i++) {
			d += pow(elements[i], 2);
		}
		d = sqrt(d);
		return d;
	}

	void display() {
		for (int i = 0; i < N; i++) {
			cout << elements[i] << " ";
		}
		cout << endl;
	}

	void random() {
		for (int i = 0; i < N; i++) {
			elements[i] = RandomNormal(0, 1);
		}
		*this = *this / this->norm();
	}
};

#endif
