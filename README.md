# Visual Maze Solver

## Overview
This program is a basic maze solver that takes in the photo of a maze and outputs a photo of the solution. This program has an additional option to visualize the solving process to see how the pathfinding algorithm works.

The point of this project was familiarize myself with graphs (networks of nodes), pathfinding algorithms (Dijkstra's and A*), multithreaded programming, and the SFML library. 

## Showcase
<!---All of these gifs have been manually synchronized to have a total of 150 frames and to start solving on the 30th frame. These were shot with OBS and then edited on ezgif.com--->
<img src="Maze Gifs/Generated Small Maze - Dijkstra.gif" alt="Generated Small Maze - Dijkstra"  width=250/>

<img src="Maze Gifs/Generated Small Maze 2 - Dijkstra.gif" alt="Generated Small Maze 2 - Dijkstra"  width=250/>

The following is the same maze solved with two different solving algorithms 

Dijkstra's: <br>
<img src="Maze Gifs/Generated 101x101 Maze - Dijkstra.gif" alt="Generated 101x101 Maze - Dijkstra"  width=250/>

A*: <br>
<img src="Maze Gifs/Generated 101x101 Maze - A Star.gif" alt="Generated 101x101 Maze - A Star"  width=250/>

It should be noted that due to the fact that mazes usually only have one solution that is very intricate and does not always head directly towards the end goal, the advantage of A*'s direction heuristic tends to be marginalized. However, the advantage becomes more apparent in mazes made with various turns and solutions such as the following. 

Dijkstra's: <br>
<img src="Maze Gifs/Neutral Maze - Dijkstra.gif" alt="Neutral Maze - Dijkstra"  width=250/>

A*: <br>
<img src="Maze Gifs/Neutral Maze - A Star.gif" alt="Neutral Maze - A Star"  width=250/>
