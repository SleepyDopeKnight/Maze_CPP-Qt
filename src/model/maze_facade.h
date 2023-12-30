#ifndef A1_MAZE_1_MAZE_FACADE_H_
#define A1_MAZE_1_MAZE_FACADE_H_

#include <fstream>

#include "./maze_generator/maze_generator.h"
#include "./maze_solver/maze_solver.h"

namespace s21 {
class MazeFacade {
 public:
  using matrix = std::vector<std::vector<int>>;

  MazeFacade() = default;
  ~MazeFacade() = default;

  MazeFacade(const MazeFacade &) = delete;
  MazeFacade(MazeFacade &&) = delete;
  MazeFacade &operator=(const MazeFacade &) = delete;
  MazeFacade &operator=(MazeFacade &&) = delete;

  void SetRowsCols(int rows, int cols);
  matrix GetGeneratedHorWalls();
  matrix GetGeneratedVertWalls();
  matrix GetFromFileHorWalls();
  matrix GetFromFileVertWalls();
  std::vector<std::pair<int, int>> GetFoundedPath();
  bool GetResultMazeFindPath();

  void Generate();
  void Solve(int row_start_position, int col_start_position,
             int row_end_position, int col_end_position);
  bool RecordDataFromFile(std::string file_path);
  void SaveDataToFile(std::string file_path);

 private:
  bool ValidationMatrix(std::ifstream &file_stream, matrix &walls);
  bool CheckLastRowAndCol();

  s21::MazeSolver maze_solver_;
  s21::MazeGenerator maze_generator_;

  int rows_;
  int cols_;
  matrix vertical_walls_;
  matrix horizontal_walls_;
};

}  // namespace s21

#endif  // A1_MAZE_1_MAZE_FACADE_H_
