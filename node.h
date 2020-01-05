#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

class Node {
public:
	// Constructor
	Node(unsigned int x_, unsigned int y_) : x(x_), y(y_), distance(-1), prev(nullptr) {}

	unsigned int x;
	unsigned int y;
	std::unordered_set<Node*> connections;

	// Used during Dijkstra's Algorithm
	int distance;
	Node* prev;
};

bool operator<(const std::pair<int, Node*>& a, const std::pair<int, Node*>& b);

void joinNodes(Node* a, Node* b);

void generateNodes(Node*& start, Node*& end, const sf::Image& maze, std::vector<Node*>& nodes);

void translateMazeToPhoto(Node* n, const sf::Image& maze, const std::string& mazeName);