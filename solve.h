#include "node.h"
#include <set>

// SFML only allows 1 variable to be passed into their threads and SFML's thread
// seem much easier to use than STL's so I am using this struct to work around this issue
struct mazeType {
	// Name of maze file
	std::string mazeName;
	
	// Solves using Dijkstra if true, solve using A* if false
	bool dijkstra;

	// Extra variables needed to visualize maze solving process
	sf::Texture mazeBoard;
	sf::Mutex safety;
	bool visualize;
	bool solved;

	// Constructor
	mazeType() : mazeName(""), dijkstra(true), visualize(false), solved(false) {}
};

float calcDistance(Node* a, Node* b);

void updateMazeTexture(mazeType& maze, Node* n);

void solveDijkstra(mazeType& maze);

void solveVisualized(mazeType& maze);

// Additional functions
void trimMaze(const std::string& mazeName);

void debugMaze(const std::string& mazeName);