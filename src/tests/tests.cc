#include <gtest/gtest.h>

#include <filesystem>

#include "../controllers/maze_controllers.h"

void TestIncorrectGenerateRun(int rows, int cols) {
  s21::MazeControllers maze;
  maze.SetMazeSize(rows, cols);
  maze.StartGenerate();
  int horizontal_walls = maze.GetGeneratedMazeHorizontalWalls().size();
  int vertical_walls = maze.GetGeneratedMazeVerticalWalls().size();
  EXPECT_EQ(horizontal_walls, 0);
  EXPECT_EQ(vertical_walls, 0);

  maze.StartWave(0, 0, 1, 1);
  bool find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);

  maze.StartWave(0, 0, 1, 1);
  find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);

  maze.StartWave(0, 0, 20, 1);
  find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);
}

TEST(generate_maze_suite, minus_maze_size) {
  TestIncorrectGenerateRun(-10, -10);
}

TEST(generate_maze_suite, zero_cols) { TestIncorrectGenerateRun(0, 40); }

TEST(generate_maze_suite, zero_rows) { TestIncorrectGenerateRun(40, 0); }

TEST(generate_maze_suite, big_rows) { TestIncorrectGenerateRun(55, 0); }

TEST(generate_maze_suite, big_cols) { TestIncorrectGenerateRun(0, 55); }

TEST(generate_maze_suite, big_maze_size) { TestIncorrectGenerateRun(55, 55); }

TEST(generate_maze_suite, zero_maze_size) { TestIncorrectGenerateRun(0, 0); }

TEST(generate_maze_suite, small_col) { TestIncorrectGenerateRun(40, 1); }

TEST(generate_maze_suite, small_row) { TestIncorrectGenerateRun(1, 40); }

TEST(generate_maze_suite, small_maze_size) { TestIncorrectGenerateRun(1, 1); }

TEST(generate_maze_suite, valid_maze_size) {
  s21::MazeControllers maze;
  maze.SetMazeSize(9, 23);
  maze.StartGenerate();
  int horizontal_walls = maze.GetGeneratedMazeHorizontalWalls().size();
  int vertical_walls = maze.GetGeneratedMazeVerticalWalls()[0].size();
  EXPECT_EQ(horizontal_walls, 9);
  EXPECT_EQ(vertical_walls, 23);

  maze.StartWave(0, 0, -11, 11);
  bool find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);

  maze.StartWave(0, 0, 8, 8);
  find_path = maze.GetIsPathFound();
  EXPECT_TRUE(find_path);
}

TEST(generate_maze_suite, great_maze) {
  for (int k = 0; k < 10; ++k) {
    s21::MazeControllers maze;
    maze.SetMazeSize(50, 50);
    maze.StartGenerate();
    int horizontal_walls = maze.GetGeneratedMazeHorizontalWalls().size();
    int vertical_walls = maze.GetGeneratedMazeVerticalWalls()[0].size();
    EXPECT_EQ(horizontal_walls, 50);
    EXPECT_EQ(vertical_walls, 50);

    for (int i = 1; i < horizontal_walls; ++i) {
      for (int j = 1; j < vertical_walls; ++j) {
        maze.StartWave(0, 0, i, j);
        bool find_path = maze.GetIsPathFound();
        ASSERT_TRUE(find_path);
      }
    }
  }
}

TEST(maze_from_file_suite, valid_file) {
  s21::MazeControllers maze;
  EXPECT_TRUE(maze.FileUpload("./tests/valid_maze.txt"));
  int horizontal_walls = maze.GetFromFileMazeHorizontalWalls().size();
  int vertical_walls = maze.GetFromFileMazeVerticalWalls()[0].size();
  EXPECT_EQ(horizontal_walls, 10);
  EXPECT_EQ(vertical_walls, 10);

  maze.StartWave(0, 0, -11, 11);
  bool find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);

  maze.StartWave(0, 0, 9, 9);
  find_path = maze.GetIsPathFound();
  EXPECT_TRUE(find_path);

  std::vector<std::pair<int, int>> expected_path = {
      {9, 9}, {8, 9}, {8, 8}, {7, 8}, {6, 8}, {6, 9}, {5, 9}, {4, 9}, {3, 9},
      {3, 8}, {4, 8}, {4, 7}, {5, 7}, {5, 6}, {5, 5}, {6, 5}, {6, 6}, {6, 7},
      {7, 7}, {8, 7}, {8, 6}, {8, 5}, {7, 5}, {7, 4}, {7, 3}, {6, 3}, {5, 3},
      {5, 4}, {4, 4}, {4, 5}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5},
      {0, 4}, {0, 3}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 2}, {2, 1}, {3, 1},
      {4, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}};
  std::vector<std::pair<int, int>> founded_path = maze.GetMazePath();
  ASSERT_EQ(expected_path, founded_path);
}

void TestIncorrectFileUploadRun(std::string file_path, int h_walls,
                                int v_walls) {
  s21::MazeControllers maze;
  EXPECT_FALSE(maze.FileUpload(file_path));
  int horizontal_walls = maze.GetFromFileMazeHorizontalWalls().size();
  int vertical_walls = maze.GetFromFileMazeVerticalWalls().size();
  EXPECT_EQ(horizontal_walls, h_walls);
  EXPECT_EQ(vertical_walls, v_walls);

  maze.StartWave(0, 0, 7, 2);
  bool find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);
}

TEST(maze_from_file_suite, empty_file) {
  TestIncorrectFileUploadRun("./tests/empty_maze.txt", 0, 0);
}

TEST(maze_from_file_suite, big_rows_cols_file) {
  TestIncorrectFileUploadRun("./tests/big_rows_cols_maze.txt", 0, 0);
}

TEST(maze_from_file_suite, small_rows_cols_file) {
  TestIncorrectFileUploadRun("./tests/small_rows_cols_maze.txt", 0, 0);
}

TEST(maze_from_file_suite, incorrect_data_file) {
  TestIncorrectFileUploadRun("./tests/incorrect_data_maze.txt", 3, 3);
}

TEST(maze_from_file_suite, incorrect_last_col_file) {
  TestIncorrectFileUploadRun("./tests/broken_last_col_maze.txt", 3, 3);
}

TEST(maze_from_file_suite, incorrect_last_row_file) {
  TestIncorrectFileUploadRun("./tests/broken_last_row_maze.txt", 3, 3);
}

TEST(maze_from_file_suite, incorrect_horizontal_wall_file) {
  TestIncorrectFileUploadRun("./tests/broken_h_walls_maze.txt", 3, 3);
}

TEST(maze_from_file_suite, incorrect_vertical_wall_file) {
  TestIncorrectFileUploadRun("./tests/broken_v_walls_maze.txt", 0, 3);
}

TEST(maze_from_file_suite, png_file) {
  TestIncorrectFileUploadRun("./tests/png_in_past.txt", 0, 0);
}

TEST(maze_from_file_suite, no_file) { TestIncorrectFileUploadRun("", 0, 0); }

TEST(maze_from_file_suite, incorrect_path) {
  TestIncorrectFileUploadRun("./testdsadas/png_in_past.txt", 0, 0);
}

TEST(maze_from_file_suite, not_great_maze_file) {
  s21::MazeControllers maze;
  EXPECT_TRUE(maze.FileUpload("./tests/not_great_maze.txt"));
  int horizontal_walls = maze.GetFromFileMazeHorizontalWalls().size();
  int vertical_walls = maze.GetFromFileMazeVerticalWalls()[0].size();
  EXPECT_EQ(horizontal_walls, 3);
  EXPECT_EQ(vertical_walls, 3);

  maze.StartWave(0, 0, 1, 0);
  bool find_path = maze.GetIsPathFound();
  EXPECT_TRUE(find_path);

  maze.StartWave(0, 0, 2, 2);
  find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);
  maze.StartWave(2, 2, 0, 0);
  find_path = maze.GetIsPathFound();
  EXPECT_FALSE(find_path);
}

TEST(maze_from_file_suite, save_file) {
  s21::MazeControllers maze;
  EXPECT_TRUE(maze.FileUpload("./tests/valid_maze.txt"));
  maze.FileSave("./tests/saved_maze.txt");

  std::ifstream file_stream("./tests/saved_maze.txt");
  std::string file_content((std::istreambuf_iterator<char>(file_stream)),
                           std::istreambuf_iterator<char>());

  std::string expected_content =
      "10 10\n"
      "1 1 0 0 0 0 1 0 0 1 \n"
      "0 1 0 1 1 1 1 1 1 1 \n"
      "1 0 0 1 0 1 1 0 1 1 \n"
      "1 1 1 0 0 0 1 1 0 1 \n"
      "0 1 0 1 0 0 1 0 1 1 \n"
      "1 0 1 0 1 0 0 1 1 1 \n"
      "1 0 1 1 1 0 0 1 0 1 \n"
      "0 0 0 0 0 1 0 1 1 1 \n"
      "1 1 0 0 1 0 0 1 0 1 \n"
      "0 0 0 1 0 0 0 0 0 1 \n"
      "\n"
      "0 0 0 1 0 1 0 0 1 0 \n"
      "0 1 1 0 0 0 0 0 0 0 \n"
      "0 0 0 1 1 1 0 1 0 0 \n"
      "0 0 1 1 1 1 0 0 0 0 \n"
      "0 0 0 1 0 1 1 0 0 0 \n"
      "0 1 1 0 1 0 1 1 1 0 \n"
      "1 1 0 0 0 1 1 0 0 1 \n"
      "0 1 1 1 1 0 1 0 0 0 \n"
      "0 0 1 1 0 1 1 1 1 0 \n"
      "1 1 1 1 1 1 1 1 1 1 \n";
  EXPECT_EQ(file_content, expected_content);

  std::filesystem::remove("./tests/saved_maze.txt");
}

TEST(maze_from_file_suite, no_save_file) {
  s21::MazeControllers maze;
  EXPECT_TRUE(maze.FileUpload("./tests/valid_maze.txt"));
  maze.FileSave("");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
