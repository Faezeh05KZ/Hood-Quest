# 🐺 HoodQuest: The Algorithm Forest

**Data Structures and Algorithms Course Project** — A text-based game where Little Red Riding Hood must navigate a forest full of branching paths to reach Grandma's house before the wolf catches her. 

There is no hunter in this version. If you are not careful, those cookies will never arrive! 🍪

---

## What is this project exactly?

The forest map is represented as a Graph. Every turn, **Dijkstra's algorithm** suggests the shortest path to Grandma's house. However, you don't have to follow it—you can manually choose an alternative route, but you must accept the risk of the wolf catching up. The wolf rolls a die every turn; if it lands on an even number, it moves one node closer to you using **BFS**.

The game also features a complete user system: registration, login, and securely hashed passwords. Player scores are ranked using a **Max-Heap** to display the leaderboard's top player. If you regret a move, there is an **Undo** feature (though it comes with a 2-point penalty 😅).

## Data Structures & Algorithms Used

Everything was implemented entirely from scratch, with `std::stack` or `std::priority_queue`!

- **Graph** (Adjacency List) — The game map.
- **Dijkstra** — Provides the suggested shortest path each turn.
- **BFS** — The wolf's tracking and movement mechanism.
- **A\*** — An alternative routing algorithm using a coordinate-distance heuristic.
- **Hash Table** (Chaining) — User database and authentication.
- **Stack** (Linked List based) — Powers the Undo feature.
- **Max-Heap** — Manages the leaderboard.
- **BST (Binary Search Tree)** — Used for searching scores by username.

## Project Structure

HoodQuest/
├── Graph/     → Map and routing logic (Graph, Vertex, Edge, BFS, Dijkstra, AStar, etc.)
├── User/      → User management, auth, and scoring (HashTable, Stack, Heap, BST, etc.)
├── Game/      → Main game engine, turn logic, rules, and UI
└── main.cpp

## How to Run?

**Prerequisites:** You need a C++ compiler that supports C++17, and CMake.
```text

git clone https://github.com/Faezeh05KZ/Hood-Quest
cd Hood-Quest
mkdir build && cd build
cmake ..
make
./HoodQuest
```
If you don't have CMake installed and just want a quick test run, this one-liner works too:
```text

g++ -std=c++17 *.cpp -o HoodQuest && ./HoodQuest
```

## Team Members

- **Aida Ramezani** — Graph Module
- **Faezeh Keshavarz** — User Module
- **Rania Afsharian** — Game Module

## Course Information

Final Project for the **Data Structures and Algorithms** course.  
**Bu-Ali Sina University**  
**Professor:** Ali Javidani
