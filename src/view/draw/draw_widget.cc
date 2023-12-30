#include "draw_widget.h"

#include "ui_draw_widget.h"

namespace s21 {
Draw::Draw(QWidget *parent, Control *control)
    : QWidget(parent), control_widget_(control), ui_(new Ui::Draw) {
  ui_->setupUi(this);
}

Draw::~Draw() { delete ui_; }

void Draw::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  if (draw_) {
    QPen pen_maze(Qt::black, kWallThickness, Qt::SolidLine);
    QPen pen_path(Qt::white, kWallThickness, Qt::SolidLine);
    painter.setPen(pen_maze);

    if (generate_) {
      controllers_.SetMazeSize(control_widget_->GetRow(),
                               control_widget_->GetCol());
      controllers_.StartGenerate();
      find_ = false;
    }
    if (file_) {
      update();
      find_ = false;
    }
    if (file_ || generate_) {
      InitWalls();
      generate_ = false;
      file_ = false;
    }
    DrawMaze(painter);
    if (find_) {
      painter.setPen(pen_path);
      DrawPath(painter);
    }
  }
}

void Draw::InitWalls() {
  horizontal_walls_ = controllers_.GetFromFileMazeHorizontalWalls();
  vertical_walls_ = controllers_.GetFromFileMazeVerticalWalls();

  rows_ = horizontal_walls_.size();
  if (rows_ > 0) {
    cols_ = horizontal_walls_[0].size();
  }

  control_widget_->SetMaxValuePathSpinbox(rows_, cols_);
  control_widget_->SetTextOfMazeSize(rows_, cols_);
}

void Draw::DrawMaze(QPainter &painter) {
  if (rows_ <= kMaxMazeSize && rows_ >= kMinMazeSize && cols_ <= kMaxMazeSize &&
      cols_ >= kMinMazeSize) {
    QRect square(kUpperLeftCorner, kUpperLeftCorner, kHEeightAndWidth,
                 kHEeightAndWidth);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (j < cols_ - 1 && vertical_walls_[i][j] == kWall) {
          painter.fillRect(kUpperLeftCorner + (j * kHEeightAndWidth / cols_) +
                               kHEeightAndWidth / cols_,
                           kUpperLeftCorner + (i * kHEeightAndWidth / rows_),
                           kWallThickness, kHEeightAndWidth / rows_, Qt::black);
        }
        if (i < rows_ - 1 && horizontal_walls_[i][j] == kWall) {
          painter.fillRect(kUpperLeftCorner + (j * kHEeightAndWidth / cols_),
                           kUpperLeftCorner + (i * kHEeightAndWidth / rows_) +
                               kHEeightAndWidth / rows_,
                           kHEeightAndWidth / cols_, kWallThickness, Qt::black);
        }
      }
    }
    painter.drawRect(square);
  } else {
    draw_ = false;
  }
}

void Draw::DrawPath(QPainter &painter) {
  controllers_.StartWave(
      control_widget_->GetStartX(), control_widget_->GetStartY(),
      control_widget_->GetEndX(), control_widget_->GetEndY());
  if (controllers_.GetIsPathFound()) {
    std::vector<std::pair<int, int>> maze_path = controllers_.GetMazePath();
    for (size_t i = 0; i < maze_path.size() - 1; ++i) {
      painter.drawLine(
          kUpperLeftCorner + maze_path[i].second * kHEeightAndWidth / cols_ +
              kHEeightAndWidth / cols_ / 2,
          kUpperLeftCorner + maze_path[i].first * kHEeightAndWidth / rows_ +
              kHEeightAndWidth / rows_ / 2,
          kUpperLeftCorner +
              maze_path[i + 1].second * kHEeightAndWidth / cols_ +
              kHEeightAndWidth / cols_ / 2,
          kUpperLeftCorner + maze_path[i + 1].first * kHEeightAndWidth / rows_ +
              kHEeightAndWidth / rows_ / 2);
    }
  }
}

void Draw::DrawGeneratedMaze() {
  control_widget_->SetTextOfFileName("");
  generate_ = true;
  draw_ = true;
  update();
}

void Draw::DrawMazePath() {
  if (draw_) {
    find_ = true;
    update();
  }
}

void Draw::ReadFile(const QString &file_path) {
  if (controllers_.FileUpload(file_path.toStdString())) {
    file_ = true;
    draw_ = true;
  } else {
    draw_ = false;
    control_widget_->SetMaxValuePathSpinbox(kMinPathPoints, kMinPathPoints);
    control_widget_->SetTextOfMazeSize(0, 0);
  }
}

void Draw::SaveMaze(const QString &file_path) {
  controllers_.FileSave(file_path.toStdString());
}
}  // namespace s21
