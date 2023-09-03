#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

struct Maze {
  uint8_t length;
  int size_x;
  int size_y;
  std::vector<std::vector<char> > tiles;
};

std::vector<Maze> readMazes(
    const std::string& filename,
    const std::vector<int>& indices = std::vector<int>()) {
  std::vector<Maze> mazes;
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return mazes;
  }

  // Remove duplicates and sort indices
  std::set<int> uniqueIndices(indices.begin(), indices.end());
  std::vector<int> sortedIndices(uniqueIndices.begin(), uniqueIndices.end());
  std::sort(sortedIndices.begin(), sortedIndices.end());

  int mazeIndex = 1;  // Start from index 1 as specified
  while (file) {
    Maze maze;
    char length, size_x, size_y;

    file.read(&length, sizeof(length));
    file.read(&size_x, sizeof(size_x));
    file.read(&size_y, sizeof(size_y));

    if (!file) break;  // no header to read -> end of the file

    maze.length = static_cast<uint8_t>(length);
    maze.size_x = static_cast<int>(size_x);
    maze.size_y = static_cast<int>(size_y);

    maze.tiles.resize(maze.size_y);
    for (int y = 0; y < maze.size_y; ++y) {
      maze.tiles[y].resize(maze.size_x);
      file.read(&maze.tiles[y][0], maze.size_x);
    }

    // Only push the maze if indices is empty or the current maze index is in
    // indices
    if (sortedIndices.empty() ||
        std::find(sortedIndices.begin(), sortedIndices.end(), mazeIndex) !=
            sortedIndices.end()) {
      mazes.push_back(maze);
    }

    mazeIndex++;
  }

  file.close();
  return mazes;
}

int main() {
  std::string filename = "../../mazes/mazes.bin";
  std::vector<Maze> mazes =
      readMazes(filename, {2, 5, 3, 2});  // Example with indices

  // Print the mazes to check
  for (const Maze& maze : mazes) {
    std::cout << "Length: " << static_cast<char16_t>(maze.length) << ", "
              << "Size X: " << maze.size_x << ", "
              << "Size Y: " << maze.size_y << std::endl;
    for (const auto& row : maze.tiles) {
      for (char tile : row) {
        std::cout << static_cast<int>(tile);
      }
      std::cout << std::endl;
    }
    std::cout << "------------------" << std::endl;
  }

  return 0;
}
