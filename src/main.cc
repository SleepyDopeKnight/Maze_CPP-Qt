#include <QApplication>

#include "./view/maze_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MazeView w;
  w.show();
  return a.exec();
}
