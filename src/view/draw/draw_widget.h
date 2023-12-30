#ifndef A1_MAZE_1_DRAW_WIDGET_H_
#define A1_MAZE_1_DRAW_WIDGET_H_

#include <QPainter>
#include <QWidget>

#include "../../controllers/maze_controllers.h"
#include "../control/control_widget.h"

constexpr double kHEeightAndWidth = 500.0;
constexpr int kUpperLeftCorner = 15;
constexpr int kWallThickness = 2;
constexpr int kMinPathPoints = 1;

QT_BEGIN_NAMESPACE
namespace Ui {
class Draw;
}
QT_END_NAMESPACE

namespace s21 {
class Draw : public QWidget {
  Q_OBJECT

 public:
  Draw(QWidget *parent = nullptr, Control *control = nullptr);
  ~Draw();
  void ReadFile(const QString &file_path);
  void SaveMaze(const QString &file_path);

 public slots:
  void DrawMazePath();
  void DrawGeneratedMaze();

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  void InitWalls();
  void DrawMaze(QPainter &painter);
  void DrawPath(QPainter &painter);

  int rows_ = 2;
  int cols_ = 2;
  std::vector<std::vector<int>> horizontal_walls_;
  std::vector<std::vector<int>> vertical_walls_;

  bool draw_ = false;
  bool generate_ = false;
  bool file_ = false;
  bool find_ = false;

  Control *control_widget_;
  Ui::Draw *ui_;
  s21::MazeControllers controllers_;
};
}  // namespace s21
#endif  // A1_MAZE_1_DRAW_WIDGET_H_
