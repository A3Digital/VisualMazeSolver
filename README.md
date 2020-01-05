# Visual Maze Solver

## Overview
This program is a basic maze solver that takes in the photo of a maze and outputs a photo of the solution. This program has an additional option to visualize the solving process to see how the pathfinding algorithm works.

The point of this project was familiarize myself with graphs (networks of nodes), pathfinding algorithms (Dijkstra's and A*), multithreaded programming, and the SFML library. 

## Showcase
<!---All of these gifs have been manually synchronized to have a total of 150 frames and to start solving on the 30th frame. These were shot with OBS and then edited on ezgif.com--->
![Generated Small Maze - Dijkstra](<Maze Gifs/Generated Small Maze - Dijkstra.gif>)

![Generated Small Maze 2 - Dijkstra](<Maze Gifs/Generated Small Maze 2 - Dijkstra.gif>)

The following is the same maze solved with two different solving algorithms 

Dijkstra's:
![Generated 101x101 Maze - Dijkstra](<Generated 101x101 Maze - Dijkstra.gif>)

A*:
![Generated 101x101 Maze - A Star](<Generated 101x101 Maze - A Star.gif>)

It should be noted that due to the fact that mazes usually only have one solution that is very intricate and does not always head directly towards the end goal, the advantage of A*'s direction heuristic tends to be marginalized. However, the advantage becomes more apparent in mazes made with various turns and solutions such as the following. 

![Neutral Maze - Dijkstra](<Maze Gifs/Neutral Maze - Dijkstra.gif>)

![Neutral Maze - A Star](<Maze Gifs/Neutral Maze - A Star.gif>)