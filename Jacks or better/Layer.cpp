#include "Layer.h"

std::vector<double> Layer::operator*(std::vector<double> rhs) const {
	std::vector<double> calc = std::vector<double>();
	for (int i = 0; i < rhs.size(); i++) {
		calc.push_back(layer[i] * rhs);
	}
	return calc;
}

double Layer::Node::operator*(std::vector<double> rhs) const {
	double calc = 0.0;
	for (int i = 0; i < rhs.size(); i++) {
		calc += weights[i] * rhs[i];
	}
	return ((calc / (abs(calc) + 1)) + 1) / 2;
}
