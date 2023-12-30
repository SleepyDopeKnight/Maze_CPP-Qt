#include "maze_view.h"

#include "ui_maze_view.h"

namespace s21 {
MazeView::MazeView(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeView) {
  ui_->setupUi(this);

  control_widget_ = new Control;
  draw_widget_ = new Draw(nullptr, control_widget_);

  ui_->control_widget->addWidget(control_widget_);
  ui_->draw_widget->addWidget(draw_widget_);
  Connections();
}

MazeView::~MazeView() {
  delete ui_;
  delete draw_widget_;
  delete control_widget_;
}

void MazeView::Connections() {
  connect(control_widget_, &Control::GenerateMazeClicked, draw_widget_,
          &Draw::DrawGeneratedMaze);
  connect(control_widget_, &Control::FindPathClicked, draw_widget_,
          &Draw::DrawMazePath);
  connect(control_widget_, &Control::OpenFileClicked, draw_widget_,
          &Draw::ReadFile);
  connect(control_widget_, &Control::SaveFileClicked, draw_widget_,
          &Draw::SaveMaze);
}
}  // namespace s21
