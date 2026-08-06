cmake_minimum_required(VERSION 3.16)

project(HoodQuest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HoodQuest
    src/main.cpp

    # Graph
    src/Graph.cpp
    src/GraphBuilder.cpp
    src/GraphPrinter.cpp
    src/Vertex.cpp
    src/Edge.cpp
    src/BFS.cpp
    src/Dijkstra.cpp
    src/AStar.cpp
    src/MinHeap.cpp

    # Game
    src/Game.cpp
    src/GameInitializer.cpp
    src/GameLoop.cpp
    src/GameState.cpp
    src/MoveManager.cpp
    src/TurnManager.cpp
    src/Renderer.cpp
    src/GameRules.cpp
    src/ScoreManager.cpp
    src/UndoManager.cpp
    src/InputManager.cpp

    # User
    src/Player.cpp
    src/Wolf.cpp
    src/Authentication.cpp
    src/User.cpp
    src/UserStorage.cpp
    src/HashTable.cpp
    src/BST.cpp
    src/Leaderboard.cpp
    src/Heap.cpp
    src/Stack.cpp
)