#include "maze_generator.h"

namespace s21 {

MazeGenerator::MazeGenerator() : counter_(1), gen_(rd_()), dis_(0, 1) {}

void MazeGenerator::GenerateMaze(int rows, int cols) {
  ClearData();
  InitData(rows, cols);
  for (int row = 0; row < rows_; ++row) {
    AddRow(row);
    AddRightWalls(row);
    AddBottomWalls(row);
  }
  if (rows_ > 1) {
    FixLastRow();
  }
}

void MazeGenerator::InitData(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  maze_.assign(rows_, std::vector<int>(cols_, 0));
  vertical_walls_.assign(rows_, std::vector<int>(cols_, 0));
  horizontal_walls_.assign(rows_, std::vector<int>(cols_, 1));
  for (int i = 0; i < rows; ++i) {
    vertical_walls_[i][cols_ - 1] = kWall;
  }
}

void MazeGenerator::AddRow(int row) {
  for (int col = 0; col < cols_; ++col) {
    if (row == 0 || horizontal_walls_[row - 1][col]) {
      maze_[row][col] = counter_;
      ++counter_;
    } else {
      maze_[row][col] = maze_[row - 1][col];
    }
  }
}

void MazeGenerator::AddRightWalls(int row) {
  for (int col = 0; col < cols_ - 1; ++col) {
    if (maze_[row][col] == maze_[row][col + 1] || dis_(gen_)) {
      vertical_walls_[row][col] = kWall;
    } else {
      MergeSets(row, col);
    }
  }
}

void MazeGenerator::AddBottomWalls(int row) {
  bool is_closed = true;
  for (int col = 0; col < cols_; ++col) {
    if (col > 0 && vertical_walls_[row][col - 1]) {
      is_closed = true;
    }
    if (is_closed && (vertical_walls_[row][col] || dis_(gen_))) {
      horizontal_walls_[row][col] = kPass;
      is_closed = false;
    }
  }
}

void MazeGenerator::MergeSets(int row, int col) {
  int current_set_element = maze_[row][col];
  int replaceable_element = maze_[row][col + 1];
  for (col = 0; col < cols_; ++col) {
    if (maze_[row][col] == replaceable_element) {
      maze_[row][col] = current_set_element;
    }
  }
}

void MazeGenerator::FixLastRow() {
  int row = rows_ - 1;
  horizontal_walls_[row].assign(cols_, 1);
  for (int col = 0; col < cols_ - 1; ++col) {
    if (maze_[row][col] != maze_[row][col + 1]) {
      if (vertical_walls_[row - 1][col]) {
        vertical_walls_[row - 1][col] = kPass;
      } else {
        vertical_walls_[row][col] = kPass;
      }
    }
  }
}

void MazeGenerator::ClearData() {
  counter_ = 1;
  vertical_walls_.clear();
  horizontal_walls_.clear();
  maze_.clear();
}

MazeGenerator::matrix MazeGenerator::GetHorizontalWalls() {
  return horizontal_walls_;
}

MazeGenerator::matrix MazeGenerator::GetVerticalWalls() {
  return vertical_walls_;
}

}  // namespace s21
