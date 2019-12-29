#pragma once
#include <random>
#include <vector>
class Layer {
public:
	Layer(int previous, int height) {
		layer = std::vector<Node>();
		for (int i = 0; i < height; i++) {
			layer.push_back(Node(previous));
		}
	}
	std::vector<double> operator* (std::vector<double> rhs) const;
private:
	class Node {
	public:
		Node(int height) {
			weights = std::vector<double>();
			for (int i = 0; i < height; i++) {
				weights.push_back(((double)(rand() % (RAND_MAX - 2) + 1))/RAND_MAX); //random generation on the interval (0,1)
			}
		}
		double operator* (std::vector<double> rhs) const;

		std::vector<double> weights;
	};
	std::vector<Node> layer;
};

