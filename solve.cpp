#include "solve.h"
#include <cmath>
#include <set>
#include <iostream>
#include <thread>

float calcDistance(Node* a, Node* b) {
	return sqrt( pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
}

void updateMazeTexture(mazeType& maze, Node* n) {
	Node* prev = n->prev;
	while(prev) {
		if(prev->x == n->x) {
			unsigned int low = std::min(prev->y, n->y);
			unsigned int high = std::max(prev->y, n->y);
			
			sf::Uint8 pixels[(high - low + 1) * 4] = { 0 };
			for(unsigned int i = 1; i < (high - low + 1) * 4; i += 4) {
				pixels[i] = 255 / (1 + maze.solved); // Green
				pixels[i+1] = 255 * maze.solved; // Blue
				pixels[i+2] = 255; // Alpha
			}

			maze.mazeBoard.update(pixels, 1, high - low + 1, n->x, low);

		} else {
			unsigned int low = std::min(prev->x, n->x);
			unsigned int high = std::max(prev->x, n->x);
			
			sf::Uint8 pixels[(high - low + 1) * 4] = { 0 };
			for(unsigned int i = 1; i < (high - low + 1) * 4; i += 4) {
				pixels[i] = 255 / (1 + maze.solved); // Green
				pixels[i+1] = 255 * maze.solved; // Blue
				pixels[i+2] = 255; // Alpha
			}

			maze.mazeBoard.update(pixels, high - low + 1, 1, low, n->y);

		}
		n = prev;
		prev = prev->prev;
	}
}

void solveDijkstra(mazeType& maze) {

	sf::Image original;
	if(!original.loadFromFile(maze.mazeName)) 
		exit(1);

	float sleepTime = 0.0;

	if(maze.visualize) {
		// Let's the window open if being visualized
		sf::sleep(sf::seconds(0.5));
		sleepTime = (15.0 / (original.getSize().x * original.getSize().y));	
	}

	Node *start = nullptr, *end = nullptr;
	std::vector<Node*> all_nodes;

	generateNodes(start, end, original, all_nodes);
	
	typedef std::set<std::pair<float, Node*> > pq;
	pq nodes;

	Node* n = start;

	n->distance = 0;

	nodes.insert(std::make_pair(n->distance, n));

	while(!nodes.empty()) {

		pq::iterator itr = nodes.begin();
		n = itr->second;

		if(maze.visualize) {
			maze.safety.lock();
			maze.mazeBoard.loadFromImage(original);
	
			updateMazeTexture(maze, n);
			maze.safety.unlock();
	
			sf::sleep(sf::seconds(sleepTime));
		}
		// Maze has been solved
		if(n == end)
			break;

		for(std::unordered_set<Node*>::iterator itr_n = n->connections.begin(); itr_n != n->connections.end(); ++itr_n) {
			Node* temp = *itr_n;
			// Since nodes are connected either horizontally or vertically, this distance must be an integer
			int distance = abs((n->x - temp->x) + (n->y - temp->y));
			if(temp->distance == -1) {
				// Update data
				temp->prev = n;
				temp->distance = n->distance + distance;
				temp->connections.erase(n);
				// Insert node into set
				float displacement = 0;
				if(!maze.dijkstra)
					displacement = calcDistance(temp, end);
				nodes.insert(std::make_pair(temp->distance + displacement, temp));
			} else if(n->distance + distance < temp->distance) {
				// Erase previous node
				nodes.erase(std::make_pair(temp->distance, temp));
				// Update data
				temp->prev = n;
				temp->distance = n->distance + distance;
				temp->connections.erase(n);
				// Insert node into set
				float displacement = 0;
				if(!maze.dijkstra)
					displacement = calcDistance(temp, end);
				nodes.insert(std::make_pair(temp->distance + displacement, temp));
			
			}
		}

		nodes.erase(itr);

	}

	if(n == end) {
		if(maze.visualize){
			maze.safety.lock();
			maze.solved = true;
			updateMazeTexture(maze, end);
			maze.safety.unlock();
		}
		
		translateMazeToPhoto(end, original, maze.mazeName);
		std::cout << "The maze has been solved!\n";
	} else {
		if(maze.visualize) {
			maze.safety.lock();
			maze.mazeBoard.loadFromImage(original);
			maze.safety.unlock();
		}

		std::cout << "This maze can not be solved.\n";
	}

	for(Node* n : all_nodes) {
		delete n;
	}

}

void solveVisualized(mazeType& maze) {

	if (!maze.mazeBoard.loadFromFile(maze.mazeName))
		exit(1);

	sf::Sprite mazeSprite;
	mazeSprite.setTexture(maze.mazeBoard);

	// Calculate window size
	int scale = std::min(sf::VideoMode::getDesktopMode().width / maze.mazeBoard.getSize().x, sf::VideoMode::getDesktopMode().height / maze.mazeBoard.getSize().y);
	if(scale == 0) {
		std::cerr << "This maze file is too big to be visualized while solving.\n";
		exit(1);
	}

	mazeSprite.setScale(scale, scale);

	sf::RenderWindow window(sf::VideoMode(scale * maze.mazeBoard.getSize().x, scale * maze.mazeBoard.getSize().y ), "Solving " + maze.mazeName);
	sf::Vector2i origin(0, 1);
	window.setPosition(origin);

	sf::Thread thread(&solveDijkstra, std::ref(maze));
	thread.launch();

	while(window.isOpen()) {

		sf::Event event;
		
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		window.clear();
		maze.safety.lock();
		window.draw(mazeSprite);
		maze.safety.unlock();
		window.display();

	}
	thread.terminate();

}

void trimMaze(const std::string& mazeName) {
	sf::Image maze;
	if(!maze.loadFromFile(mazeName))
		exit(1);

	unsigned int width = maze.getSize().x, height = maze.getSize().y;

	if(maze.getPixel(0, 0) == sf::Color::Black ||
		maze.getPixel(0, height - 1) == sf::Color::Black ||
		maze.getPixel(width - 1, 0) == sf::Color::Black ||
		maze.getPixel(width - 1, height - 1) == sf::Color::Black) {
		
		std::cerr << "This maze does not need to be trimmed.\n";
		exit(1);
	}

	if(width < 3 || height < 3) {
		std::cerr << "This maze is too small.\n";
		exit(1);
	}

	sf::Image copy;
	copy.create(width - 2, height - 2);

	for(unsigned int y = 0; y < height - 2; ++y) {
		for(unsigned int x = 0; x < width - 2; ++x) {
			copy.setPixel(x, y, maze.getPixel(x+1, y+1));
		}
	}

	if(copy.saveToFile(mazeName)) {
		std::cout << "The maze was successfully trimmed.\n";
	}
}

void debugMaze(const std::string& mazeName) {
	sf::Image maze;

	if(!maze.loadFromFile(mazeName))
		exit(1);

	Node *start = nullptr, *end = nullptr;
	std::vector<Node*> all_nodes;

	generateNodes(start, end, maze, all_nodes);

	sf::Image copy = maze;
	for(Node* n : all_nodes) {
		copy.setPixel(n->x, n->y, sf::Color::Green);
		delete n;
	}

	unsigned int size = mazeName.size();

	copy.saveToFile(mazeName.substr(0, size - 4) + "_debug" + mazeName.substr(size - 4, size));

	std::cout << "The maze file with all nodes displayed has been created.\n";
}