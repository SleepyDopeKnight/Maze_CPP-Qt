#ifndef A1_MAZE_1_MAZE_CONTROLLERS_H_
#define A1_MAZE_1_MAZE_CONTROLLERS_H_

#include "../model/maze_facade.h"

namespace s21 {
class MazeControllers {
 public:
  using matrix = std::vector<std::vector<int>>;
  MazeControllers();
  ~MazeControllers();

  void SetMazeSize(int rows, int cols);
  matrix GetGeneratedMazeVerticalWalls();
  matrix GetGeneratedMazeHorizontalWalls();
  matrix GetFromFileMazeVerticalWalls();
  matrix GetFromFileMazeHorizontalWalls();
  std::vector<std::pair<int, int>> GetMazePath();
  bool GetIsPathFound();

  void StartGenerate();
  void StartWave(int row_start_position, int col_start_position,
                 int row_end_position, int col_end_position);
  void FileSave(std::string file_path);
  bool FileUpload(std::string file_path);

 private:
  MazeFacade *maze_facade_;
};
}  // namespace s21

#endif  // A1_MAZE_1_MAZE_CONTROLLERS_H_