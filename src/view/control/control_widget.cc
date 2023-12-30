#include "control_widget.h"

#include "ui_control_widget.h"

namespace s21 {
Control::Control(QWidget *parent) : QWidget(parent), ui_(new Ui::Control) {
  ui_->setupUi(this);
  Connections();
}

Control::~Control() { delete ui_; }

int Control::GetRow() { return ui_->row_box->value(); }

int Control::GetCol() { return ui_->col_box->value(); }

int Control::GetStartX() { return ui_->start_x_box->value() - 1; }

int Control::GetStartY() { return ui_->start_y_box->value() - 1; }

int Control::GetEndX() { return ui_->end_x_box->value() - 1; }

int Control::GetEndY() { return ui_->end_y_box->value() - 1; }

void Control::SetMaxValuePathSpinbox(const int &rows, const int &cols) {
  ui_->start_x_box->setMaximum(rows);
  ui_->start_y_box->setMaximum(cols);
  ui_->end_x_box->setMaximum(rows);
  ui_->end_y_box->setMaximum(cols);
}

void Control::OpenFile() {
  QString file_path =
      (QFileDialog::getOpenFileName(this, "Open a file", "", "(*.txt)"));
  if (!file_path.isEmpty()) {
    SetTextOfFileName(file_path);
    emit OpenFileClicked(file_path);
  }
}

void Control::SaveFile() {
  QString file_path =
      (QFileDialog::getSaveFileName(this, "Save a file", "", "(*.txt)"));
  if (!file_path.isEmpty()) {
    emit SaveFileClicked(file_path);
  }
}

void Control::SetTextOfMazeSize(const int &rows, const int &cols) {
  QString text = QString("Строки: %1 Колонки: %2").arg(rows).arg(cols);
  ui_->maze_size->setText(text);
}

void Control::SetTextOfFileName(QString file_path) {
  QFileInfo file_info(file_path);
  QString file_name = file_info.fileName();
  ui_->file_name->setText(file_name);
}

void Control::Connections() {
  connect(ui_->file_button, &QPushButton::clicked, this, &Control::OpenFile);
  connect(ui_->save_button, &QPushButton::clicked, this, &Control::SaveFile);
  connect(ui_->generate_button, &QPushButton::clicked, this,
          &Control::GenerateMazeClicked);
  connect(ui_->path_button, &QPushButton::clicked, this,
          &Control::FindPathClicked);

  connect(ui_->row_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetRow);
  connect(ui_->col_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetCol);

  connect(ui_->start_x_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetStartX);
  connect(ui_->start_y_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetStartY);
  connect(ui_->end_x_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetEndX);
  connect(ui_->end_y_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Control::GetEndY);
}
}  // namespace s21
