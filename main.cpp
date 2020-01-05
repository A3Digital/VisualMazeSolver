// g++ -g -Wall main.cpp node.cpp solve.cpp -o solve -lsfml-graphics -lsfml-window -lsfml-system

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <cmath>
#include "solve.h"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cerr << "Not enough arguments\n";
		exit(1);
	}

	mazeType maze;
	bool debug = false;
	bool trim = false;

	for(int i = 1; i < argc; ++i) {
		if(std::string(argv[i]) == "-visualize") 
			maze.visualize = true;
		else if(std::string(argv[i]) == "-dijkstra")
			maze.dijkstra = true;
		else if(std::string(argv[i]) == "-A*")
			maze.dijkstra = false;
		else if(std::string(argv[i]) == "-trim")
			trim = true;
		else if(std::string(argv[i]) == "-debug")
			debug = true;
		else
			maze.mazeName = std::string(argv[i]);
	}

	if(debug)
		debugMaze(maze.mazeName);
	else if(trim)
		trimMaze(maze.mazeName);
	else if(maze.visualize) 
		solveVisualized(maze);
	else
		solveDijkstra(maze);

}