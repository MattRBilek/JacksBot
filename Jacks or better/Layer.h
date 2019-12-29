#pragma once
#include <random>

class Layer {
public:
	Layer(int height) {
		layer = new Node[height];
		Layer::height = height;
	}
	~Layer() {
		delete layer;
	}
	//Layer operator* (Layer rhs) const;
	//Layer operator*= (Layer rhs);
private:
	class Node {
	public:
		Node() {
			double weight = ((rand() % (RAND_MAX - 2)) + 1)/RAND_MAX;
		}
	};
	Node* layer;
	int height;
};

