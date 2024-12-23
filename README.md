# A* Traffic Management System

This project implements a traffic management system using the A* algorithm (with a twist of Dijkstra's algorithm) to find the shortest path between two locations. The system is based on a set of interconnected nodes representing different locations, and roads between these locations are associated with distances. It calculates the optimal route between a start location and a goal location using the A* algorithm (without heuristic to behave like Dijkstra's).

## Features
- **Location Nodes:** Add locations with unique IDs and geographical coordinates.
- **Road Connections:** Connect locations with roads, each with a specific weight (distance).
- **Shortest Path Calculation:** Find the shortest path between two locations using the A* algorithm.
- **Graphical Representation:** Display locations and their respective connections in the system.

## How to Use
1. **Add Locations and Roads:** Add nodes (locations) and define roads (edges) between them along with the corresponding distances.
2. **Calculate Shortest Path:** Enter a starting location and a destination location to find the shortest path using the A* algorithm.
3. **Display the Shortest Path:** The path will be displayed in a user-friendly format.

## Algorithm
- The **A* Algorithm** is used to compute the shortest path between two locations. While typically utilizing a heuristic, this version of the algorithm uses the same behavior as **Dijkstra's algorithm** by setting the heuristic to zero. This removes the need for heuristic distance calculations and calculates the shortest path based purely on the weights (distances) of the roads.

## Requirements
- C++ Compiler (with C++11 or higher)
- Standard C++ Library

## Key Components
- **Node:** Represents a location with an ID, name, and geographical coordinates.
- **TrafficSystem:** The main class handling the addition of locations, roads, and the A* algorithm for pathfinding.
- **A* Algorithm (Dijkstra's Version):** Calculates the shortest path between two locations by evaluating all possible paths.
