#ifndef A1_MAZE_1_MAZE_GENERATOR_H_
#define A1_MAZE_1_MAZE_GENERATOR_H_

#include <random>
#include <vector>

namespace s21 {
constexpr int kWall = 1;
constexpr int kPass = 0;
class MazeGenerator {
 public:
  using matrix = std::vector<std::vector<int>>;

  MazeGenerator();
  ~MazeGenerator() = default;

  MazeGenerator(MazeGenerator &&) = delete;
  MazeGenerator(const MazeGenerator &) = delete;
  MazeGenerator &operator=(const MazeGenerator &) = delete;
  MazeGenerator &operator=(MazeGenerator &&) = delete;

  void GenerateMaze(int rows, int cols);

  matrix GetHorizontalWalls();
  matrix GetVerticalWalls();

 private:
  void AddRow(int row);
  void AddRightWalls(int row);
  void AddBottomWalls(int row);
  void MergeSets(int row, int col);
  void FixLastRow();
  void ClearData();
  void InitData(int rows, int cols);

  int counter_;
  int rows_{};
  int cols_{};

  matrix maze_{};
  matrix vertical_walls_{};
  matrix horizontal_walls_{};

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> dis_;
};

}  // namespace s21

#endif  // A1_MAZE_1_MAZE_GENERATOR_H_
