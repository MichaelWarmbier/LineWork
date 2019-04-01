#pragma once
#include <string>
#include "Definitions.h"
class lineType {
public:
	double slope();
	void showValues(int);
	void showQuadInfo();
	bool equal(lineType line1, lineType line2);
	bool parallel(lineType line1, lineType line2);
	bool perpendicular(lineType line1, lineType line2);
	void pointOfIntersection(lineType line1, lineType line2, double &x, double &y);
	int quadrilateral();
	lineType() {
		a = 0;
		b = 0;
		c = 0;
	}
private:
	double a, b, c;
};

