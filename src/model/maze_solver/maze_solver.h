#ifndef A1_MAZE_1_MAZE_SOLVER_H_
#define A1_MAZE_1_MAZE_SOLVER_H_

#include <stack>
#include <utility>
#include <vector>

constexpr int kWall = 1;
constexpr int kPass = 0;
constexpr int kNegativePoint = 0;
constexpr int kMinMazeSize = 2;
constexpr int kMaxMazeSize = 50;

namespace s21 {
class MazeSolver {
 public:
  using matrix = std::vector<std::vector<int>>;

  MazeSolver() = default;
  ~MazeSolver() = default;

  MazeSolver(MazeSolver &&) = delete;
  MazeSolver(const MazeSolver &) = delete;
  MazeSolver &operator=(const MazeSolver &) = delete;
  MazeSolver &operator=(MazeSolver &&) = delete;

  void InitData(int rows, int cols, matrix vertical_walls,
                matrix horizontal_walls);
  matrix Solve(int row_start_position, int col_start_position,
               int row_end_position, int col_end_position);
  bool FindPath(matrix &maze, int row_start_position, int col_start_position,
                int row_end_position, int col_end_position);
  std::vector<std::pair<int, int>> GetPath();
  bool GetResultFindPath();

 private:
  void WavePropagation(matrix &maze, int row_index, int col_index,
                       int row_end_position, int col_end_position);
  void ForkCheck(matrix &maze, int &row_index, int &col_index,
                 int &size_of_wave);
  void RightwardPropagation(matrix &maze, int &row_index, int &col_index,
                            int &size_of_wave);
  void LeftwardPropagation(matrix &maze, int &row_index, int &col_index,
                           int &size_of_wave);
  void UpwardPropagation(matrix &maze, int &row_index, int &col_index,
                         int &size_of_wave);
  void DownwardPropagation(matrix &maze, int &row_index, int &col_index,
                           int &size_of_wave);
  bool RightOfWay(const matrix &maze, const int &row_index,
                  const int &col_index, const int &size_of_wave);
  bool LeftOfWay(const matrix &maze, const int &row_index, const int &col_index,
                 const int &size_of_wave);
  bool UpOfWay(const matrix &maze, const int &row_index, const int &col_index,
               const int &size_of_wave);
  bool DownOfWay(const matrix &maze, const int &row_index, const int &col_index,
                 const int &size_of_wave);

  int rows_{};
  int cols_{};
  matrix vertical_walls_{};
  matrix horizontal_walls_{};
  std::vector<std::pair<int, int>> path_ = {{0, 0}};

  struct CellInfo_ {
    int cell_row_ = 0;
    int cell_col_ = 0;
    int cell_wave_ = 0;
  };
  std::stack<CellInfo_> fork_position_;
  int count_of_pass_ = -1;
  bool exist_path_ = false;
};

}  // namespace s21

#endif  // A1_MAZE_1_MAZE_SOLVER_H_
