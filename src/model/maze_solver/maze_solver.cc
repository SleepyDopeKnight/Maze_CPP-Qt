#include "maze_solver.h"

namespace s21 {

void MazeSolver::InitData(int rows, int cols, matrix vertical_walls,
                          matrix horizontal_walls) {
  rows_ = rows;
  cols_ = cols;
  vertical_walls_ = std::move(vertical_walls);
  horizontal_walls_ = std::move(horizontal_walls);
}

MazeSolver::matrix MazeSolver::Solve(int row_start_position,
                                     int col_start_position,
                                     int row_end_position,
                                     int col_end_position) {
  if (row_start_position < kNegativePoint ||
      row_end_position < kNegativePoint || col_end_position < kNegativePoint ||
      col_start_position < kNegativePoint || rows_ < kMinMazeSize ||
      cols_ < kMinMazeSize || rows_ > kMaxMazeSize || cols_ > kMaxMazeSize) {
    return {};
  }
  matrix maze(rows_, std::vector<int>(cols_, 0));
  maze[row_start_position][col_start_position] = -1;
  WavePropagation(maze, row_start_position, col_start_position,
                  row_end_position, col_end_position);
  maze[row_start_position][col_start_position] = 0;
  exist_path_ = FindPath(maze, row_start_position, col_start_position,
                         row_end_position, col_end_position);
  return maze;
}

void MazeSolver::WavePropagation(matrix &maze, int row_index, int col_index,
                                 int row_end_position, int col_end_position) {
  int size_of_wave = 2;
  CellInfo_ pass = {0, 0, 0};
  std::stack<CellInfo_> empty_stack;
  while (true) {
    count_of_pass_ = 0;
    RightwardPropagation(maze, row_index, col_index, size_of_wave);
    LeftwardPropagation(maze, row_index, col_index, size_of_wave);
    UpwardPropagation(maze, row_index, col_index, size_of_wave);
    DownwardPropagation(maze, row_index, col_index, size_of_wave);
    if (!fork_position_.empty() && count_of_pass_ == 0) {
      pass = fork_position_.top();
      row_index = pass.cell_row_;
      col_index = pass.cell_col_;
      size_of_wave = pass.cell_wave_;
      fork_position_.pop();
      count_of_pass_ = -1;
    }
    if ((row_index == row_end_position && col_index == col_end_position) ||
        count_of_pass_ == 0) {
      std::swap(fork_position_, empty_stack);
      break;
    }
  }
}

void MazeSolver::ForkCheck(matrix &maze, int &row_index, int &col_index,
                           int &size_of_wave) {
  if (RightOfWay(maze, row_index, col_index, size_of_wave)) {
    ++count_of_pass_;
  }
  if (LeftOfWay(maze, row_index, col_index, size_of_wave)) {
    ++count_of_pass_;
  }
  if (UpOfWay(maze, row_index, col_index, size_of_wave)) {
    ++count_of_pass_;
  }
  if (DownOfWay(maze, row_index, col_index, size_of_wave)) {
    ++count_of_pass_;
  }

  if (count_of_pass_ >= 2) {
    fork_position_.push({row_index, col_index, size_of_wave});
    if (count_of_pass_ == 3) {
      fork_position_.push({row_index, col_index, size_of_wave});
    }
  }
}

void MazeSolver::RightwardPropagation(matrix &maze, int &row_index,
                                      int &col_index, int &size_of_wave) {
  if (RightOfWay(maze, row_index, col_index, size_of_wave)) {
    ForkCheck(maze, row_index, col_index, size_of_wave);
    maze[row_index][col_index + 1] = size_of_wave;
    col_index += 1;
    ++size_of_wave;
  }
}

void MazeSolver::LeftwardPropagation(matrix &maze, int &row_index,
                                     int &col_index, int &size_of_wave) {
  if (LeftOfWay(maze, row_index, col_index, size_of_wave)) {
    ForkCheck(maze, row_index, col_index, size_of_wave);
    maze[row_index][col_index - 1] = size_of_wave;
    col_index -= 1;
    ++size_of_wave;
  }
}

void MazeSolver::UpwardPropagation(matrix &maze, int &row_index, int &col_index,
                                   int &size_of_wave) {
  if (UpOfWay(maze, row_index, col_index, size_of_wave)) {
    ForkCheck(maze, row_index, col_index, size_of_wave);
    maze[row_index - 1][col_index] = size_of_wave;
    row_index -= 1;
    ++size_of_wave;
  }
}

void MazeSolver::DownwardPropagation(matrix &maze, int &row_index,
                                     int &col_index, int &size_of_wave) {
  if (DownOfWay(maze, row_index, col_index, size_of_wave)) {
    ForkCheck(maze, row_index, col_index, size_of_wave);
    maze[row_index + 1][col_index] = size_of_wave;
    row_index += 1;
    ++size_of_wave;
  }
}

bool MazeSolver::RightOfWay(const matrix &maze, const int &row_index,
                            const int &col_index, const int &size_of_wave) {
  return (vertical_walls_[row_index][col_index] == 0 &&
          (maze[row_index][col_index + 1] == 0 ||
           maze[row_index][col_index + 1] > size_of_wave));
}

bool MazeSolver::LeftOfWay(const matrix &maze, const int &row_index,
                           const int &col_index, const int &size_of_wave) {
  return (col_index > 0 && vertical_walls_[row_index][col_index - 1] == 0 &&
          (maze[row_index][col_index - 1] == 0 ||
           maze[row_index][col_index - 1] > size_of_wave));
}

bool MazeSolver::UpOfWay(const matrix &maze, const int &row_index,
                         const int &col_index, const int &size_of_wave) {
  return (row_index > 0 && horizontal_walls_[row_index - 1][col_index] == 0 &&
          (maze[row_index - 1][col_index] == 0 ||
           maze[row_index - 1][col_index] > size_of_wave));
}

bool MazeSolver::DownOfWay(const matrix &maze, const int &row_index,
                           const int &col_index, const int &size_of_wave) {
  return (horizontal_walls_[row_index][col_index] == 0 &&
          (maze[row_index + 1][col_index] == 0 ||
           maze[row_index + 1][col_index] > size_of_wave));
}

bool MazeSolver::FindPath(matrix &maze, int row_start_position,
                          int col_start_position, int row_end_position,
                          int col_end_position) {
  if (count_of_pass_ == 0) {
    return false;
  }
  maze[row_start_position][col_start_position] = 1;
  path_.clear();
  int current_position = maze[row_end_position][col_end_position];
  std::pair<int, int> local_minimum_position = {row_end_position,
                                                col_end_position};
  path_.emplace_back(local_minimum_position);
  while (maze[row_end_position][col_end_position] != 1) {
    if (col_end_position < cols_ - 1 &&
        vertical_walls_[row_end_position][col_end_position] == kPass &&
        current_position == maze[row_end_position][col_end_position + 1] + 1) {
      // right
      current_position = maze[row_end_position][col_end_position + 1];
      local_minimum_position = {row_end_position, col_end_position + 1};
    } else if (row_end_position < rows_ - 1 &&
               horizontal_walls_[row_end_position][col_end_position] == kPass &&
               current_position ==
                   maze[row_end_position + 1][col_end_position] + 1) {
      // down
      current_position = maze[row_end_position + 1][col_end_position];
      local_minimum_position = {row_end_position + 1, col_end_position};
    } else if (col_end_position > 0 &&
               vertical_walls_[row_end_position][col_end_position - 1] ==
                   kPass &&
               current_position ==
                   maze[row_end_position][col_end_position - 1] + 1) {
      // left
      current_position = maze[row_end_position][col_end_position - 1];
      local_minimum_position = {row_end_position, col_end_position - 1};
    } else if (row_end_position > 0 &&
               horizontal_walls_[row_end_position - 1][col_end_position] ==
                   kPass &&
               current_position ==
                   maze[row_end_position - 1][col_end_position] + 1) {
      // up
      current_position = maze[row_end_position - 1][col_end_position];
      local_minimum_position = {row_end_position - 1, col_end_position};
    }
    row_end_position = local_minimum_position.first;
    col_end_position = local_minimum_position.second;
    path_.emplace_back(local_minimum_position);
  }
  return true;
}

std::vector<std::pair<int, int>> MazeSolver::GetPath() { return path_; }

bool MazeSolver::GetResultFindPath() { return exist_path_; }
}  // namespace s21
