#include "maze_facade.h"

namespace s21 {

void MazeFacade::SetRowsCols(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
}

MazeFacade::matrix MazeFacade::GetGeneratedHorWalls() {
  return maze_generator_.GetHorizontalWalls();
}

MazeFacade::matrix MazeFacade::GetGeneratedVertWalls() {
  return maze_generator_.GetVerticalWalls();
}

MazeFacade::matrix MazeFacade::GetFromFileHorWalls() {
  return horizontal_walls_;
}

MazeFacade::matrix MazeFacade::GetFromFileVertWalls() {
  return vertical_walls_;
}

std::vector<std::pair<int, int>> MazeFacade::GetFoundedPath() {
  return maze_solver_.GetPath();
}

bool MazeFacade::GetResultMazeFindPath() {
  return maze_solver_.GetResultFindPath();
}

void MazeFacade::Generate() {
  if (rows_ >= kMinMazeSize && cols_ >= kMinMazeSize && rows_ <= kMaxMazeSize &&
      cols_ <= kMaxMazeSize) {
    maze_generator_.GenerateMaze(rows_, cols_);
    vertical_walls_ = maze_generator_.GetVerticalWalls();
    horizontal_walls_ = maze_generator_.GetHorizontalWalls();
  }
}

void MazeFacade::Solve(int row_start_position, int col_start_position,
                       int row_end_position, int col_end_position) {
  if (rows_ >= kMinMazeSize && cols_ >= kMinMazeSize && rows_ <= kMaxMazeSize &&
      cols_ <= kMaxMazeSize && !vertical_walls_.empty() &&
      !horizontal_walls_.empty()) {
    maze_solver_.InitData(rows_, cols_, vertical_walls_, horizontal_walls_);
    maze_solver_.Solve(row_start_position, col_start_position, row_end_position,
                       col_end_position);
  }
}

bool MazeFacade::RecordDataFromFile(std::string file_path) {
  rows_ = 0;
  cols_ = 0;
  std::ifstream infile(file_path);
  if (!infile) {
    return false;
  }
  infile >> rows_ >> cols_;
  if (infile.eof() || rows_ < kMinMazeSize || rows_ > kMaxMazeSize ||
      cols_ < kMinMazeSize || cols_ > kMaxMazeSize) {
    infile.close();
    return false;
  }
  if (!ValidationMatrix(infile, vertical_walls_)) {
    infile.close();
    return false;
  }
  if (!ValidationMatrix(infile, horizontal_walls_)) {
    infile.close();
    return false;
  }
  if (!CheckLastRowAndCol()) {
    infile.close();
    return false;
  }

  infile.close();
  return true;
}

bool MazeFacade::ValidationMatrix(std::ifstream &file_stream, matrix &walls) {
  walls.resize(rows_);
  for (int i = 0; i < rows_; ++i) {
    walls[i].resize(cols_);
    for (int j = 0; j < cols_; ++j) {
      file_stream >> walls[i][j];
      if (walls[i][j] != kPass && walls[i][j] != kWall) {
        return false;
      }
    }
  }
  return true;
}

bool MazeFacade::CheckLastRowAndCol() {
  for (int i = 0; i < rows_ - 1; ++i) {
    if (vertical_walls_[i][cols_ - 1] != kWall) {
      return false;
    }
  }

  for (int j = 0; j < cols_ - 1; ++j) {
    if (horizontal_walls_[rows_ - 1][j] != kWall) {
      return false;
    }
  }
  return true;
}

void MazeFacade::SaveDataToFile(std::string file_path) {
  if (vertical_walls_.size() > 0 && horizontal_walls_.size() > 0) {
    std::ofstream new_file(file_path);
    if (!new_file) {
      return;
    }
    new_file << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        new_file << vertical_walls_[i][j] << " ";
      }
      new_file << std::endl;
    }
    new_file << std::endl;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        new_file << horizontal_walls_[i][j] << " ";
      }
      new_file << std::endl;
    }
    new_file.close();
  }
}
}  // namespace s21
