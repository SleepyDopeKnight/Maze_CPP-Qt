#include "./maze_controllers.h"

namespace s21 {
MazeControllers::MazeControllers() { maze_facade_ = new MazeFacade; }

MazeControllers::~MazeControllers() { delete maze_facade_; }

void MazeControllers::SetMazeSize(int rows, int cols) {
  maze_facade_->SetRowsCols(rows, cols);
}

MazeControllers::matrix MazeControllers::GetGeneratedMazeVerticalWalls() {
  return maze_facade_->GetGeneratedVertWalls();
}

MazeControllers::matrix MazeControllers::GetGeneratedMazeHorizontalWalls() {
  return maze_facade_->GetGeneratedHorWalls();
}

MazeControllers::matrix MazeControllers::GetFromFileMazeVerticalWalls() {
  return maze_facade_->GetFromFileVertWalls();
}

MazeControllers::matrix MazeControllers::GetFromFileMazeHorizontalWalls() {
  return maze_facade_->GetFromFileHorWalls();
}

std::vector<std::pair<int, int>> MazeControllers::GetMazePath() {
  return maze_facade_->GetFoundedPath();
}

bool MazeControllers::GetIsPathFound() {
  return maze_facade_->GetResultMazeFindPath();
}

void MazeControllers::StartGenerate() { maze_facade_->Generate(); }

void MazeControllers::StartWave(int row_start_position, int col_start_position,
                                int row_end_position, int col_end_position) {
  maze_facade_->Solve(row_start_position, col_start_position, row_end_position,
                      col_end_position);
}

void MazeControllers::FileSave(std::string file_path) {
  maze_facade_->SaveDataToFile(file_path);
}

bool MazeControllers::FileUpload(std::string file_path) {
  return maze_facade_->RecordDataFromFile(file_path);
}

}  // namespace s21