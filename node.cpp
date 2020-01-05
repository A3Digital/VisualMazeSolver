#include "node.h"
#include <cmath>

// Is needed to sort the node pointer pairs for Dijkstra's algorithm
bool operator<(const std::pair<float, Node*>& a, const std::pair<float, Node*>& b) {
	return a.first < b.first || (a.first == b.first && a.second < b.second);
}

void joinNodes(Node* a, Node* b) {
	// Add connections to each node
	a->connections.insert(b);
	b->connections.insert(a);
}

void generateNodes(Node*& start, Node*& end, const sf::Image& maze, std::vector<Node*>& nodes) {
	// Variables needed for creation of nodes
	unsigned int width = maze.getSize().x, height = maze.getSize().y, index = 0;
	const sf::Uint8* pixels = maze.getPixelsPtr();
	
	Node* verticalNodes[width] = { nullptr };

	// Top Border
	for(unsigned int x = 0; x < width; ++x, index += 4) {
		if(pixels[index] == 255) {
			Node* temp = new Node(x, 0);
			verticalNodes[x] = temp;
			if(!start)
				start = temp;
			else
				end = temp;
			nodes.push_back(temp);
		}
	}

	for(unsigned int y = 1; y < height - 1; ++y) {
		
		Node* prev = nullptr;

		// Left Border
		if(pixels[index] == 255) {
			prev = new Node(0, y);
			if(!start)
				start = prev;
			else
				end = prev;
			nodes.push_back(prev);
		}
		index += 4;

		// Inside
		for(unsigned int x = 1; x < width - 1; ++x, index += 4) {
			if(pixels[index] == 255) {
				int xCount = 0, yCount = 0;
				// Count how many squares to the left or right
				if(pixels[index - 4] == 255)
					++xCount;
				if(pixels[index + 4] == 255)
					++xCount;
				// Count how many squares above or below
				if(pixels[index - (width * 4)] == 255)
					++yCount;
				if(pixels[index + (width * 4)] == 255)
					++yCount;

				if((xCount == 1 && yCount == 0) || (xCount == 0 && yCount == 1) || (xCount > 0 && yCount > 0)) {
					Node* temp = new Node(x, y);
					if(prev)
						joinNodes(prev, temp);
					if(verticalNodes[x])
						joinNodes(verticalNodes[x], temp);
					prev = temp;
					verticalNodes[x] = temp;
					nodes.push_back(temp);
				}
			} else {
				prev = nullptr;
				verticalNodes[x] = nullptr;
			}
		}

		// Right Border
		if(pixels[index] == 255) {
			Node* temp = new Node(width - 1, y);
			if(prev)
				joinNodes(prev, temp);
			if(!start)
				start = temp;
			else
				end = temp;
			nodes.push_back(temp);
		}
		index += 4;
	}

	// Bottom Border
	for(unsigned int x = 0; x < width; ++x, index += 4) {
		if(pixels[index] == 255) {
			Node* temp = new Node(x, height - 1);
			if(verticalNodes[x])
				joinNodes(verticalNodes[x], temp);
			if(!start)
				start = temp;
			else
				end = temp;
			nodes.push_back(temp);
		}
	}
}

void translateMazeToPhoto(Node* n, const sf::Image& maze, const std::string& mazeName) {
	sf::Image copy = maze;

	Node* prev = n->prev;
	while(prev) {
		if(prev->x == n->x) {
			unsigned int low = std::min(prev->y, n->y);
			unsigned int high = std::max(prev->y, n->y);
			for(unsigned int i = low; i <= high; i++) {
				copy.setPixel(prev->x, i, sf::Color::Green);
			}
		} else {
			unsigned int low = std::min(prev->x, n->x);
			unsigned int high = std::max(prev->x, n->x);
			for(unsigned int i = low; i <= high; i++) {
				copy.setPixel(i, prev->y, sf::Color::Green);
			}
		}
		n = prev;
		prev = prev->prev;
	}

	copy.saveToFile( mazeName.substr(0, mazeName.size()-4) + "_solved" + mazeName.substr(mazeName.size()-4, mazeName.size()));

}