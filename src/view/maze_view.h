#ifndef A1_MAZE_1_MAZE_VIEW_H_
#define A1_MAZE_1_MAZE_VIEW_H_

#include <QMainWindow>

#include "../controllers/maze_controllers.h"
#include "./control/control_widget.h"
#include "./draw/draw_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeView;
}
QT_END_NAMESPACE
namespace s21 {
class MazeView : public QMainWindow {
  Q_OBJECT

 public:
  MazeView(QWidget *parent = nullptr);
  ~MazeView();

 private:
  void Connections();

  Draw *draw_widget_;
  Control *control_widget_;
  Ui::MazeView *ui_;
  s21::MazeControllers controllers_;
};
}  // namespace s21
#endif  // A1_MAZE_1_MAZE_VIEW_H_
